#include "include/FDGL/OpenGLRenderBuffer.h"

template<>
bool FDGL::is<FDGL::OpenGLRenderBufferWrapper>(const OpenGLObjectWrapper &res)
{
    return glIsRenderbuffer(res.getId());
}

template<>
const FDGL::OpenGLRenderBufferWrapper FDGL::as<FDGL::OpenGLRenderBufferWrapper>(const FDGL::OpenGLObjectWrapper &res)
{
    if(!is<OpenGLRenderBufferWrapper>(res))
    return OpenGLRenderBufferWrapper();

    return OpenGLRenderBufferWrapper(res.getId());
}

template<>
FDGL::OpenGLRenderBufferWrapper FDGL::as<FDGL::OpenGLRenderBufferWrapper>(FDGL::OpenGLObjectWrapper &res)
{
    if(!is<OpenGLRenderBufferWrapper>(res))
    return OpenGLRenderBufferWrapper();

    return OpenGLRenderBufferWrapper(res.getId());
}

FDGL::OpenGLRenderBufferWrapper::OpenGLRenderBufferWrapper(FDGL::OpenGLRenderBufferWrapper &&other) : OpenGLRenderBufferWrapper()
{
    *this = std::move(other);
}

FDGL::OpenGLRenderBufferWrapper::OpenGLRenderBufferWrapper(FDGL::OpenGLObjectWrapper &&other) : OpenGLRenderBufferWrapper()
{
    if(FDGL::is<OpenGLRenderBufferWrapper>(other))
        *this = std::move(other);
}

FDGL::OpenGLRenderBufferWrapper &FDGL::OpenGLRenderBufferWrapper::operator=(FDGL::OpenGLRenderBufferWrapper &&other)
{
    OpenGLObjectWrapper::operator=(std::move(other));
    return *this;
}

bool FDGL::OpenGLRenderBufferWrapper::create()
{
    reset(0);
    glGenRenderbuffers(1, &m_id);

    return m_id != 0;
}

void FDGL::OpenGLRenderBufferWrapper::destroy()
{
    if(m_id == 0)
        return;

    glDeleteRenderbuffers(1, &m_id);
    m_id = 0;
}

void FDGL::OpenGLRenderBufferWrapper::bind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_id);
}

void FDGL::OpenGLRenderBufferWrapper::unbind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void FDGL::OpenGLRenderBufferWrapper::allocate(GLenum internalformat, size_t width, size_t height)
{
    glNamedRenderbufferStorage(m_id, internalformat, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
}

FDGL::OpenGLRenderBufferWrapper &FDGL::OpenGLRenderBufferWrapper::operator=(const FDGL::OpenGLRenderBufferWrapper &other)
{
    OpenGLObjectWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLRenderBufferWrapper &FDGL::OpenGLRenderBufferWrapper::operator=(FDGL::OpenGLObjectWrapper &&other)
{
    if(FDGL::is<OpenGLRenderBufferWrapper>(other))
        OpenGLObjectWrapper::operator=(std::move(other));

    return *this;
}

FDGL::OpenGLRenderBufferWrapper &FDGL::OpenGLRenderBufferWrapper::operator=(const FDGL::OpenGLObjectWrapper &other)
{
    if(FDGL::is<OpenGLRenderBufferWrapper>(other))
        OpenGLObjectWrapper::operator=(other);
    return *this;
}
