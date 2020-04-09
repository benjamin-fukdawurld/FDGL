#include "Renderer.h"

#include <FDGL/BufferedMesh.h>
#include <FDGL/ShaderComponent.h>

#include <FD3D/SceneGraph/SceneLoader.h>

#include <GLFW/glfw3.h>

#include "GLUtils.h"

Renderer::Renderer(FDGL::BaseOpenGLContext &ctx):
    m_ctx(ctx),
    m_activeCamera(nullptr)
{}

const FDGL::BaseOpenGLContext &Renderer::getOpenGLContex() const
{
    return m_ctx;
}

FDGL::BaseOpenGLContext &Renderer::getOpenGLContex()
{
    return m_ctx;
}

FDCore::TimeManager<> &Renderer::getTimeManager()
{
    return m_timeMgr;
}

const FDCore::TimeManager<> &Renderer::getTimeManager() const
{
    return m_timeMgr;
}

FD3D::Scene &Renderer::getScene()
{
    return m_scene;
}

const FD3D::Scene &Renderer::getScene() const
{
    return m_scene;
}

FD3D::TransformStack &Renderer::getTransformStack()
{
    return m_transformStack;
}

const FD3D::TransformStack &Renderer::getTransformStack() const
{
    return m_transformStack;
}

void Renderer::pushTransform(const FD3D::Transform &trans)
{
    m_transformStack.push(trans);
}

void Renderer::popTransform()
{
    m_transformStack.pop();
}

bool Renderer::hasActiveCamera() const
{
    return m_activeCamera == nullptr;
}

FD3D::Camera *Renderer::getActiveCamera()
{
    return m_activeCamera;
}

const FD3D::Camera *Renderer::getActiveCamera() const
{
    return m_activeCamera;
}

FD3D::Projection *Renderer::getProjection()
{
    return (m_activeCamera == nullptr ?
                nullptr
              : &m_activeCamera->projection);
}

const FD3D::Projection *Renderer::getProjection() const
{
    return (m_activeCamera == nullptr ?
                nullptr
              : &m_activeCamera->projection);
}

void Renderer::setActiveCamera(FD3D::Camera *cam)
{
    m_activeCamera = cam;
}

void Renderer::renderScene()
{
    std::stack<FD3D::SceneNode::id_type> todo;
    std::unordered_map<FD3D::SceneNode::id_type, NodeState> nodeStates;
    todo.push(m_scene.getRootId());
    while(!todo.empty())
    {
        if(nodeStates.find(todo.top()) == nodeStates.end())
            nodeStates[todo.top()] = NodeState::New;

        NodeTransitionGuard current(*this, todo.top(), nodeStates[todo.top()]);
        switch(current.getState())
        {
            case NodeState::New:
                addNodeChildren(current.getId(), todo);
            break;

            case NodeState::Explored:
                renderNode(m_scene.getNode(current.getId()));
            break;

            case NodeState::Rendered:
            case NodeState::Done:
            case NodeState::Invalid:
                todo.pop();
            break;
        }
    }
}

void Renderer::onInit(FDGL::BaseOpenGLWindow &w)
{
    m_timeMgr.start();
    initContext();
    initWindow(w);
    initScene();
    initProjection(w);
    initTextures();
}

void Renderer::onQuit(FDGL::BaseOpenGLWindow &)
{

}

void Renderer::onRender(FDGL::BaseOpenGLWindow &w)
{
    w.clear();

    drawLight();

    //renderScene();

    rotateCamera(m_timeMgr.getElapsedTime() / 1000.0f);

    SceneRenderer r(*this);
    r.renderScene();

    w.swapBuffer();
}

void Renderer::onResize(FDGL::BaseOpenGLWindow &, int width, int height)
{
    getActiveCamera()->projection.setWidth(width);
    getActiveCamera()->projection.setHeight(height);
}

void Renderer::onError(FDGL::ErrorSoure source, FDGL::ErrorType type, uint32_t id, FDGL::ErrorSeverity level, const std::string &msg) const
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

void Renderer::initContext()
{
    m_ctx.enableDepth();
    m_ctx.enableFaceCulling();
    m_ctx.enableDebugOutut();
    glDepthFunc(GL_LESS);
    glDebugMessageCallback(&Renderer::debugCallbackHelper, this);

    FDGL::OpenGLVertexArrayWrapper vao;
    vao.create();
    vao.bind();

    m_ctx.addRessource("default_mesh_shader", createShaderProgram());
    m_ctx.addRessource("default_light_shader", createLightShaderProgram());
    m_ctx.addRessource("attribute_less_vao", vao);
}

