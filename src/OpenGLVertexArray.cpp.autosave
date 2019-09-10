#include <FDGL/OpenGLVertexArray.h>

template<>
bool FDGL::is<FDGL::OpenGLVertexArrayWrapper>(const OpenGLResourceWrapper &res)
{
    return glIsBuffer(res.getId());
}

template<>
const FDGL::OpenGLVertexArrayWrapper FDGL::as<FDGL::OpenGLVertexArrayWrapper>(const FDGL::OpenGLResourceWrapper &res)
{
    if(!is<OpenGLVertexArrayWrapper>(res))
    return OpenGLVertexArrayWrapper();

    return OpenGLVertexArrayWrapper(res.getId());
}

template<>
FDGL::OpenGLVertexArrayWrapper FDGL::as<FDGL::OpenGLVertexArrayWrapper>(FDGL::OpenGLResourceWrapper &res)
{
    if(!is<OpenGLVertexArrayWrapper>(res))
    return OpenGLVertexArrayWrapper();

    return OpenGLVertexArrayWrapper(res.getId());
}

FDGL::OpenGLVertexArrayWrapper::OpenGLVertexArrayWrapper(FDGL::OpenGLVertexArrayWrapper &&other) : OpenGLVertexArrayWrapper()
{
    *this = std::move(other);
}

FDGL::OpenGLVertexArrayWrapper::OpenGLVertexArrayWrapper(FDGL::OpenGLResourceWrapper &&other) : OpenGLVertexArrayWrapper()
{
    if(FDGL::is<OpenGLVertexArrayWrapper>(other))
        *this = std::move(other);
}

FDGL::OpenGLVertexArrayWrapper &FDGL::OpenGLVertexArrayWrapper::operator=(FDGL::OpenGLVertexArrayWrapper &&other)
{
    OpenGLResourceWrapper::operator=(std::move(other));
    return *this;
}

bool FDGL::OpenGLVertexArrayWrapper::create()
{
    release();
    glGenBuffers(1, &m_id);

    return m_id != 0;
}

void FDGL::OpenGLVertexArrayWrapper::destroy()
{
    if(m_id == 0)
        return;

    glDeleteBuffers(1, &m_id);
    m_id = 0;
}

void FDGL::OpenGLVertexArrayWrapper::bind(FDGL::BufferTarget target)
{
    glBindBuffer(static_cast<GLenum>(target), m_id);
}

void FDGL::OpenGLVertexArrayWrapper::unbind(FDGL::BufferTarget target)
{
    glBindBuffer(static_cast<GLenum>(target), 0);
}

FDGL::OpenGLVertexArrayWrapper &FDGL::OpenGLVertexArrayWrapper::operator=(const FDGL::OpenGLVertexArrayWrapper &other)
{
    OpenGLResourceWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLVertexArrayWrapper &FDGL::OpenGLVertexArrayWrapper::operator=(FDGL::OpenGLResourceWrapper &&other)
{
    if(FDGL::is<OpenGLVertexArrayWrapper>(other))
        OpenGLResourceWrapper::operator=(std::move(other));

    return *this;
}

FDGL::OpenGLVertexArrayWrapper &FDGL::OpenGLVertexArrayWrapper::operator=(const FDGL::OpenGLResourceWrapper &other)
{
    if(FDGL::is<OpenGLVertexArrayWrapper>(other))
        OpenGLResourceWrapper::operator=(other);
    return *this;
}
