#include "include/FDGL/OpenGLFrameBuffer.h"

template<>
bool FDGL::is<FDGL::OpenGLFrameBufferWrapper>(const OpenGLResourceWrapper &res)
{
    return glIsFramebuffer(res.getId());
}

template<>
const FDGL::OpenGLFrameBufferWrapper FDGL::as<FDGL::OpenGLFrameBufferWrapper>(const FDGL::OpenGLResourceWrapper &res)
{
    if(!is<OpenGLFrameBufferWrapper>(res))
    return OpenGLFrameBufferWrapper();

    return OpenGLFrameBufferWrapper(res.getId());
}

template<>
FDGL::OpenGLFrameBufferWrapper FDGL::as<FDGL::OpenGLFrameBufferWrapper>(FDGL::OpenGLResourceWrapper &res)
{
    if(!is<OpenGLFrameBufferWrapper>(res))
    return OpenGLFrameBufferWrapper();

    return OpenGLFrameBufferWrapper(res.getId());
}

FDGL::OpenGLFrameBufferWrapper::OpenGLFrameBufferWrapper(FDGL::OpenGLFrameBufferWrapper &&other) : OpenGLFrameBufferWrapper()
{
    *this = std::move(other);
}

FDGL::OpenGLFrameBufferWrapper::OpenGLFrameBufferWrapper(FDGL::OpenGLResourceWrapper &&other) : OpenGLFrameBufferWrapper()
{
    if(FDGL::is<OpenGLFrameBufferWrapper>(other))
        *this = std::move(other);
}

FDGL::OpenGLFrameBufferWrapper &FDGL::OpenGLFrameBufferWrapper::operator=(FDGL::OpenGLFrameBufferWrapper &&other)
{
    OpenGLResourceWrapper::operator=(std::move(other));
    return *this;
}

bool FDGL::OpenGLFrameBufferWrapper::create()
{
    release();
    glGenFramebuffers(1, &m_id);

    return m_id != 0;
}

void FDGL::OpenGLFrameBufferWrapper::destroy()
{
    if(m_id == 0)
        return;
    glDeleteFramebuffers(1, &m_id);
    m_id = 0;
}

void FDGL::OpenGLFrameBufferWrapper::bind(FDGL::FrameBufferTarget target)
{
    glBindFramebuffer(static_cast<GLenum>(target), m_id);
}

void FDGL::OpenGLFrameBufferWrapper::unbind(FrameBufferTarget target)
{
    glBindFramebuffer(static_cast<GLenum>(target), 0);
}

bool FDGL::OpenGLFrameBufferWrapper::isComplete(FrameBufferTarget target) const
{
    return glCheckNamedFramebufferStatus(m_id, static_cast<GLenum>(target)) == GL_FRAMEBUFFER_COMPLETE;
}

void FDGL::OpenGLFrameBufferWrapper::attachTexture(OpenGLTextureWrapper tex, FrameBufferAttachment attachment, int level)
{
    glNamedFramebufferTexture(m_id, static_cast<GLenum>(attachment), *tex, level);
}

void FDGL::OpenGLFrameBufferWrapper::attachRenderBuffer(OpenGLRenderBufferWrapper rbo, FrameBufferAttachment attachment)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(attachment), GL_RENDERBUFFER, *rbo);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FDGL::OpenGLFrameBufferWrapper &FDGL::OpenGLFrameBufferWrapper::operator=(const FDGL::OpenGLFrameBufferWrapper &other)
{
    OpenGLResourceWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLFrameBufferWrapper &FDGL::OpenGLFrameBufferWrapper::operator=(FDGL::OpenGLResourceWrapper &&other)
{
    if(FDGL::is<OpenGLFrameBufferWrapper>(other))
        OpenGLResourceWrapper::operator=(std::move(other));

    return *this;
}

FDGL::OpenGLFrameBufferWrapper &FDGL::OpenGLFrameBufferWrapper::operator=(const FDGL::OpenGLResourceWrapper &other)
{
    if(FDGL::is<OpenGLFrameBufferWrapper>(other))
        OpenGLResourceWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLFrameBufferWrapper &FDGL::OpenGLFrameBufferBindGuard::getWrapper() const
{
    return m_wrapper;
}

FDGL::FrameBufferTarget FDGL::OpenGLFrameBufferBindGuard::getTarget() const
{
    return m_target;
}
