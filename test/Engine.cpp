#include "Engine.h"

#include <FDGL/BufferedMeshComponent.h>
#include <FDGL/OpenGLVertexArray.h>

#include <FD3D/SceneGraph/SceneLoader.h>
#include <FD3D/Behavior/StrategyBehaviorComponent.h>

#include "GLUtils.h"

#include <pybind11/eval.h>


#include <GLFW/glfw3.h>
#include "GLFWImpl.h"

#include "Renderer.h"












bool Engine::init()
{
    m_renderer.setScene(&m_scene);

    if(!m_window.create(800, 600, "Test window"))
        return false;

    m_ctx.setCurrentContext(m_window);
    if (!m_ctx.loadOpenGLFunctions(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        return false;

    m_window.setRenderer(m_renderer);
    m_window.init();
    m_window.setInputStrategy(&Engine::processInput, this);

    initScene();

    return true;
}

void Engine::quit()
{
    m_window.destroy();
}

void Engine::processInput(FDGL::BaseOpenGLWindow &)
{
    Window &w = static_cast<Window&>(m_window);
    if(glfwGetKey(w.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(w.getWindow(), true);

    glfwPollEvents();
}

void Engine::update()
{
    for(auto it = m_behaviors.begin(), end = m_behaviors.end(); it != end; ++it)
    {
        for(auto id: it->value)
        {
            FD3D::Component *comp = m_scene.getComponent(id);
            if(comp)
            {
                FD3D::BehaviorComponent *bvr = comp->as<FD3D::BehaviorComponent>();
                if(bvr)
                    bvr->update();
            }
        }
    }
}

void Engine::initScene()
{
    assert(loadScene("../../FDGL/test/resources/crate/CrateModel.obj"));
    std::vector<FD3D::CameraNode*> cams = m_scene.getNodesAs<FD3D::CameraNode>();
    if(cams.empty())
    {
        std::unique_ptr<FD3D::CameraNode> cam(new FD3D::CameraNode);
        cam->setName("default_camera");
        cam->getEntity()->setPosition(glm::vec3(0.0f, 3.0f, 10.0f));
        cams.push_back(cam.get());
        m_scene.addNode(cam.release());
    }

    static_cast<Renderer&>(m_renderer).setActiveCamera(cams.front()->getEntity());
    static_cast<Renderer&>(m_renderer).initProjection(800, 600);

    std::vector<FD3D::LightNode*> lights = m_scene.getNodesAs<FD3D::LightNode>();
    if(lights.empty())
    {
        std::function<void(FD3D::StrategyBehaviorComponent*)> updateLightFunc = [this](FD3D::StrategyBehaviorComponent *bvr){
            float elapsedTimeInSeconds = m_timeMgr.getElapsedTime() / 1000.0f;

            float radius = 3.0f;
            glm::vec3 &p = bvr->getNode()->as<FD3D::LightNode>()->getEntity()->getPosition();
            p.x = std::sin(elapsedTimeInSeconds) * radius;
            p.z = std::cos(elapsedTimeInSeconds) * radius;
            p.y = std::sin(elapsedTimeInSeconds * 3) * radius;
        };

        std::unique_ptr<FD3D::LightNode> light(new FD3D::LightNode);
        light->setName("default_light");
        FD3D::Light &l = *light->getEntity();
        l.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
        l.setDirection(glm::vec3(0.0f, 0.0f, -1.0f));
        l.setType(FD3D::LightType::DirectionalLight);
        l.setDirection(glm::vec3(1.0f, -1.0f, 0.0f));
        l.attenuation.setConstantAttenuation(5.0f);
        lights.push_back(light.get());

        std::unique_ptr<FD3D::StrategyBehaviorComponent> b(new FD3D::StrategyBehaviorComponent());
        b->setUpdateStrategy(updateLightFunc);
        b->setScene(&m_scene);
        b->setNodeId(light->getId());
        m_scene.addComponent(b.get());
        m_scene.bindComponent(light->getId(), b->getId());
        if(!m_behaviors.contains(light->getId()))
            m_behaviors.insert(light->getId(), {});

        m_behaviors[light->getId()]->push_back(b->getId());
        b.release();

        m_scene.addNode(light.release());
    }

    static_cast<Renderer&>(m_renderer).setLight(lights.front()->getEntity());

    std::vector<FDGL::BufferedMeshComponent*> meshes = m_scene.getComponentsAs<FDGL::BufferedMeshComponent>();
    std::function<void(FD3D::StrategyBehaviorComponent*)> updateFunc = [this](FD3D::StrategyBehaviorComponent *bvr){
        bvr->getNode()->as<FD3D::ObjectNode>()->getEntity()->setRotation(glm::vec3(0, m_timeMgr.getElapsedTime() / 10000.0f, 0));
    };

    for(auto *m: meshes)
    {
        m->setVAOFunctionToDefault();
        auto v = m_scene.getBoundNodes(m->getId());
        for(auto &n: v)
        {
            std::unique_ptr<FD3D::StrategyBehaviorComponent> b(new FD3D::StrategyBehaviorComponent());
            b->setUpdateStrategy(updateFunc);
            b->setScene(&m_scene);
            b->setNodeId(n->getId());
            m_scene.addComponent(b.get());
            m_scene.bindComponent(n->getId(), b->getId());

            if(!m_behaviors.contains(n->getId()))
                m_behaviors.insert(n->getId(), {});

            m_behaviors[n->getId()]->push_back(b->getId());
            b.release();
        }
    }
}

bool Engine::loadScene(const std::string &path)
{
    FDGL::BufferedMeshComponent::setDefaultVAOFunction([](FDGL::BufferedMeshComponent &mesh)
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
        return new FDGL::BufferedMeshComponent();
    });
    return loader.loadScene(m_scene, path, aiProcess_Triangulate);
}

BaseEngine::BaseEngine(FDGL::BaseOpenGLContext &ctx, FDGL::BaseOpenGLWindow &window, FDGL::BaseRenderer &renderer) :
    m_ctx(ctx),
    m_window(window),
    m_renderer(renderer)
{}

FDGL::BaseOpenGLContext &BaseEngine::getContext()
{
    return m_ctx;
}

const FDGL::BaseOpenGLContext &BaseEngine::getContext() const
{
    return m_ctx;
}

FDGL::BaseOpenGLWindow &BaseEngine::getWindow()
{
    return m_window;
}

const FDGL::BaseOpenGLWindow &BaseEngine::getWindow() const
{
    return m_window;
}

FD3D::Scene &BaseEngine::getScene()
{
    return m_scene;
}

const FD3D::Scene &BaseEngine::getScene() const
{
    return m_scene;
}

FDGL::BaseRenderer &BaseEngine::getRenderer()
{
    return m_renderer;
}

const FDGL::BaseRenderer &BaseEngine::getRenderer() const
{
    return m_renderer;
}

FDCore::TimeManager<> &BaseEngine::getTimeManager()
{
    return m_timeMgr;
}

const FDCore::TimeManager<> &BaseEngine::getTimeManager() const
{
    return m_timeMgr;
}
