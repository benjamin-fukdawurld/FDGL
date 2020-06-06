#ifndef FDGL_OPENGLTEXTUREOBJECTWRAPPER_H
#define FDGL_OPENGLTEXTUREOBJECTWRAPPER_H

#include <FDGL/OpenGLResource.h>

#include <FDGL/OpenGLUtils.h>

#include <FDGL/OpenGLTextureObjectBindGuard.h>

#include <glm/vec4.hpp>

#include <iostream>

namespace FDGL
{
    class OpenGLTextureObjectWrapper : public FDGL::OpenGLObjectWrapper
    {
        public:
            explicit OpenGLTextureObjectWrapper(uint32_t id = 0) : OpenGLObjectWrapper(id) {}
            OpenGLTextureObjectWrapper(const OpenGLTextureObjectWrapper &other) : OpenGLObjectWrapper(other) {}
            OpenGLTextureObjectWrapper(const OpenGLObjectWrapper &other) : OpenGLObjectWrapper(other) {}

            OpenGLTextureObjectWrapper(OpenGLTextureObjectWrapper &&other);

            OpenGLTextureObjectWrapper(OpenGLObjectWrapper &&other);

            OpenGLTextureObjectWrapper &operator=(const OpenGLObjectWrapper &other);

            OpenGLTextureObjectWrapper &operator=(OpenGLObjectWrapper &&other);

            OpenGLTextureObjectWrapper &operator=(const OpenGLTextureObjectWrapper &other);

            OpenGLTextureObjectWrapper &operator=(OpenGLTextureObjectWrapper &&other);

            bool create();

            void destroy() override;

            void bind(TextureTarget target);
            void unbind(TextureTarget target);

            void activateTexture(uint8_t texUnit = 0);

            void setWrapModeS(TextureWrapMode mode);
            void setWrapModeT(TextureWrapMode mode);
            void setWrapModeR(TextureWrapMode mode);

            void setBorderColor(const glm::vec4 &color);

            void setMinFilter(TextureFilter filter);
            void setMagFilter(TextureFilter filter);

            void generateMipMap();

            template<typename T>
            bool allocate(TextureTarget target,
                         int level,
                         GLint internalFormat,
                         size_t *size,
                         GLenum format,
                         GLenum type,
                         const T *data = nullptr);

            template<typename T>
            bool allocate(TextureTarget target,
                         GLint internalFormat,
                         size_t *size,
                         GLenum format,
                         GLenum type,
                         const T* data = nullptr)
            {
                return allocate(target, 0, internalFormat, size, format, type, data);
            }

            template<typename T>
            bool setData(FDGL::TextureTarget target,
                         GLint internalFormat,
                         int level,
                         size_t *offset,
                         size_t *size,
                         GLenum format,
                         GLenum type,
                         const T* data);

            template<typename T>
            bool setData(FDGL::TextureTarget target,
                         GLint internalFormat,
                         size_t *offset,
                         size_t *size,
                         GLenum format,
                         GLenum type,
                         const T* data)
            {
                return setData(target, internalFormat, 0, offset, size, format, type, data);
            }
    };

    template<typename T>
    bool FDGL::OpenGLTextureObjectWrapper::allocate(FDGL::TextureTarget target,
                                             int level,
                                             GLint internalFormat,
                                             size_t *size,
                                             GLenum format,
                                             GLenum type,
                                             const T *data)
    {
        OpenGLTextureObjectBindGuard guard(*this, target);
        switch(target)
        {
            case TextureTarget::Texture1D:
                glTexImage1D(static_cast<GLenum>(target),
                             level,
                             internalFormat,
                             static_cast<int>(*size),
                             0,
                             format,
                             type,
                             data);
            break;

            case TextureTarget::Texture2D:
            case TextureTarget::Texture1DArray:
            case TextureTarget::TextureRectangle:
            case TextureTarget::TextureCubeMapPosX:
            case TextureTarget::TextureCubeMapNegX:
            case TextureTarget::TextureCubeMapPosY:
            case TextureTarget::TextureCubeMapNegY:
            case TextureTarget::TextureCubeMapPosZ:
            case TextureTarget::TextureCubeMapNegZ:
                glTexImage2D(static_cast<GLenum>(target),
                             level,
                             internalFormat,
                             static_cast<int>(size[0]),
                             static_cast<int>(size[1]),
                             0,
                             format,
                             type,
                             data);
            break;

            case TextureTarget::Texture3D:
            case TextureTarget::Texture2DArray:
                glTexImage3D(static_cast<GLenum>(target),
                             level,
                             internalFormat,
                             static_cast<int>(size[0]),
                             static_cast<int>(size[1]),
                             static_cast<int>(size[2]),
                             0,
                             format,
                             type,
                             data);
            break;

            default:
                std::cerr << __func__ << ": texture target is not supported" << std::endl;
            return false;
        }

        return getLastOpenGLErrors().empty();
    }

    template<typename T>
    bool OpenGLTextureObjectWrapper::setData(FDGL::TextureTarget target,
                                       GLint internalFormat,
                                       int level,
                                       size_t *offset,
                                       size_t *size,
                                       GLenum format,
                                       GLenum type,
                                       const T *data)
    {
        OpenGLTextureObjectBindGuard guard(*this, target);
        switch(target)
        {
            case TextureTarget::Texture1D:
                glTexSubImage1D(static_cast<GLenum>(target),
                                level,
                                internalFormat,
                                static_cast<int>(*offset),
                                static_cast<int>(*size),
                                0,
                                format,
                                type,
                                data);
            break;

            case TextureTarget::Texture2D:
            case TextureTarget::Texture1DArray:
            case TextureTarget::TextureRectangle:
            case TextureTarget::TextureCubeMapPosX:
            case TextureTarget::TextureCubeMapNegX:
            case TextureTarget::TextureCubeMapPosY:
            case TextureTarget::TextureCubeMapNegY:
            case TextureTarget::TextureCubeMapPosZ:
            case TextureTarget::TextureCubeMapNegZ:
                glTexSubImage2D(static_cast<GLenum>(target),
                                level,
                                internalFormat,
                                static_cast<int>(offset[0]),
                                static_cast<int>(offset[1]),
                                static_cast<int>(size[0]),
                                static_cast<int>(size[1]),
                                0,
                                format,
                                type,
                                data);
            break;

            case TextureTarget::Texture3D:
            case TextureTarget::Texture2DArray:
                glTexSubImage3D(static_cast<GLenum>(target),
                                level,
                                internalFormat,
                                static_cast<int>(offset[0]),
                                static_cast<int>(offset[1]),
                                static_cast<int>(offset[2]),
                                static_cast<int>(size[0]),
                                static_cast<int>(size[1]),
                                static_cast<int>(size[2]),
                                0,
                                format,
                                type,
                                data);
            break;

            default:
                std::cerr << __func__ << ": texture target is not supported" << std::endl;
            return false;
        }

        return getLastOpenGLErrors().empty();
    }

    template<>
    bool is<OpenGLTextureObjectWrapper>(const OpenGLObjectWrapper &res);

    template<>
    const OpenGLTextureObjectWrapper as<OpenGLTextureObjectWrapper>(const OpenGLObjectWrapper &res);

    template<>
    OpenGLTextureObjectWrapper as<OpenGLTextureObjectWrapper>(OpenGLObjectWrapper &res);

    typedef OwnedObject<OpenGLTextureObjectWrapper> OpenGLTextureObject;
}

#endif // FDGL_OPENGLTEXTUREOBJECTWRAPPER_H
