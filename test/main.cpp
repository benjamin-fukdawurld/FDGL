#include <iostream>

#include <FD3D/SceneGraph/SceneLoader.h>
#include <FD3D/Utils/TrasformStack.h>

#include <FDGL/OpenGLBuffer.h>
#include <FDGL/OpenGLVertexArray.h>
#include <FDGL/OpenGLUtils.h>
#include <FDGL/BufferedMesh.h>

#include <FDCore/TimeManager.h>

#include "GLFWImpl.h"
#include "GLUtils.h"

#include <thread>
#include <chrono>
#include <unordered_set>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


using namespace std;
using namespace std::chrono_literals;

std::ostream &operator<<(std::ostream &out, const glm::quat &q)
{
    return out << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
}

std::ostream &operator<<(std::ostream &out, const glm::vec2 &q)
{
    return out << "[" << q.x << ", " << q.y << "]";
}

std::ostream &operator<<(std::ostream &out, const glm::vec3 &q)
{
    return out << "[" << q.x << ", " << q.y << ", " << q.z << "]";
}

std::ostream &operator<<(std::ostream &out, const glm::vec4 &q)
{
    return out << "[" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << "]";
}

std::ostream &operator<<(std::ostream &out, const glm::mat4 &m)
{
    auto getCell = [](const glm::mat4 &m, int row, int col)
    {
        switch(row)
        {
            case 0:
            return m[col].x;

            case 1:
            return m[col].y;

            case 2:
            return m[col].z;

            case 3:
            return m[col].w;

            default:
            return std::numeric_limits<float>::signaling_NaN();
        }
    };

    out << "[";

    cout << "\t" << getCell(m, 0, 0);
    for(int col = 1; col < 4; ++col)
    {
        cout << ", " << getCell(m, 0, col);
    }

    for(int row = 1; row < 4; ++row)
    {
        cout << endl;
        cout << "\t" << getCell(m, row, 0);
        for(int col = 1; col < 4; ++col)
        {
            cout << ", " << getCell(m, row, col);
        }
    }

    return out << endl << "]";
}

class Renderer
{
    protected:
        Context &m_ctx;
        FD3D::Scene m_scene;
        FD3D::TrasformStack m_transformStack;
        FDGL::OpenGLShaderProgram m_program;
        FDGL::OpenGLTexture m_tex;
        FD3D::CameraNode *m_activeCamera;
        FD3D::Transform m_transform;

    public:
        Renderer(Context &ctx):
            m_ctx(ctx),
            m_activeCamera(nullptr)
        {}

        ~Renderer() = default;

        const Context &getOpenGLContex() const
        {
            return m_ctx;
        }

        Context &getOpenGLContex()
        {
            return m_ctx;
        }

        FD3D::Camera *getActiveCamera()
        {
            return (m_activeCamera == nullptr ?
                        nullptr
                      : &m_activeCamera->getEntity());
        }

        const FD3D::Camera *getActiveCamera() const
        {
            return (m_activeCamera == nullptr ?
                        nullptr
                      : &m_activeCamera->getEntity());
        }

        void onInit(FDGL::BaseOpenGLWindow &w)
        {
            initContext();

            w.setClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
            w.setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            assert(loadScene("../../FDGL/test/resources/crate/CrateModel.obj"));

            std::vector<FD3D::CameraNode*> cams = m_scene.getNodesAs<FD3D::CameraNode>();
            if(cams.empty())
            {
                std::unique_ptr<FD3D::CameraNode> cam(new FD3D::CameraNode);
                cams.push_back(cam.get());
                m_scene.addNode(cam.release());
            }

            m_activeCamera = cams.front();

            std::vector<FDGL::BufferedMesh*> meshes = m_scene.getComponentsAs<FDGL::BufferedMesh>();
            for(auto *m: meshes)
                m->setVAOFunctionToDefault();


            m_program = createShaderProgram();
            m_program.bind();
            m_tex = loadTexture("../../FDGL/test/resources/wall.jpg");

            FD3D::Projection &proj = getActiveCamera()->projection;
            proj.setFov(glm::radians(45.0f));
            proj.setWidth(w.getWidth());
            proj.setHeight(w.getHeight());
            proj.setNear(0.1f);
            proj.setFar(100.0f);
            proj.setType(FD3D::ProjectionType::Perspective);
            m_program.setUniform(2, proj.getMatrix());
        }

