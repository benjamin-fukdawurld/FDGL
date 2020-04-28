#ifndef ENGINE_H
#define ENGINE_H
#include <pybind11/embed.h>

#include <FDCore/TimeManager.h>
#include <FDCore/AssociativeContainer.h>

#include <FD3D/SceneGraph/Scene.h>

#include "Renderer.h"

class BaseEngine
{
    protected:
        FDGL::BaseOpenGLContext &m_ctx;
        FDGL::BaseOpenGLWindow &m_window;
        FDGL::BaseRenderer &m_renderer;
        FD3D::Scene m_scene;

        FDCore::TimeManager<> m_timeMgr;

    public:
        BaseEngine(FDGL::BaseOpenGLContext &ctx,
                   FDGL::BaseOpenGLWindow &window,
                   FDGL::BaseRenderer &renderer);

        FDGL::BaseOpenGLContext &getContext();

        const FDGL::BaseOpenGLContext &getContext() const;

        FDGL::BaseOpenGLWindow &getWindow();

        const FDGL::BaseOpenGLWindow &getWindow() const;

        FD3D::Scene &getScene();

        const FD3D::Scene &getScene() const;

        FDGL::BaseRenderer &getRenderer();

        const FDGL::BaseRenderer &getRenderer() const;

        FDCore::TimeManager<> &getTimeManager();

        const FDCore::TimeManager<> &getTimeManager() const;
};

class Engine : public BaseEngine
{
    protected:
        FDCore::AssociativeContainer<FD3D::SceneNode::id_type, std::vector<FD3D::Component::id_type>> m_behaviors;


    public:
        using BaseEngine::BaseEngine;

        bool init();

        void quit();

        void processInput(FDGL::BaseOpenGLWindow &window);

        void update();

        void initScene();

        bool loadScene(const std::string &path);
};

#endif // ENGINE_H
