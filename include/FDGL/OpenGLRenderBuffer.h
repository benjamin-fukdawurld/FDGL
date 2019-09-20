#ifndef OPENGLRENDERBUFFER_H
#define OPENGLRENDERBUFFER_H

#include <FDGL/OpenGLResource.h>

#include <FDGL/OpenGLUtils.h>

namespace FDGL
{
    class OpenGLRenderBufferWrapper : public FDGL::OpenGLResourceWrapper
    {
        public:
            explicit OpenGLRenderBufferWrapper(uint32_t id = 0) : OpenGLResourceWrapper(id) {}
            OpenGLRenderBufferWrapper(const OpenGLRenderBufferWrapper &other) : OpenGLResourceWrapper(other) {}
            OpenGLRenderBufferWrapper(const OpenGLResourceWrapper &other) : OpenGLResourceWrapper(other) {}

            OpenGLRenderBufferWrapper(OpenGLRenderBufferWrapper &&other);

            OpenGLRenderBufferWrapper(OpenGLResourceWrapper &&other);

            OpenGLRenderBufferWrapper &operator=(const OpenGLResourceWrapper &other);

            OpenGLRenderBufferWrapper &operator=(OpenGLResourceWrapper &&other);

            OpenGLRenderBufferWrapper &operator=(const OpenGLRenderBufferWrapper &other);

            OpenGLRenderBufferWrapper &operator=(OpenGLRenderBufferWrapper &&other);

            bool create();

            void destroy() override;

            void bind();
            void unbind();

            void allocate(GLenum internalformat, size_t width, size_t height);
    };

    template<>
    bool is<OpenGLRenderBufferWrapper>(const OpenGLResourceWrapper &res);

    template<>
    const OpenGLRenderBufferWrapper as<OpenGLRenderBufferWrapper>(const OpenGLResourceWrapper &res);

    template<>
    OpenGLRenderBufferWrapper as<OpenGLRenderBufferWrapper>(OpenGLResourceWrapper &res);

    typedef OwnedRessource<OpenGLRenderBufferWrapper> OpenGLRenderBuffer;
}

#endif // OPENGLRENDERBUFFER_H