        void onQuit(FDGL::BaseOpenGLWindow &)
        {

        }

        void onRender(FDGL::BaseOpenGLWindow &w)
        {
            w.clear();

            // activate shader
            m_program.bind();
            m_program.setUniform("texture", 0);

            // bind textures on corresponding texture units
            m_tex.activateTexture(0);
            m_tex.bind(FDGL::TextureTarget::Texture2D);

            double t2 = glfwGetTime();
            float radius = 10.0f;
            float camX = sin(t2) * radius;
            float camZ = cos(t2) * radius;
            getActiveCamera()->setPosition(glm::vec3(camX, 0.0f, camZ));
            getActiveCamera()->setRotation(glm::vec3(0.0f, t2, 0.0f));
            m_program.setUniform(1, getActiveCamera()->getMatrix());

            std::stack<FD3D::SceneNode::id_type> todo;
            std::unordered_set<FD3D::SceneNode::id_type> explored;
            todo.push(m_scene.getNode(m_scene.getRootId()));
            while(!todo.empty())
            {
                FD3D::SceneNode::id_type current = todo.top();
                FD3D::SceneNodeProxy node = m_scene.getNode(current);
                if(!node)
                {
                    todo.pop();
                    continue;
                }

                if(explored.find(current) != explored.end())
                {
                    drawNode(node);
                    todo.pop();
                    m_transformStack.pop();
                    continue;
                }

                addNodeChildren(todo, explored, current);
                FD3D::ObjectNode *obj = node->as<FD3D::ObjectNode>();
                if(obj != nullptr)
                    m_transformStack.push(obj->getEntity());

                explored.insert(current);
            }

            w.swapBuffer();
        }

        void onResize(FDGL::BaseOpenGLWindow &, int width, int height)
        {
            getActiveCamera()->projection.setWidth(width);
            getActiveCamera()->projection.setHeight(height);
        }

        void onError(FDGL::ErrorSoure source, FDGL::ErrorType type,
                     uint32_t id, FDGL::ErrorSeverity level,
                     const std::string &msg) const
        {
            constexpr const char *format = "GL_DEBUG_MESSAGE:"
                                           "\n{"
                                           "\n    source: %s,"
                                           "\n    type: %s,"
                                           "\n    severity: %s,"
                                           "\n    id: %u"
                                           "\n    message: %s"
                                           "\n}\n";
            fprintf(stderr, format,
                    FDGL::errorSourceToString(source).c_str(),
                    FDGL::errorTypeToString(type).c_str(),
                    FDGL::errorSeverityToString(level).c_str(),
                    id, msg.c_str());
        }

    private:
        static void debugCallbackHelper(GLenum source,
                                        GLenum type,
                                        GLuint id,
                                        GLenum severity,
                                        GLsizei length,
                                        const GLchar *message,
                                        const void *userParam)
        {
            const Renderer *r = reinterpret_cast<const Renderer *>(userParam);
            r->onError(static_cast<FDGL::ErrorSoure>(source),
                       static_cast<FDGL::ErrorType>(type), id,
                       static_cast<FDGL::ErrorSeverity>(severity),
                       std::string(message, static_cast<size_t>(length)));
        }

        void initContext()
        {
            m_ctx.enableDepth();
            m_ctx.enableFaceCulling();
            m_ctx.enableDebugOutut();
            glDebugMessageCallback(&Renderer::debugCallbackHelper, this);
        }


