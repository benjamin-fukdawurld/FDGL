#include <FDGL/OpenGLBuffer.h>

template<>
bool FDGL::is<FDGL::OpenGLBufferWrapper>(const OpenGLResourceWrapper &res)
{
    return glIsBuffer(res.getId());
}

template<>
const FDGL::OpenGLBufferWrapper FDGL::as<FDGL::OpenGLBufferWrapper>(const FDGL::OpenGLResourceWrapper &res)
{
    if(!is<OpenGLBufferWrapper>(res))
    return OpenGLBufferWrapper();

    return OpenGLBufferWrapper(res.getId());
}

template<>
FDGL::OpenGLBufferWrapper FDGL::as<FDGL::OpenGLBufferWrapper>(FDGL::OpenGLResourceWrapper &res)
{
    if(!is<OpenGLBufferWrapper>(res))
    return OpenGLBufferWrapper();

    return OpenGLBufferWrapper(res.getId());
}

FDGL::OpenGLBufferWrapper::OpenGLBufferWrapper(FDGL::OpenGLBufferWrapper &&other) : OpenGLBufferWrapper()
{
    *this = std::move(other);
}

FDGL::OpenGLBufferWrapper::OpenGLBufferWrapper(FDGL::OpenGLResourceWrapper &&other) : OpenGLBufferWrapper()
{
    if(FDGL::is<OpenGLBufferWrapper>(other))
        *this = std::move(other);
}

FDGL::OpenGLBufferWrapper &FDGL::OpenGLBufferWrapper::operator=(FDGL::OpenGLBufferWrapper &&other)
{
    OpenGLResourceWrapper::operator=(std::move(other));
    return *this;
}

bool FDGL::OpenGLBufferWrapper::create()
{
    release();
    glGenBuffers(1, &m_id);

    return m_id != 0;
}

void FDGL::OpenGLBufferWrapper::destroy()
{
    if(m_id == 0)
        return;

    glDeleteBuffers(1, &m_id);
    m_id = 0;
}

void FDGL::OpenGLBufferWrapper::bind(FDGL::BufferTarget target)
{
    glBindBuffer(static_cast<GLenum>(target), m_id);
}

void FDGL::OpenGLBufferWrapper::unbind(FDGL::BufferTarget target)
{
    glBindBuffer(static_cast<GLenum>(target), 0);
}

FDGL::OpenGLBufferWrapper &FDGL::OpenGLBufferWrapper::operator=(const FDGL::OpenGLBufferWrapper &other)
{
    OpenGLResourceWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLBufferWrapper &FDGL::OpenGLBufferWrapper::operator=(FDGL::OpenGLResourceWrapper &&other)
{
    if(FDGL::is<OpenGLBufferWrapper>(other))
        OpenGLResourceWrapper::operator=(std::move(other));

    return *this;
}

FDGL::OpenGLBufferWrapper &FDGL::OpenGLBufferWrapper::operator=(const FDGL::OpenGLResourceWrapper &other)
{
    if(FDGL::is<OpenGLBufferWrapper>(other))
        OpenGLResourceWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLBufferWrapper &FDGL::OpenGLBufferBindGuard::getWrapper() const
{
    return m_wrapper;
}

FDGL::BufferTarget FDGL::OpenGLBufferBindGuard::getTarget() const
{
    return m_target;
}
