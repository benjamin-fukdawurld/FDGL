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

size_t FDGL::OpenGLBufferWrapper::size() const
{
    GLint size;
    glGetNamedBufferParameteriv(m_id, GL_BUFFER_SIZE, &size);
    return static_cast<size_t>(size);
}

FDGL::BufferUsage FDGL::OpenGLBufferWrapper::getUsage() const
{
    GLint usage;
    glGetNamedBufferParameteriv(m_id, GL_BUFFER_USAGE, &usage);
    return static_cast<FDGL::BufferUsage>(usage);
}

FDGL::OpenGLBufferWrapper FDGL::OpenGLBufferWrapper::copy() const
{
    FDGL::OpenGLBufferWrapper result;
    size_t s = size();
    result.create();
    result.allocate(s, getUsage());
    copy(result, 0, 0, s);

    return result;
}

void FDGL::OpenGLBufferWrapper::copy(FDGL::OpenGLBufferWrapper &buffer, size_t readOffset, size_t writeOffset, size_t size) const
{
    glCopyNamedBufferSubData(m_id, buffer.m_id,
                             static_cast<GLintptr>(readOffset), static_cast<GLintptr>(writeOffset),
                             static_cast<GLsizeiptr>(size));
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

FDGL::OpenGLBufferWrapper &FDGL::OpenGLBufferBindGuard::getWrapper()
{
    return m_wrapper;
}

const FDGL::OpenGLBufferWrapper &FDGL::OpenGLBufferBindGuard::getWrapper() const
{
    return m_wrapper;
}

FDGL::BufferTarget FDGL::OpenGLBufferBindGuard::getTarget() const
{
    return m_target;
}
