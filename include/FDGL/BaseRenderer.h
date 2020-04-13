#ifndef BASERENDERER_H
#define BASERENDERER_H

#include <FDCore/TimeManager.h>
#include <FD3D/SceneGraph/Scene.h>
#include <FDGL/BaseOpenGLContext.h>

#include <glad/glad.h>

namespace FDGL
{
    class BaseRenderer
    {
        protected:
            FDGL::BaseOpenGLContext &m_ctx;
            FD3D::Scene *m_scene;

        public:
            BaseRenderer(FDGL::BaseOpenGLContext &ctx);
            virtual ~BaseRenderer() = default;

            const FDGL::BaseOpenGLContext &getOpenGLContex() const;

            FDGL::BaseOpenGLContext &getOpenGLContex();

            FD3D::Scene *getScene();

            const FD3D::Scene *getScene() const;

            void setScene(FD3D::Scene *scene);

            void onInit(FDGL::BaseOpenGLWindow &w);

            void onQuit(FDGL::BaseOpenGLWindow &w);

            void onRender(FDGL::BaseOpenGLWindow &w);

            void onResize(FDGL::BaseOpenGLWindow &w, int width, int height);

            void onError(FDGL::ErrorSoure source, FDGL::ErrorType type,
                                 uint32_t id, FDGL::ErrorSeverity level,
                                 const std::string &msg) const;


        protected:

            virtual void init(FDGL::BaseOpenGLWindow &w) = 0;

            virtual void quit(FDGL::BaseOpenGLWindow &w) = 0;

            virtual void render(FDGL::BaseOpenGLWindow &w) = 0;

            virtual void resize(FDGL::BaseOpenGLWindow &w, int width, int height) = 0;

            virtual void errorHandler(FDGL::ErrorSoure source, FDGL::ErrorType type,
                                      uint32_t id, FDGL::ErrorSeverity level,
                                      const std::string &msg) const = 0;

            static void debugCallbackHelper(GLenum source,
                                            GLenum type,
                                            GLuint id,
                                            GLenum severity,
                                            GLsizei length,
                                            const GLchar *message,
                                            const void *userParam);
    };

}


#endif // BASERENDERER_H