        bool loadScene(const std::string &path)
        {
            FDGL::BufferedMesh::setDefaultVAOFunction([](FDGL::BufferedMesh &mesh)
            {
                FDGL::OpenGLBufferWrapper vbo = mesh.getVBO();
                FDGL::OpenGLBufferWrapper ebo = mesh.getEBO();
                vbo.bind(FDGL::BufferTarget::VertexAttribute);
                ebo.bind(FDGL::BufferTarget::VertexIndex);
                size_t s = mesh.getStride() * sizeof(float);
                FDGL::setAttribFromBuffer<GL_FLOAT, 3, false>(0, s,
                    static_cast<size_t>(mesh.getComponentOffset(FD3D::VertexComponentType::Position)) * sizeof(float));
                FDGL::enableAttrib(0);
                FDGL::setAttribFromBuffer<GL_FLOAT, 3, false>(1, s,
                    static_cast<size_t>(mesh.getComponentOffset(FD3D::VertexComponentType::Normal)) * sizeof(float));
                FDGL::enableAttrib(1);
                FDGL::setAttribFromBuffer<GL_FLOAT, 2, false>(2, s,
                    static_cast<size_t>(mesh.getComponentOffset(FD3D::VertexComponentType::Texture)) * sizeof(float));
                FDGL::enableAttrib(2);
            });
            FD3D::SceneLoader loader;
            loader.setTextureLoader([](const std::string &path){
                return loadTexture(path);
            });
            loader.setEmbeddedTextureLoader([](const aiTexture *texture){
                return loadTexture(texture);
            });
            loader.setMeshAllocator([](){
                return new FDGL::BufferedMesh();
            });
            return loader.loadScene(m_scene, path, aiProcess_Triangulate);
        }

        size_t addNodeChildren(std::stack<FD3D::SceneNode::id_type> &stack,
                               std::unordered_set<FD3D::SceneNode::id_type> &done,
                               FD3D::SceneNode::id_type node)
        {
            size_t result = 0;
            const std::vector<FD3D::SceneNode::id_type> &children = m_scene.getNode(node)->getChildIds();
            for(size_t i = 0, imax = children.size(); i < imax; ++i)
            {
                if(done.find(children[i]) != done.end())
                {
                    stack.push(children[i]);
                    ++result;
                }
            }

            return result;
        }

        void drawNode(FD3D::SceneNodeProxy &node)
        {
            m_program.setUniform(0, m_transformStack.getCurrentMatrix());
            std::vector<FDGL::BufferedMesh*> meshes = node.getComponentsAs<FDGL::BufferedMesh>();
            for(size_t i = 0, imax = meshes.size(); i < imax; ++i)
            {
                meshes[i]->getVAO().bind();
                FDGL::drawElements<uint32_t>(FDGL::DrawMode::Triangles, meshes[i]->getNumberOfIndices(), nullptr);
            }
        }
};


