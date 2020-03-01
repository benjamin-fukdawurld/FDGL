#include <iostream>

#include <FD3D/SceneGraph/SceneLoader.h>
#include <FDGL/OpenGLBuffer.h>
#include <FDGL/OpenGLVertexArray.h>
#include <FDGL/OpenGLUtils.h>

#include <FDCore/TimeManager.h>

#include "GLFWImpl.h"
#include "GLUtils.h"

#include <thread>
#include <chrono>

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

    ctx.enableDepth();
    ctx.enableFaceCulling();

    w.setClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
    w.setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    FDCore::TimeManager<> timeMgr;
    timeMgr.start();

    FD3D::Scene scene;
    FD3D::SceneLoader loader;
    loader.setTextureLoader([](const std::string &path){
        return loadTexture(path);
    });
    loader.setEmbeddedTextureLoader([](const aiTexture *texture){
        return loadTexture(texture);
    });
    assert(loader.loadScene(scene,
        "/home/ben/Bureau/dev/FanatikDevelopment/FDGL/test/resources/crate/CrateModel.obj",
        aiProcess_Triangulate
    ));

    std::vector<FD3D::Mesh*> meshes = scene.getComponentsAs<FD3D::Mesh>();
    std::vector<FD3D::Material*> mat = scene.getComponentsAs<FD3D::Material>();

    FDGL::OpenGLShaderProgram program = createShaderProgram();
    FDGL::OpenGLTexture tex = loadTexture("../../FDGL/test/resources/wall.jpg");

    FDGL::OpenGLBuffer vbo, ebo;
    vbo.create();
    vbo.bind(FDGL::BufferTarget::VertexAttribute);
    vbo.allocate(sizeof(float) * meshes[0]->getNumberOfVertices() * meshes[0]->getVertexSize(),
            FDGL::BufferUsage::StaticDraw, meshes[0]->getVertices());
    ebo.create();
    ebo.bind(FDGL::BufferTarget::VertexIndex);
    ebo.allocate(sizeof(uint32_t) * meshes[0]->getNumberOfIndices(),
            FDGL::BufferUsage::StaticDraw, meshes[0]->getIndices());

    FDGL::OpenGLVertexArray vao;
    vao.create();
    vao.setFunction([](FDGL::OpenGLBuffer &vbo, FDGL::OpenGLBuffer &ebo, FD3D::AbstractMesh &m)
    {
        vbo.bind(FDGL::BufferTarget::VertexAttribute);
        ebo.bind(FDGL::BufferTarget::VertexIndex);
        size_t s = m.getStride() * sizeof(float);
        FDGL::setAttribFromBuffer<GL_FLOAT, 3, false>(0, s,
            static_cast<size_t>(m.getComponentOffset(FD3D::VertexComponentType::Position)) * sizeof(float));
        FDGL::enableAttrib(0);
        FDGL::setAttribFromBuffer<GL_FLOAT, 3, false>(1, s,
            static_cast<size_t>(m.getComponentOffset(FD3D::VertexComponentType::Normal)) * sizeof(float));
        FDGL::enableAttrib(1);
        FDGL::setAttribFromBuffer<GL_FLOAT, 2, false>(2, s,
            static_cast<size_t>(m.getComponentOffset(FD3D::VertexComponentType::Texture)) * sizeof(float));
        FDGL::enableAttrib(2);
    }, std::ref(vbo), std::ref(ebo), std::ref(*meshes.front()));

    program.bind();


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    program.setUniform("texture", 0);

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
        tex.activateTexture(0);
        tex.bind(FDGL::TextureTarget::Texture2D);

        // activate shader
        program.bind();

        // camera/view transformation
        float t = timeMgr.getElapsedTime<std::chrono::seconds>();
        double t2 = glfwGetTime();
        float radius = 10.0f;
        float camX = sin(t2) * radius;
        float camZ = cos(t2) * radius;
        cam.setPosition(glm::vec3(camX, 0.0f, camZ));
        cam.setRotation(glm::vec3(0.0f, t2, 0.0f));
        program.setUniform(1, cam.getMatrix());

        program.setUniform(0, transform.getMatrix());
        vao.bind();
        FDGL::drawElements<uint32_t>(FDGL::DrawMode::Triangles, meshes[0]->getNumberOfIndices(), nullptr);
        //glDrawElements(GL_TRIANGLES, meshes[0]->getNumberOfIndices(), GL_UNSIGNED_INT, reinterpret_cast<void*>(0));

        w.swapBuffer();
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
    FD3D::Transform trans;
    cout << trans.getMatrix() << endl;

    trans.setRotation(glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
    cout << glm::degrees(trans.getEulerAngles()) << endl;
    cout << trans.getRotation() << endl;
    cout << trans.getMatrix() << endl;
    trans.rotate(glm::vec3(0.0f, glm::radians(90.0f), 0.0f));
    cout << glm::degrees(trans.getEulerAngles()) << endl;
    cout << trans.getRotation() << endl;
    cout << trans.getMatrix() << endl;

    return draw_mesh(argc, argv);
}
