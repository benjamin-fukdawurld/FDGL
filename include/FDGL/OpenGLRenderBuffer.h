#ifndef OPENGLRENDERBUFFER_H
#define OPENGLRENDERBUFFER_H

#include <FDGL/OpenGLResource.h>

#include <FDGL/OpenGLUtils.h>

namespace FDGL
{
    class OpenGLRenderBufferWrapper : public FDGL::OpenGLObjectWrapper
    {
        public:
            explicit OpenGLRenderBufferWrapper(uint32_t id = 0) : OpenGLObjectWrapper(id) {}
            OpenGLRenderBufferWrapper(const OpenGLRenderBufferWrapper &other) : OpenGLObjectWrapper(other) {}
            OpenGLRenderBufferWrapper(const OpenGLObjectWrapper &other) : OpenGLObjectWrapper(other) {}

            OpenGLRenderBufferWrapper(OpenGLRenderBufferWrapper &&other);

            OpenGLRenderBufferWrapper(OpenGLObjectWrapper &&other);

            OpenGLRenderBufferWrapper &operator=(const OpenGLObjectWrapper &other);

            OpenGLRenderBufferWrapper &operator=(OpenGLObjectWrapper &&other);

            OpenGLRenderBufferWrapper &operator=(const OpenGLRenderBufferWrapper &other);

            OpenGLRenderBufferWrapper &operator=(OpenGLRenderBufferWrapper &&other);

            bool create();

            void destroy() override;

            void bind();
            void unbind();

            void allocate(GLenum internalformat, size_t width, size_t height);
    };

    template<>
    bool is<OpenGLRenderBufferWrapper>(const OpenGLObjectWrapper &res);

    template<>
    const OpenGLRenderBufferWrapper as<OpenGLRenderBufferWrapper>(const OpenGLObjectWrapper &res);

    template<>
    OpenGLRenderBufferWrapper as<OpenGLRenderBufferWrapper>(OpenGLObjectWrapper &res);

    typedef OwnedObject<OpenGLRenderBufferWrapper> OpenGLRenderBuffer;
}

#endif // OPENGLRENDERBUFFER_H
