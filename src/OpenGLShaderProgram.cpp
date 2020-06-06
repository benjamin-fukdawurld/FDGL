#include <FDGL/OpenGLShaderProgram.h>

#include <iostream>
#include <memory>
#include <cstring>

#include <FDCore/FileUtils.h>

FDGL::OpenGLShaderProgramWrapper::OpenGLShaderProgramWrapper(FDGL::OpenGLShaderProgramWrapper &&other) : OpenGLShaderProgramWrapper()
{
    *this = std::move(other);
}

FDGL::OpenGLShaderProgramWrapper::OpenGLShaderProgramWrapper(FDGL::OpenGLObjectWrapper &&other) : OpenGLShaderProgramWrapper()
{
    if(FDGL::is<OpenGLShaderProgramWrapper>(other))
        *this = std::move(other);
}

FDGL::OpenGLShaderProgramWrapper::OpenGLShaderProgramWrapper(std::initializer_list<FDGL::OpenGLShader> l) :
    FDGL::OpenGLShaderProgramWrapper()
{
    create();
    for(auto &shad : l)
        attach(shad);

    if(!link())
    {
        std::cerr << getLinkErrors() << std::endl;
        destroy();
    }
}

FDGL::OpenGLShaderProgramWrapper &FDGL::OpenGLShaderProgramWrapper::operator=(FDGL::OpenGLObjectWrapper &&other)
{
    if(FDGL::is<OpenGLShaderProgramWrapper>(other))
        OpenGLObjectWrapper::operator=(std::move(other));
    return *this;
}

FDGL::OpenGLShaderProgramWrapper &FDGL::OpenGLShaderProgramWrapper::operator=(const FDGL::OpenGLShaderProgramWrapper &other)
{
    OpenGLObjectWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLShaderProgramWrapper &FDGL::OpenGLShaderProgramWrapper::operator=(const FDGL::OpenGLObjectWrapper &other)
{
    if(FDGL::is<OpenGLShaderProgramWrapper>(other))
        OpenGLObjectWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLShaderProgramWrapper &FDGL::OpenGLShaderProgramWrapper::operator=(FDGL::OpenGLShaderProgramWrapper &&other)
{
    OpenGLObjectWrapper::operator=(std::move(other));
    return *this;
}

bool FDGL::OpenGLShaderProgramWrapper::create()
{
    reset(glCreateProgram());
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

size_t FDGL::OpenGLShaderProgramWrapper::getBinarySize()
{
    int size;
    glGetProgramiv(m_id, GL_PROGRAM_BINARY_LENGTH, &size);
    return static_cast<size_t>(size);
}

std::unique_ptr<uint8_t[]> FDGL::OpenGLShaderProgramWrapper::getBinary()
{
    size_t size = getBinarySize();
    std::unique_ptr<uint8_t[]> output(new uint8_t[size + sizeof(GLenum) + sizeof(size_t)]);
    memcpy(output.get(), &size, sizeof(size_t));
    glGetProgramBinary(m_id,
                       static_cast<GLsizei>(size),
                       nullptr,
                       reinterpret_cast<GLenum*>(output.get() + sizeof (size_t)),
                       reinterpret_cast<void*>(output.get() + sizeof (size_t) + sizeof(GLenum)));

    return output;
}

void FDGL::OpenGLShaderProgramWrapper::loadBinary(uint8_t bin[])
{
    size_t *size = reinterpret_cast<size_t*>(bin);
    GLenum *format = reinterpret_cast<GLenum *>(bin + sizeof (size_t));
    void *data = reinterpret_cast<void*>(bin + sizeof (size_t) + sizeof(GLenum));

    glProgramBinary(m_id, *format, data, static_cast<GLsizei>(*size));
}

template<>
bool FDGL::is<FDGL::OpenGLShaderProgramWrapper>(const FDGL::OpenGLObjectWrapper &res)
{
    return glIsProgram(res.getId());
}

template<>
const FDGL::OpenGLShaderProgramWrapper FDGL::as<FDGL::OpenGLShaderProgramWrapper>(const FDGL::OpenGLObjectWrapper &res)
{
    if(is<OpenGLShaderProgramWrapper>(res))
        return FDGL::OpenGLShaderProgramWrapper(res);

    return FDGL::OpenGLShaderProgramWrapper();
}

template<>
FDGL::OpenGLShaderProgramWrapper FDGL::as<FDGL::OpenGLShaderProgramWrapper>(FDGL::OpenGLObjectWrapper &res)
{
    if(is<OpenGLShaderProgramWrapper>(res))
        return FDGL::OpenGLShaderProgramWrapper(res);

    return FDGL::OpenGLShaderProgramWrapper();
}

FDGL::OpenGLShaderProgramWrapper FDGL::operator ""_shad(const char *filePath, size_t)
{
    FDGL::OpenGLShaderProgramWrapper program;
    size_t size;
    std::unique_ptr<uint8_t[]> bin = FDCore::readBinaryFile(filePath, size);
    if(size < (sizeof(size_t) + sizeof(GLenum)))
        return program;

    program.create();
    program.loadBinary(bin.get());

    return program;
}
