#include <FDGL/BaseRenderer.h>

FDGL::BaseRenderer::BaseRenderer(FDGL::BaseOpenGLContext &ctx) :
    m_ctx(ctx),
    m_scene(nullptr)
{}

const FDGL::BaseOpenGLContext &FDGL::BaseRenderer::getOpenGLContex() const
{
    return m_ctx;
}

FDGL::BaseOpenGLContext &FDGL::BaseRenderer::getOpenGLContex()
{
    return m_ctx;
}

FD3D::Scene *FDGL::BaseRenderer::getScene()
{
    return m_scene;
}

const FD3D::Scene *FDGL::BaseRenderer::getScene() const
{
    return m_scene;
}

void FDGL::BaseRenderer::setScene(FD3D::Scene *scene)
{
    m_scene = scene;
}

void FDGL::BaseRenderer::onInit(FDGL::BaseOpenGLWindow &w)
{
    init(w);
}

void FDGL::BaseRenderer::onQuit(FDGL::BaseOpenGLWindow &w)
{
    quit(w);
}

void FDGL::BaseRenderer::onRender(FDGL::BaseOpenGLWindow &w)
{
    render(w);
}

void FDGL::BaseRenderer::onResize(FDGL::BaseOpenGLWindow &w, int width, int height)
{
    resize(w, width, height);
}

void FDGL::BaseRenderer::onError(FDGL::ErrorSoure source,
                                 FDGL::ErrorType type,
                                 uint32_t id,
                                 FDGL::ErrorSeverity level,
                                 const std::string &msg) const
{
    errorHandler(source, type, id, level, msg);
}

void FDGL::BaseRenderer::debugCallbackHelper(GLenum source,
                                             GLenum type,
                                             GLuint id,
                                             GLenum severity,
                                             GLsizei length,
                                             const GLchar *message,
                                             const void *userParam)
{
    const BaseRenderer *r = reinterpret_cast<const BaseRenderer *>(userParam);
    r->onError(static_cast<FDGL::ErrorSoure>(source),
               static_cast<FDGL::ErrorType>(type), id,
               static_cast<FDGL::ErrorSeverity>(severity),
               std::string(message, static_cast<size_t>(length)));
}
