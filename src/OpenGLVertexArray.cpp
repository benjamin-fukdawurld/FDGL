#include <FDGL/OpenGLVertexArray.h>

#include <glad/glad.h>


FDGL::OpenGLVertexArrayWrapper::OpenGLVertexArrayWrapper(FDGL::OpenGLVertexArrayWrapper &&other)
{
    *this = std::move(other);
}

FDGL::OpenGLVertexArrayWrapper::OpenGLVertexArrayWrapper(FDGL::OpenGLResourceWrapper &&other)
{
    if(FDGL::is<FDGL::OpenGLVertexArrayWrapper>(other))
    *this = std::move(other);
}

FDGL::OpenGLVertexArrayWrapper &FDGL::OpenGLVertexArrayWrapper::operator=(const FDGL::OpenGLResourceWrapper &other)
{
    if(FDGL::is<OpenGLVertexArrayWrapper>(other))
        OpenGLResourceWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLVertexArrayWrapper &FDGL::OpenGLVertexArrayWrapper::operator=(FDGL::OpenGLResourceWrapper &&other)
{
    if(FDGL::is<OpenGLVertexArrayWrapper>(other))
        OpenGLResourceWrapper::operator=(std::move(other));
    return *this;
}

FDGL::OpenGLVertexArrayWrapper &FDGL::OpenGLVertexArrayWrapper::operator=(const FDGL::OpenGLVertexArrayWrapper &other)
{
    OpenGLResourceWrapper::operator=(std::move(other));
    return *this;
}

FDGL::OpenGLVertexArrayWrapper &FDGL::OpenGLVertexArrayWrapper::operator=(FDGL::OpenGLVertexArrayWrapper &&other)
{
    OpenGLResourceWrapper::operator=(std::move(other));
    return *this;
}

bool FDGL::OpenGLVertexArrayWrapper::create()
{
    glGenVertexArrays(1, &m_id);
    return m_id != 0;
}

void FDGL::OpenGLVertexArrayWrapper::destroy()
{
    if(m_id == 0)
        return;

    glDeleteVertexArrays(1, &m_id);
    m_id = 0;
}

void FDGL::OpenGLVertexArrayWrapper::bind()
{
    glBindVertexArray(m_id);
}

void FDGL::OpenGLVertexArrayWrapper::unbind()
{
    glBindVertexArray(0);
}

template<>
bool FDGL::is<FDGL::OpenGLVertexArrayWrapper>(const FDGL::OpenGLResourceWrapper &res)
{
    return glIsVertexArray(res.getId());
}

template<>
const FDGL::OpenGLVertexArrayWrapper FDGL::as<FDGL::OpenGLVertexArrayWrapper>(const FDGL::OpenGLResourceWrapper &res)
{
    if(FDGL::is<FDGL::OpenGLVertexArrayWrapper>(res))
        return FDGL::OpenGLVertexArrayWrapper(res);

    return FDGL::OpenGLVertexArrayWrapper();
}

template<>
FDGL::OpenGLVertexArrayWrapper FDGL::as<FDGL::OpenGLVertexArrayWrapper>(FDGL::OpenGLResourceWrapper &res)
{
    if(FDGL::is<FDGL::OpenGLVertexArrayWrapper>(res))
        return FDGL::OpenGLVertexArrayWrapper(res);

    return FDGL::OpenGLVertexArrayWrapper();
}
