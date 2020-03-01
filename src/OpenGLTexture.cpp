#include "include/FDGL/OpenGLTexture.h"

#include <glm/gtc/type_ptr.hpp>

template<>
bool FDGL::is<FDGL::OpenGLTextureWrapper>(const OpenGLResourceWrapper &res)
{
    return glIsTexture(res.getId());
}

template<>
const FDGL::OpenGLTextureWrapper FDGL::as<FDGL::OpenGLTextureWrapper>(const FDGL::OpenGLResourceWrapper &res)
{
    if(!is<OpenGLTextureWrapper>(res))
    return OpenGLTextureWrapper();

    return OpenGLTextureWrapper(res.getId());
}

template<>
FDGL::OpenGLTextureWrapper FDGL::as<FDGL::OpenGLTextureWrapper>(FDGL::OpenGLResourceWrapper &res)
{
    if(!is<OpenGLTextureWrapper>(res))
    return OpenGLTextureWrapper();

    return OpenGLTextureWrapper(res.getId());
}

FDGL::OpenGLTextureWrapper::OpenGLTextureWrapper(FDGL::OpenGLTextureWrapper &&other) : OpenGLTextureWrapper()
{
    *this = std::move(other);
}

FDGL::OpenGLTextureWrapper::OpenGLTextureWrapper(FDGL::OpenGLResourceWrapper &&other) : OpenGLTextureWrapper()
{
    if(FDGL::is<OpenGLTextureWrapper>(other))
        *this = std::move(other);
}

FDGL::OpenGLTextureWrapper &FDGL::OpenGLTextureWrapper::operator=(FDGL::OpenGLTextureWrapper &&other)
{
    OpenGLResourceWrapper::operator=(std::move(other));
    return *this;
}

bool FDGL::OpenGLTextureWrapper::create()
{
    release();
    glGenTextures(1, &m_id);

    return m_id != 0;
}

void FDGL::OpenGLTextureWrapper::destroy()
{
    if(m_id == 0)
        return;

    glDeleteTextures(1, &m_id);
    m_id = 0;
}

void FDGL::OpenGLTextureWrapper::bind(FDGL::TextureTarget target)
{
    glBindTexture(static_cast<GLenum>(target), m_id);
}

void FDGL::OpenGLTextureWrapper::unbind(FDGL::TextureTarget target)
{
    glBindBuffer(static_cast<GLenum>(target), 0);
}

void FDGL::OpenGLTextureWrapper::activateTexture(uint8_t texUnit)
{
    if(texUnit <= 15)
        glActiveTexture(GL_TEXTURE0 + texUnit);
    else
        std::cerr << "texture unit must be in range [0, 15] received '" << static_cast<int>(texUnit) << "'" << std::endl;
}

void FDGL::OpenGLTextureWrapper::setWrapModeS(TextureWrapMode mode)
{
    glTexParameteri(m_id, GL_TEXTURE_WRAP_S, static_cast<int>(mode));
}

void FDGL::OpenGLTextureWrapper::setWrapModeT(TextureWrapMode mode)
{
    glTexParameteri(m_id, GL_TEXTURE_WRAP_T, static_cast<int>(mode));
}

void FDGL::OpenGLTextureWrapper::setWrapModeR(TextureWrapMode mode)
{
    glTexParameteri(m_id, GL_TEXTURE_WRAP_R, static_cast<int>(mode));
}

void FDGL::OpenGLTextureWrapper::setBorderColor(const glm::vec4 &color)
{
    glTexParameterfv(m_id, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(color));
}

void FDGL::OpenGLTextureWrapper::setMinFilter(FDGL::TextureFilter filter)
{
    glTexParameteri(m_id, GL_TEXTURE_MIN_FILTER, static_cast<int>(filter));
}

void FDGL::OpenGLTextureWrapper::setMagFilter(FDGL::TextureFilter filter)
{
    glTexParameteri(m_id, GL_TEXTURE_MAG_FILTER, static_cast<int>(filter));
}

void FDGL::OpenGLTextureWrapper::generateMipMap()
{
    glGenerateTextureMipmap(m_id);
}

FDGL::OpenGLTextureWrapper &FDGL::OpenGLTextureWrapper::operator=(const FDGL::OpenGLTextureWrapper &other)
{
    OpenGLResourceWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLTextureWrapper &FDGL::OpenGLTextureWrapper::operator=(FDGL::OpenGLResourceWrapper &&other)
{
    if(FDGL::is<OpenGLTextureWrapper>(other))
        OpenGLResourceWrapper::operator=(std::move(other));

    return *this;
}

FDGL::OpenGLTextureWrapper &FDGL::OpenGLTextureWrapper::operator=(const FDGL::OpenGLResourceWrapper &other)
{
    if(FDGL::is<OpenGLTextureWrapper>(other))
        OpenGLResourceWrapper::operator=(other);
    return *this;
}

FDGL::OpenGLTextureWrapper &FDGL::OpenGLTextureBindGuard::getWrapper() const
{
    return m_wrapper;
}

FDGL::TextureTarget FDGL::OpenGLTextureBindGuard::getTarget() const
{
    return m_target;
}
