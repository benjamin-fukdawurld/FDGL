#ifndef RENDERER_H
#define RENDERER_H

#include <FDCore/TimeManager.h>

#include <FDGL/BaseOpenGLContext.h>
#include <FDGL/BaseOpenGLWindow.h>
#include <FDGL/OpenGLShaderProgram.h>
#include <FDGL/OpenGLTexture.h>
#include <FDGL/OpenGLVertexArray.h>

#include <FD3D/Camera/Camera.h>
#include <FD3D/Light/Light.h>
#include <FD3D/SceneGraph/Scene.h>
#include <FD3D/Utils/TransformStack.h>

#include <stack>
#include <unordered_map>
#include <unordered_set>

class Renderer
{
    private:
        enum class NodeState : int8_t
        {
            Invalid  =-1,
            New = 0,
            Explored,
            Rendered,
            Done
        };

        class NodeTransitionGuard
        {
            private:
                Renderer &m_renderer;
                const FD3D::SceneNode::id_type m_id;
                NodeState &m_state;

            public:
                NodeTransitionGuard(Renderer &r, FD3D::SceneNode::id_type id, NodeState &state):
                    m_renderer(r),
                    m_id(id),
                    m_state(state)
                {}

                ~NodeTransitionGuard()
                {
                    applyTransition();
                }

                Renderer &getRenderer()
                {
                    return m_renderer;
                }

                const Renderer &getRenderer() const
                {
                    return m_renderer;
                }

                FD3D::SceneNode::id_type getId()
                {
                    return m_id;
                }

                NodeState getState() const
                {
                    return m_state;
                }

            private:
                void applyTransition()
                {
                    switch (m_state)
                    {
                        case NodeState::New:
                        {
                            FD3D::ObjectNode *obj = m_renderer.getScene().getNode(m_id)->as<FD3D::ObjectNode>();
                            if(obj != nullptr)
                                m_renderer.pushTransform(obj->getEntity());

                            m_state = NodeState::Explored;
                        }
                        break;

                        case NodeState::Explored:
                        m_state =  NodeState::Rendered;
                        break;

                        case NodeState::Rendered:
                        {
                            FD3D::ObjectNode *obj = m_renderer.getScene().getNode(m_id)->as<FD3D::ObjectNode>();
                            if(obj != nullptr)
                                m_renderer.popTransform();

                            m_state = NodeState::Done;
                        }
                        break;

                        default:
                        break;
                    }
                }
        };

    protected:
        FDGL::BaseOpenGLContext &m_ctx;
        FDCore::TimeManager<> m_timeMgr;
        FD3D::Scene m_scene;
        FD3D::TransformStack m_transformStack;
        FDGL::OpenGLTexture m_tex;
        FD3D::Camera *m_activeCamera;
        FD3D::Light *m_light;

    public:
        Renderer(FDGL::BaseOpenGLContext &ctx);

        ~Renderer() = default;

        const FDGL::BaseOpenGLContext &getOpenGLContex() const;

        FDGL::BaseOpenGLContext &getOpenGLContex();

        FDCore::TimeManager<> &getTimeManager();

        const FDCore::TimeManager<> &getTimeManager() const;

        FD3D::Scene &getScene();
        const FD3D::Scene &getScene() const;

        FD3D::TransformStack &getTransformStack();
        const FD3D::TransformStack &getTransformStack() const;
        void pushTransform(const FD3D::Transform &trans);
        void popTransform();

        bool hasActiveCamera() const;

        FD3D::Camera *getActiveCamera();

        const FD3D::Camera *getActiveCamera() const;

        FD3D::Projection *getProjection();

        const FD3D::Projection *getProjection() const;

        void setActiveCamera(FD3D::Camera *cam);



        void renderScene();
        void renderNode(FD3D::SceneNodeProxy node);
        void addNodeChildren(FD3D::SceneNode::id_type id,
                             std::stack<FD3D::SceneNode::id_type> &todo);



        void onInit(FDGL::BaseOpenGLWindow &w);

        void onQuit(FDGL::BaseOpenGLWindow &);

        void onRender(FDGL::BaseOpenGLWindow &w);

        void onResize(FDGL::BaseOpenGLWindow &, int width, int height);

        void onError(FDGL::ErrorSoure source, FDGL::ErrorType type,
                     uint32_t id, FDGL::ErrorSeverity level,
                     const std::string &msg) const;

    private:

        void initContext();

        void initWindow(FDGL::BaseOpenGLWindow &w);

        void initScene();

        void initProjection(FDGL::BaseOpenGLWindow &w);

        void initTextures();


        bool loadScene(const std::string &path);

        void drawLight();

        static void debugCallbackHelper(GLenum source,
                                        GLenum type,
                                        GLuint id,
                                        GLenum severity,
                                        GLsizei length,
                                        const GLchar *message,
                                        const void *userParam);

        void rotateCamera(float elapsedTime);

};

class SceneRenderer
{
    public:
        enum class State : int8_t
        {
            Invalid  =-1,
            New = 0,
            Explored,
            Rendered,
            Done
        };

    private:
        class NodeTransitionGuard
        {
            private:
                SceneRenderer &m_renderer;
                const FD3D::SceneNode::id_type m_id;

            public:
                NodeTransitionGuard(SceneRenderer &r, FD3D::SceneNode::id_type id);

                ~NodeTransitionGuard();

                SceneRenderer &getRenderer();
                const SceneRenderer &getRenderer() const;
                FD3D::SceneNode::id_type getId();

                State getState() const;

            private:
                void applyTransition();
        };

    private:
        Renderer &m_renderer;
        std::stack<FD3D::SceneNode::id_type> m_todo;
        std::unordered_map<FD3D::SceneNode::id_type, State> m_nodeStates;

    public:
        SceneRenderer(Renderer &renderer);

        void renderScene();

        FD3D::SceneNodeProxy getNode(FD3D::SceneNode::id_type id);

        void pushTransform(const FD3D::Transform &trans);

        void popTransform();

        State getNodeState(FD3D::SceneNode::id_type id) const;

        void setNodeState(FD3D::SceneNode::id_type id, State state);

    private:
        void addNodeChildren(FD3D::SceneNode::id_type id);

        void renderNode(FD3D::SceneNode::id_type id);
};


#endif // RENDERER_H
