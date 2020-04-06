#include <FDGL/OpenGLShader.h>

#include <FDCore/FileUtils.h>

#include <iostream>
#include <memory>

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
    reset(0);
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
    return success == GL_TRUE;
}

std::string FDGL::OpenGLShaderWrapper::getCompileErrors() const
{
    std::string result;
    std::unique_ptr<char[]> buffer;
    int size;
    glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &size);
    buffer.reset(new char[static_cast<size_t>(size)]{0});

    glGetShaderInfoLog(m_id, size, nullptr, buffer.get());
    result.append(buffer.get(), static_cast<size_t>(size));

    return result;
}

FDGL::OpenGLShaderWrapper FDGL::OpenGLShaderWrapper::createShader(FDGL::ShaderType type, const std::string &source, std::string *err)
{
    FDGL::OpenGLShaderWrapper shader;
    shader.create(type);
    shader.setSource(source);
    if(!shader.compile())
    {
        if(err)
            *err = shader.getCompileErrors();

        shader.destroy();
    }

    return shader;
}

FDGL::OpenGLShaderWrapper FDGL::OpenGLShaderWrapper::loadShader(FDGL::ShaderType type, const std::string &filePath, std::string *err)
{
    std::unique_ptr<char[]> source = FDCore::readFile(filePath);
    return createShader(type, source.get(), err);
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

FDGL::OpenGLShaderWrapper FDGL::operator ""_vert(const char *filePath, size_t)
{
    std::string err;
    auto shad = OpenGLShaderWrapper::loadShader(ShaderType::Vertex, filePath, &err);
    if(!err.empty())
        std::cerr << err << std::endl;

    return shad;
}

FDGL::OpenGLShaderWrapper FDGL::operator ""_tesc(const char *filePath, size_t)
{
    std::string err;
    auto shad = OpenGLShaderWrapper::loadShader(ShaderType::TesselationControl, filePath, &err);
    if(!err.empty())
        std::cerr << err << std::endl;

    return shad;
}

FDGL::OpenGLShaderWrapper FDGL::operator ""_tese(const char *filePath, size_t)
{
    std::string err;
    auto shad = OpenGLShaderWrapper::loadShader(ShaderType::TesselationEvaluation, filePath, &err);
    if(!err.empty())
        std::cerr << err << std::endl;

    return shad;
}

FDGL::OpenGLShaderWrapper FDGL::operator ""_geom(const char *filePath, size_t)
{
    std::string err;
    auto shad = OpenGLShaderWrapper::loadShader(ShaderType::Geometry, filePath, &err);
    if(!err.empty())
        std::cerr << err << std::endl;

    return shad;
}

FDGL::OpenGLShaderWrapper FDGL::operator ""_frag(const char *filePath, size_t)
{
    std::string err;
    auto shad = OpenGLShaderWrapper::loadShader(ShaderType::Fragment, filePath, &err);
    if(!err.empty())
        std::cerr << err << std::endl;

    return shad;
}

FDGL::OpenGLShaderWrapper FDGL::operator ""_comp(const char *filePath, size_t)
{
    std::string err;
    auto shad = OpenGLShaderWrapper::loadShader(ShaderType::Compute, filePath, &err);
    if(!err.empty())
        std::cerr << err << std::endl;

    return shad;
}
