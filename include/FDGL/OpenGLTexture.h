#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

#include <FDGL/OpenGLTextureObjectWrapper.h>

#include <FD3D/Material/AbstractTexture.h>

namespace FDGL
{
    class OpenGLTexture : public FD3D::AbstractTexture
    {
        protected:
            OpenGLTextureObject m_tex;

        public:
            OpenGLTexture() : OpenGLTexture("") {}
            OpenGLTexture(std::string_view textureName) :
                OpenGLTexture(textureName, "")
            {}

            OpenGLTexture(std::string_view textureName, std::string_view path) :
                AbstractTexture(textureName, path)
            {}

            bool load() override;
            bool isLoaded() const override;
            void release() override;

            OpenGLTextureObject &getOpenGLTexture() { return m_tex; }

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;

            static GLenum numberOfChannelsToGLFormat(size_t numberOfChannels);
    };

    class OpenGLEmbeddedTexture : public OpenGLTexture
    {
        protected:
            aiTexture *m_aiTex;

        public:
            OpenGLEmbeddedTexture() : OpenGLTexture("") {}
            OpenGLEmbeddedTexture(std::string_view textureName) :
                OpenGLEmbeddedTexture(textureName, "")
            {}

            OpenGLEmbeddedTexture(std::string_view textureName, std::string_view path) :
                OpenGLTexture(textureName, path)
            {}

            bool load() override;

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;
    };
}

generateTypeCode(FDGL::OpenGLTexture);
generateTypeCode(FDGL::OpenGLEmbeddedTexture);

#endif // OPENGLTEXTURE_H
