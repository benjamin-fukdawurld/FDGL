#ifndef OPENGLFRAMEBUFFER_H
#define OPENGLFRAMEBUFFER_H


#include <FDGL/OpenGLResource.h>
#include <FDGL/OpenGLTexture.h>
#include <FDGL/OpenGLRenderBuffer.h>

#include <FDGL/OpenGLUtils.h>

namespace FDGL
{
    class OpenGLFrameBufferWrapper : public FDGL::OpenGLResourceWrapper
    {
        public:
            explicit OpenGLFrameBufferWrapper(uint32_t id = 0) : OpenGLResourceWrapper(id) {}
            OpenGLFrameBufferWrapper(const OpenGLFrameBufferWrapper &other) : OpenGLResourceWrapper(other) {}
            OpenGLFrameBufferWrapper(const OpenGLResourceWrapper &other) : OpenGLResourceWrapper(other) {}

            OpenGLFrameBufferWrapper(OpenGLFrameBufferWrapper &&other);

            OpenGLFrameBufferWrapper(OpenGLResourceWrapper &&other);

            OpenGLFrameBufferWrapper &operator=(const OpenGLResourceWrapper &other);

            OpenGLFrameBufferWrapper &operator=(OpenGLResourceWrapper &&other);

            OpenGLFrameBufferWrapper &operator=(const OpenGLFrameBufferWrapper &other);

            OpenGLFrameBufferWrapper &operator=(OpenGLFrameBufferWrapper &&other);

            bool create();

            void destroy() override;

            void bind(FDGL::FrameBufferTarget target);
            void unbind(FDGL::FrameBufferTarget target);

            bool isComplete(FrameBufferTarget target) const;

            void attachTexture(OpenGLTextureWrapper tex, FrameBufferAttachment attachment, int level);
            void attachRenderBuffer(OpenGLRenderBufferWrapper rbo, FrameBufferAttachment attachment);
    };

    template<>
    bool is<OpenGLFrameBufferWrapper>(const OpenGLResourceWrapper &res);

    template<>
    const OpenGLFrameBufferWrapper as<OpenGLFrameBufferWrapper>(const OpenGLResourceWrapper &res);

    template<>
    OpenGLFrameBufferWrapper as<OpenGLFrameBufferWrapper>(OpenGLResourceWrapper &res);

    typedef OwnedRessource<OpenGLFrameBufferWrapper> OpenGLFrameBuffer;

    class OpenGLFrameBufferBindGuard
    {
        protected:
            OpenGLFrameBufferWrapper &m_wrapper;
            FrameBufferTarget m_target;

        public:
            OpenGLFrameBufferBindGuard(OpenGLFrameBufferWrapper &wrapper, FrameBufferTarget target) : m_wrapper(wrapper), m_target(target)
            {
                wrapper.bind(m_target);
            }

            ~OpenGLFrameBufferBindGuard()
            {
                m_wrapper.unbind(m_target);
            }

            OpenGLFrameBufferWrapper &getWrapper() const;
            FrameBufferTarget getTarget() const;
    };
}

#endif // OPENGLFRAMEBUFFER_H
