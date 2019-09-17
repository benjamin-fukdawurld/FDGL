#include <FDGL/OpenGLShaderProgram.h>

#include <iostream>
#include <memory>

FDGL::OpenGLShaderProgramWrapper::OpenGLShaderProgramWrapper(FDGL::OpenGLShaderProgramWrapper &&other) : OpenGLShaderProgramWrapper()
{
    *this = std::move(other);
}

FDGL::OpenGLShaderProgramWrapper::OpenGLShaderProgramWrapper(FDGL::OpenGLResourceWrapper &&other) : OpenGLShaderProgramWrapper()
{
    if(FDGL::is<OpenGLShaderProgramWrapper>(other))
        *this = std::move(other);
}

FDGL::OpenGLShaderProgramWrapper &FDGL::OpenGLShaderProgramWrapper::operator=(FDGL::OpenGLResourceWrapper &&other)
{
    if(FDGL::is<OpenGLShaderProgramWrapper>(other))
        OpenGLResourceWrapper::operator=(std::move(other));
    return *this;
}

FDGL::OpenGLShaderProgramWrapper &FDGL::OpenGLShaderProgramWrapper::operator=(const FDGL::OpenGLShaderProgramWrapper &other)
{
    OpenGLResourceWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLShaderProgramWrapper &FDGL::OpenGLShaderProgramWrapper::operator=(const FDGL::OpenGLResourceWrapper &other)
{
    if(FDGL::is<OpenGLShaderProgramWrapper>(other))
        OpenGLResourceWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLShaderProgramWrapper &FDGL::OpenGLShaderProgramWrapper::operator=(FDGL::OpenGLShaderProgramWrapper &&other)
{
    OpenGLResourceWrapper::operator=(std::move(other));
    return *this;
}

bool FDGL::OpenGLShaderProgramWrapper::create()
{
    release();
    m_id = glCreateProgram();
    return m_id != 0;
}

void FDGL::OpenGLShaderProgramWrapper::destroy()
{
    glDeleteProgram(m_id);
    m_id = 0;
}

void FDGL::OpenGLShaderProgramWrapper::attach(const FDGL::OpenGLShaderWrapper &shader)
{
    glAttachShader(m_id, *shader);
}

bool FDGL::OpenGLShaderProgramWrapper::link()
{
    int success = 0;
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    return success == GL_TRUE;
}

std::string FDGL::OpenGLShaderProgramWrapper::getLinkErrors() const
{
    std::string result;
    std::unique_ptr<char[]> buffer;
    int size;
    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &size);
    buffer.reset(new char[static_cast<size_t>(size)]{0});

    glGetProgramInfoLog(m_id, size, nullptr, buffer.get());
    result.append(buffer.get(), static_cast<size_t>(size));

    return result;
}

void FDGL::OpenGLShaderProgramWrapper::bind()
{
    glUseProgram(m_id);
}

void FDGL::OpenGLShaderProgramWrapper::unbind()
{
    glUseProgram(0);
}

template<>
bool FDGL::is<FDGL::OpenGLShaderProgramWrapper>(const FDGL::OpenGLResourceWrapper &res)
{
    return glIsProgram(res.getId());
}

template<>
const FDGL::OpenGLShaderProgramWrapper FDGL::as<FDGL::OpenGLShaderProgramWrapper>(const FDGL::OpenGLResourceWrapper &res)
{
    if(is<OpenGLShaderProgramWrapper>(res))
        return FDGL::OpenGLShaderProgramWrapper(res);

    return FDGL::OpenGLShaderProgramWrapper();
}

template<>
FDGL::OpenGLShaderProgramWrapper FDGL::as<FDGL::OpenGLShaderProgramWrapper>(FDGL::OpenGLResourceWrapper &res)
{
    if(is<OpenGLShaderProgramWrapper>(res))
        return FDGL::OpenGLShaderProgramWrapper(res);

    return FDGL::OpenGLShaderProgramWrapper();
}
