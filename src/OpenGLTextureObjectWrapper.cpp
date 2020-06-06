#include <FDGL/OpenGLTextureObjectWrapper.h>


#include <glm/gtc/type_ptr.hpp>

template<>
bool FDGL::is<FDGL::OpenGLTextureObjectWrapper>(const OpenGLObjectWrapper &res)
{
    return glIsTexture(res.getId());
}

template<>
const FDGL::OpenGLTextureObjectWrapper FDGL::as<FDGL::OpenGLTextureObjectWrapper>(const FDGL::OpenGLObjectWrapper &res)
{
    if(!is<OpenGLTextureObjectWrapper>(res))
    return OpenGLTextureObjectWrapper();

    return OpenGLTextureObjectWrapper(res.getId());
}

template<>
FDGL::OpenGLTextureObjectWrapper FDGL::as<FDGL::OpenGLTextureObjectWrapper>(FDGL::OpenGLObjectWrapper &res)
{
    if(!is<OpenGLTextureObjectWrapper>(res))
    return OpenGLTextureObjectWrapper();

    return OpenGLTextureObjectWrapper(res.getId());
}

FDGL::OpenGLTextureObjectWrapper::OpenGLTextureObjectWrapper(FDGL::OpenGLTextureObjectWrapper &&other) : OpenGLTextureObjectWrapper()
{
    *this = std::move(other);
}

FDGL::OpenGLTextureObjectWrapper::OpenGLTextureObjectWrapper(FDGL::OpenGLObjectWrapper &&other) : OpenGLTextureObjectWrapper()
{
    if(FDGL::is<OpenGLTextureObjectWrapper>(other))
        *this = std::move(other);
}

FDGL::OpenGLTextureObjectWrapper &FDGL::OpenGLTextureObjectWrapper::operator=(FDGL::OpenGLTextureObjectWrapper &&other)
{
    OpenGLObjectWrapper::operator=(std::move(other));
    return *this;
}

bool FDGL::OpenGLTextureObjectWrapper::create()
{
    reset(0);
    glGenTextures(1, &m_id);

    return m_id != 0;
}

void FDGL::OpenGLTextureObjectWrapper::destroy()
{
    if(m_id == 0)
        return;

    glDeleteTextures(1, &m_id);
    m_id = 0;
}

void FDGL::OpenGLTextureObjectWrapper::bind(FDGL::TextureTarget target)
{
    glBindTexture(static_cast<GLenum>(target), m_id);
}

void FDGL::OpenGLTextureObjectWrapper::unbind(FDGL::TextureTarget target)
{
    glBindTexture(static_cast<GLenum>(target), 0);
}

void FDGL::OpenGLTextureObjectWrapper::activateTexture(uint8_t texUnit)
{
    if(texUnit <= 15)
        glActiveTexture(GL_TEXTURE0 + texUnit);
    else
        std::cerr << "texture unit must be in range [0, 15] received '" << static_cast<int>(texUnit) << "'" << std::endl;
}

void FDGL::OpenGLTextureObjectWrapper::setWrapModeS(TextureWrapMode mode)
{
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, static_cast<int>(mode));
}

void FDGL::OpenGLTextureObjectWrapper::setWrapModeT(TextureWrapMode mode)
{
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, static_cast<int>(mode));
}

void FDGL::OpenGLTextureObjectWrapper::setWrapModeR(TextureWrapMode mode)
{
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, static_cast<int>(mode));
}

void FDGL::OpenGLTextureObjectWrapper::setBorderColor(const glm::vec4 &color)
{
    glTextureParameterfv(m_id, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(color));
}

void FDGL::OpenGLTextureObjectWrapper::setMinFilter(FDGL::TextureFilter filter)
{
    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, static_cast<int>(filter));
}

void FDGL::OpenGLTextureObjectWrapper::setMagFilter(FDGL::TextureFilter filter)
{
    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, static_cast<int>(filter));
}

void FDGL::OpenGLTextureObjectWrapper::generateMipMap()
{
    glGenerateTextureMipmap(m_id);
}

FDGL::OpenGLTextureObjectWrapper &FDGL::OpenGLTextureObjectWrapper::operator=(const FDGL::OpenGLTextureObjectWrapper &other)
{
    OpenGLObjectWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLTextureObjectWrapper &FDGL::OpenGLTextureObjectWrapper::operator=(FDGL::OpenGLObjectWrapper &&other)
{
    if(FDGL::is<OpenGLTextureObjectWrapper>(other))
        OpenGLObjectWrapper::operator=(std::move(other));

    return *this;
}

FDGL::OpenGLTextureObjectWrapper &FDGL::OpenGLTextureObjectWrapper::operator=(const FDGL::OpenGLObjectWrapper &other)
{
    if(FDGL::is<OpenGLTextureObjectWrapper>(other))
        OpenGLObjectWrapper::operator=(other);
    return *this;
}