int draw_mesh(int, char* [])
{
    Context ctx;
    if(!ctx.init())
        return -1;

    Window w;
    if(!w.create(800, 600, "Test window"))
        return -1;

    ctx.setCurrentContext(w);
    if (!ctx.loadOpenGLFunctions(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        return -1;

    Renderer renderer(ctx);
    w.setRenderer(renderer);
    w.init();

    FDCore::TimeManager<> timeMgr;
    timeMgr.start();

    // render loop
    // -----------
    while (w.isOpen())
    {
        w.processInput();
        w.render();
    }

    return 0;
}

int draw_cube(int, char* [])
{
    uint16_t indices[] = {
        0, 1, 2,
        2, 1, 3,

        4, 5, 6,
        6, 5, 7,

        8, 9, 10,
        10, 9, 11,

        12, 13, 14,
        14, 13, 15,

        16, 17, 18,
        18, 17, 19,

        20, 21, 22,
        22, 21, 23,

        24, 25, 26,
        26, 25, 27
    };

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

        0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, 0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f
    };

    Context ctx;
    if(!ctx.init())
        return -1;

    Window w;
    if(!w.create(800, 600, "Test window"))
        return -1;

    ctx.setCurrentContext(w);
    if (!ctx.loadOpenGLFunctions(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        return -1;

    ctx.enableDepth();
    ctx.enableFaceCulling();

    w.setClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
    w.setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    FDGL::OpenGLShaderProgram program = createShaderProgram();
    FDGL::OpenGLTexture tex = loadTexture("../../FDGL/test/resources/wall.jpg");

    FDGL::OpenGLBuffer vbo, ebo;
    vbo.create();
    vbo.bind(FDGL::BufferTarget::VertexAttribute);
    vbo.allocate(sizeof(float) * 120, FDGL::BufferUsage::StaticDraw, vertices);
    ebo.create();
    ebo.bind(FDGL::BufferTarget::VertexIndex);
    ebo.allocate(sizeof(uint16_t) * 36, FDGL::BufferUsage::StaticDraw, indices);

    FDGL::OpenGLVertexArray vao;
    vao.create();
    vao.setFunction([](FDGL::OpenGLBuffer &vbo, FDGL::OpenGLBuffer &ebo)
    {
        vbo.bind(FDGL::BufferTarget::VertexAttribute);
        ebo.bind(FDGL::BufferTarget::VertexIndex);
        FDGL::setAttribFromBuffer<GL_FLOAT, 3, false>(0, 5 * sizeof(float), 0);
        FDGL::setAttribFromBuffer<GL_FLOAT, 2, false>(1, 5 * sizeof(float), sizeof(float) * 3);

        FDGL::enableAttrib(0);
        FDGL::enableAttrib(1);
    }, std::ref(vbo), std::ref(ebo));

    program.bind();


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    program.setUniform("texture", 1, 0);

    // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
    // -----------------------------------------------------------------------------------------------------------
    FD3D::Camera cam;
    FD3D::Projection &proj = cam.projection;
    proj.setFov(glm::radians(45.0f));
    proj.setWidth(w.getWidth());
    proj.setHeight(w.getHeight());
    proj.setNear(0.1f);
    proj.setFar(100.0f);
    proj.setType(FD3D::ProjectionType::Perspective);
    program.setUniform(2, proj.getMatrix());

    FD3D::Transform transform;

    // render loop
    // -----------
    while (w.isOpen())
    {
        w.processInput();
        w.clear();

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);

        // activate shader
        program.bind();

        // camera/view transformation
        float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        cam.setPosition(glm::vec3(camX, 0.0f, camZ));
        cam.setRotation(glm::vec3(0.0f, glfwGetTime(), 0.0f));
        program.setUniform(1, cam.getMatrix());

        //program.setUniform(0, transform.getMatrix());
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        program.setUniform(0, model);
        vao.bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, reinterpret_cast<void*>(0));

        w.swapBuffer();
    }

    return 0;
}


int draw_triangle()
{
    Context ctx;
    if(!ctx.init())
        return -1;

    Window w;
    if(!w.create(800, 600, "Test window"))
        return -1;

    ctx.setCurrentContext(w);
    if (!ctx.loadOpenGLFunctions(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        return -1;

    w.setClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
    w.setClearMask(GL_COLOR_BUFFER_BIT);

    FDGL::OpenGLShaderProgram program = createShaderProgram();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };

    FDGL::OpenGLBuffer vbo;
    vbo.create();
    vbo.bind(FDGL::BufferTarget::VertexAttribute);
    vbo.allocate(sizeof(float) * 9, FDGL::BufferUsage::StaticDraw, vertices);

    FDGL::OpenGLVertexArray vao;
    vao.create();
    vao.setFunction([](FDGL::OpenGLBuffer &vbo){
        vbo.bind(FDGL::BufferTarget::VertexAttribute);
        FDGL::setAttribFromBuffer<GL_FLOAT, 3, false>(0, 3 * sizeof(float), 0);

        FDGL::enableAttrib(0);
    }, std::ref(vbo));

    while (w.isOpen())
    {
        w.processInput();
        w.clear();

        program.bind();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        w.swapBuffer();
    }

    return 0;
}

int main(int argc, char *argv[])
{
    /*FD3D::Transform trans;
    cout << trans.getMatrix() << endl;

    trans.setRotation(glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
    cout << glm::degrees(trans.getEulerAngles()) << endl;
    cout << trans.getRotation() << endl;
    cout << trans.getMatrix() << endl;
    trans.rotate(glm::vec3(0.0f, glm::radians(90.0f), 0.0f));
    cout << glm::degrees(trans.getEulerAngles()) << endl;
    cout << trans.getRotation() << endl;
    cout << trans.getMatrix() << endl;*/

    return draw_mesh(argc, argv);
}
