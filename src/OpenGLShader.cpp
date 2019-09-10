#include <FDGL/OpenGLShader.h>

FDGL::OpenGLShaderWrapper::OpenGLShaderWrapper(FDGL::OpenGLShaderWrapper &&other) : OpenGLShaderWrapper()
{
    *this = std::move(other);
}

FDGL::OpenGLShaderWrapper::OpenGLShaderWrapper(FDGL::OpenGLResourceWrapper &&other) : OpenGLShaderWrapper()
{
    if(FDGL::is<OpenGLShaderWrapper>(other))
        *this = std::move(other);
}

FDGL::OpenGLShaderWrapper &FDGL::OpenGLShaderWrapper::operator=(FDGL::OpenGLResourceWrapper &&other)
{
    if(FDGL::is<OpenGLShaderWrapper>(other))
        OpenGLResourceWrapper::operator=(std::move(other));

    return *this;
}

FDGL::OpenGLShaderWrapper &FDGL::OpenGLShaderWrapper::operator=(const FDGL::OpenGLShaderWrapper &other)
{
    OpenGLResourceWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLShaderWrapper &FDGL::OpenGLShaderWrapper::operator=(const FDGL::OpenGLResourceWrapper &other)
{
    if(FDGL::is<OpenGLShaderWrapper>(other))
        OpenGLResourceWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLShaderWrapper &FDGL::OpenGLShaderWrapper::operator=(FDGL::OpenGLShaderWrapper &&other)
{
    OpenGLResourceWrapper::operator=(std::move(other));
    return *this;
}

bool FDGL::OpenGLShaderWrapper::create(ShaderType type)
{
    release();
    m_id = glCreateShader(static_cast<GLenum>(type));
    return m_id != 0;
}

void FDGL::OpenGLShaderWrapper::destroy()
{
    if(m_id == 0)
        return;

    glDeleteShader(m_id);
    m_id = 0;
}

void FDGL::OpenGLShaderWrapper::setSource(const std::string &source)
{
    const char *src = source.c_str();
    glShaderSource(m_id, 1, &src, nullptr);
}

bool FDGL::OpenGLShaderWrapper::compile()
{
    glCompileShader(m_id);
    int  success;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    return success != 0;
}

std::string FDGL::OpenGLShaderWrapper::getCompileErrors() const
{
    std::string result;
    char buffer[1024];
    int size;
    do
    {
        glGetShaderInfoLog(m_id, 1024, &size, buffer);
        result.append(buffer, static_cast<size_t>(size));
    } while(size > 0);

    return result;
}

template<>
bool FDGL::is<FDGL::OpenGLShaderWrapper>(const FDGL::OpenGLResourceWrapper &res)
{
    return glIsShader(res.getId());
}

template<>
const FDGL::OpenGLShaderWrapper FDGL::as<FDGL::OpenGLShaderWrapper>(const FDGL::OpenGLResourceWrapper &res)
{
    if(is<OpenGLShaderWrapper>(res))
        return FDGL::OpenGLShaderWrapper(res);

    return FDGL::OpenGLShaderWrapper();
}

template<>
FDGL::OpenGLShaderWrapper FDGL::as<FDGL::OpenGLShaderWrapper>(FDGL::OpenGLResourceWrapper &res)
{
    if(is<OpenGLShaderWrapper>(res))
        return FDGL::OpenGLShaderWrapper(res);

    return FDGL::OpenGLShaderWrapper();
}
