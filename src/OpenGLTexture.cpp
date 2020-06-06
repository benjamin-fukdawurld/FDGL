#include <FDGL/OpenGLTexture.h>

bool FDGL::OpenGLTexture::load()
{
    release();

    FD3D::TextureData data = AbstractTexture::loadFile(getResourcePath());
    if(!data.data)
        return false;

    if(!m_tex.create())
        return FDGL::OpenGLTextureObjectWrapper();

    m_tex.bind(FDGL::TextureTarget::Texture2D);

    m_tex.setWrapModeS(FDGL::TextureWrapMode::Repeat);
    m_tex.setWrapModeT(FDGL::TextureWrapMode::Repeat);

    m_tex.setMinFilter(FDGL::TextureFilter::LinearMipmapLinear);
    m_tex.setMagFilter(FDGL::TextureFilter::Linear);

    GLenum format;
    switch (data.channelsInformation.getNumberOfChannels())
    {
        case 1:
            format = GL_RED;
        break;

        case 2:
            format = GL_RG;
        break;

        case 3:
            format = GL_RGB;
        break;

        case 4:
            format = GL_RGBA;
        break;

        default:
            format = GL_INVALID_ENUM;
        break;
    }

    size_t size[2] = { data.width, data.height };
    m_tex.allocate(FDGL::TextureTarget::Texture2D, 0, static_cast<GLint>(format), size,  format,
                 (data.channelsInformation.isRedFloat() ? GL_FLOAT : GL_UNSIGNED_BYTE), data.data.get());
    m_tex.generateMipMap();

    return true;
}

bool FDGL::OpenGLTexture::isLoaded() const
{
    return m_tex.getId() != 0;
}

void FDGL::OpenGLTexture::release()
{
    m_tex.destroy();
}

const char *FDGL::OpenGLTexture::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FDGL::OpenGLTexture>::code;
}

size_t FDGL::OpenGLTexture::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FDGL::OpenGLTexture>::hash();
}

bool FDGL::OpenGLTexture::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FDGL::OpenGLTexture>::hash()
            || FD3D::AbstractTexture::matchTypeCodeHash(hash);
}

GLenum FDGL::OpenGLTexture::numberOfChannelsToGLFormat(size_t numberOfChannels)
{
    switch (numberOfChannels)
    {
        case 1:
        return GL_RED;

        case 2:
        return GL_RG;

        case 3:
        return GL_RGB;

        case 4:
        return GL_RGBA;

        default:
        return GL_INVALID_ENUM;
    }
}

bool FDGL::OpenGLEmbeddedTexture::load()
{
    release();

    FD3D::TextureData data = AbstractTexture::loadEmbeddedTexture(m_aiTex);
    if(!data.data)
        return false;

    if(!m_tex.create())
        return FDGL::OpenGLTextureObjectWrapper();

    m_tex.bind(FDGL::TextureTarget::Texture2D);

    m_tex.setWrapModeS(FDGL::TextureWrapMode::Repeat);
    m_tex.setWrapModeT(FDGL::TextureWrapMode::Repeat);

    m_tex.setMinFilter(FDGL::TextureFilter::LinearMipmapLinear);
    m_tex.setMagFilter(FDGL::TextureFilter::Linear);

    GLenum format;
    switch (data.channelsInformation.getNumberOfChannels())
    {
        case 1:
            format = GL_RED;
        break;

        case 2:
            format = GL_RG;
        break;

        case 3:
            format = GL_RGB;
        break;

        case 4:
            format = GL_RGBA;
        break;

        default:
            format = GL_INVALID_ENUM;
        break;
    }

    size_t size[2] = { data.width, data.height };
    m_tex.allocate(FDGL::TextureTarget::Texture2D, 0, static_cast<GLint>(format), size,  format,
                 (data.channelsInformation.isRedFloat() ? GL_FLOAT : GL_UNSIGNED_BYTE), data.data.get());
    m_tex.generateMipMap();

    return true;
}

const char *FDGL::OpenGLEmbeddedTexture::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FDGL::OpenGLEmbeddedTexture>::code;
}

size_t FDGL::OpenGLEmbeddedTexture::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FDGL::OpenGLEmbeddedTexture>::hash();
}

bool FDGL::OpenGLEmbeddedTexture::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FDGL::OpenGLEmbeddedTexture>::hash()
            || FDGL::OpenGLTexture::matchTypeCodeHash(hash);
}