void Renderer::initWindow(FDGL::BaseOpenGLWindow &w)
{
    w.setClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
    w.setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::initScene()
{
    assert(loadScene("../../FDGL/test/resources/crate/CrateModel.obj"));
    std::vector<FD3D::CameraNode*> cams = m_scene.getNodesAs<FD3D::CameraNode>();
    if(cams.empty())
    {
        std::unique_ptr<FD3D::CameraNode> cam(new FD3D::CameraNode);
        cam->setName("default_camera");
        cams.push_back(cam.get());
        m_scene.addNode(cam.release());
    }

    m_activeCamera = &cams.front()->getEntity();

    std::vector<FD3D::LightNode*> lights = m_scene.getNodesAs<FD3D::LightNode>();
    if(lights.empty())
    {
        std::unique_ptr<FD3D::LightNode> light(new FD3D::LightNode);
        light->setName("default_light");
        light->getEntity().setType(FD3D::LightType::DirectionalLight);
        light->getEntity().setDirection(glm::vec3(1.0f, -1.0f, 0.0f));
        lights.push_back(light.get());
        m_scene.addNode(light.release());
    }

    m_light = &lights.front()->getEntity();

    std::vector<FDGL::BufferedMesh*> meshes = m_scene.getComponentsAs<FDGL::BufferedMesh>();
    for(auto *m: meshes)
        m->setVAOFunctionToDefault();
}

void Renderer::initProjection(FDGL::BaseOpenGLWindow &w)
{
    FD3D::Projection *proj = getProjection();
    if(proj == nullptr)
        return;

    proj->setFov(glm::radians(45.0f));
    proj->setWidth(w.getWidth());
    proj->setHeight(w.getHeight());
    proj->setNear(0.1f);
    proj->setFar(100.0f);
    proj->setType(FD3D::ProjectionType::Perspective);
}

void Renderer::initTextures()
{
    m_tex = loadTexture("../../FDGL/test/resources/wall.jpg");
}

bool Renderer::loadScene(const std::string &path)
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

void Renderer::renderNode(FD3D::SceneNodeProxy node)
{
    if(!node)
        return;

    std::vector<FDGL::BufferedMesh*> meshes = node.getComponentsAs<FDGL::BufferedMesh>();
    if(meshes.empty())
        return;

    FDGL::OpenGLShaderProgramWrapper program;
    for(size_t i = 0, imax = meshes.size(); i < imax; ++i)
    {
        FDGL::ShaderComponent *shadComp = nullptr;
        if(meshes[i]->hasShader())
        {
            FD3D::Component *comp = m_scene.getComponent(meshes[i]->getShaderId());
            if(!comp)
                shadComp = comp->as<FDGL::ShaderComponent>();
        }

        if(shadComp)
            program = shadComp->getShaderProgram();
        else
            program = m_ctx.getRessource("default_mesh_shader");

        program.bind();
        program.setUniform("texture", 0);
        program.setUniform(0, m_transformStack.getCurrentMatrix());
        program.setUniform(1, getActiveCamera()->getMatrix());
        program.setUniform(2, getProjection()->getMatrix());
        program.setUniform("lightColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        m_tex.activateTexture(0);
        m_tex.bind(FDGL::TextureTarget::Texture2D);

        meshes[i]->getVAO().bind();
        FDGL::drawElements<uint32_t>(FDGL::DrawMode::Triangles, meshes[i]->getNumberOfIndices(), nullptr);
    }
}

void Renderer::addNodeChildren(FD3D::SceneNode::id_type id,
                               std::stack<FD3D::SceneNode::id_type> &todo)
{
    FD3D::SceneNodeProxy node = m_scene.getNode(id);
    std::vector<FD3D::SceneNode::id_type> toAdd = node->getChildIds();
    for(size_t i = 0, imax = toAdd.size(); i < imax; ++i)
        todo.push(toAdd[i]);
}

void Renderer::drawLight()
{
    FDGL::OpenGLShaderProgramWrapper program = FDGL::as<FDGL::OpenGLShaderProgramWrapper>(m_ctx.getRessource("default_light_shader"));
    FDGL::OpenGLVertexArrayWrapper vao = FDGL::as<FDGL::OpenGLVertexArrayWrapper>(m_ctx.getRessource("attribute_less_vao"));
    program.bind();
    program.setUniform("lightPosition", m_light->getPosition());
    program.setUniform(1, getActiveCamera()->getMatrix());
    program.setUniform(2, getProjection()->getMatrix());
    program.setUniform("scale", 0.5f);
    program.setUniform("lightColor", m_light->color.ambient);
    vao.bind();
    FDGL::drawArrays(FDGL::DrawMode::Triangles, 0, 36);
}

void Renderer::debugCallbackHelper(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    const Renderer *r = reinterpret_cast<const Renderer *>(userParam);
    r->onError(static_cast<FDGL::ErrorSoure>(source),
               static_cast<FDGL::ErrorType>(type), id,
               static_cast<FDGL::ErrorSeverity>(severity),
               std::string(message, static_cast<size_t>(length)));
}

void Renderer::rotateCamera(float elapsedTime)
{
    float radius = 10.0f;
    float camX = std::sin(elapsedTime) * radius;
    float camZ = std::cos(elapsedTime) * radius;
    getActiveCamera()->setPosition(glm::vec3(camX, 0.0f, camZ));
    getActiveCamera()->setRotation(glm::vec3(0.0f, elapsedTime, 0.0f));
}

















SceneRenderer::SceneRenderer(Renderer &renderer) :
    m_renderer(renderer)
{}

void SceneRenderer::renderScene()
{
    m_todo.push(m_renderer.getScene().getRootId());
    while(!m_todo.empty())
    {
        NodeTransitionGuard current(*this, m_todo.top());
        State state = current.getState();
        switch(state)
        {
            case State::New:
                m_renderer.addNodeChildren(current.getId(), m_todo);
            break;

            case State::Explored:
                m_renderer.renderNode(m_renderer.getScene().getNode(current.getId()));
            break;

            case State::Rendered:
            case State::Done:
            case State::Invalid:
                m_todo.pop();
            break;
        }
    }
}

FD3D::SceneNodeProxy SceneRenderer::getNode(FD3D::SceneNode::id_type id)
{
    return m_renderer.getScene().getNode(id);
}

void SceneRenderer::pushTransform(const FD3D::Transform &trans)
{
    m_renderer.getTransformStack().push(trans);
}

void SceneRenderer::popTransform()
{
    m_renderer.getTransformStack().pop();
}

SceneRenderer::State SceneRenderer::getNodeState(FD3D::SceneNode::id_type id) const
{
    auto it = m_nodeStates.find(id);
    if(it == m_nodeStates.end())
        return State::New;

    return it->second;
}

void SceneRenderer::setNodeState(FD3D::SceneNode::id_type id, SceneRenderer::State state)
{
    m_nodeStates[id] = state;
}

void SceneRenderer::addNodeChildren(FD3D::SceneNode::id_type id)
{
    FD3D::SceneNodeProxy node = m_renderer.getScene().getNode(id);
    std::vector<FD3D::SceneNode::id_type> toAdd = node->getChildIds();
    for(size_t i = 0, imax = toAdd.size(); i < imax; ++i)
        m_todo.push(toAdd[i]);
}

void SceneRenderer::renderNode(FD3D::SceneNode::id_type)
{

}












SceneRenderer::NodeTransitionGuard::NodeTransitionGuard(SceneRenderer &r, FD3D::SceneNode::id_type id):
    m_renderer(r),
    m_id(id)
{}

SceneRenderer::NodeTransitionGuard::~NodeTransitionGuard()
{
    applyTransition();
}

SceneRenderer &SceneRenderer::NodeTransitionGuard::getRenderer()
{
    return m_renderer;
}

const SceneRenderer &SceneRenderer::NodeTransitionGuard::getRenderer() const
{
    return m_renderer;
}

FD3D::SceneNode::id_type SceneRenderer::NodeTransitionGuard::getId()
{
    return m_id;
}

SceneRenderer::State SceneRenderer::NodeTransitionGuard::getState() const
{
    return m_renderer.getNodeState(m_id);
}

void SceneRenderer::NodeTransitionGuard::applyTransition()
{
    State state = m_renderer.getNodeState(m_id);
    switch (state)
    {
        case State::New:
        {
            FD3D::ObjectNode *obj = m_renderer.getNode(m_id)->as<FD3D::ObjectNode>();
            if(obj != nullptr)
                m_renderer.pushTransform(obj->getEntity());

            m_renderer.setNodeState(m_id, State::Explored);
        }
        break;

        case State::Explored:
        m_renderer.setNodeState(m_id, State::Rendered);
        break;

        case State::Rendered:
        {
            FD3D::ObjectNode *obj = m_renderer.getNode(m_id)->as<FD3D::ObjectNode>();
            if(obj != nullptr)
                m_renderer.popTransform();

            m_renderer.setNodeState(m_id, State::Done);
        }
        break;

        default:
        break;
    }
}
