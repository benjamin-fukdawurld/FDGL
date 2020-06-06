#ifndef OPENGLFRAMEBUFFER_H
#define OPENGLFRAMEBUFFER_H


#include <FDGL/OpenGLResource.h>
#include <FDGL/OpenGLTexture.h>
#include <FDGL/OpenGLRenderBuffer.h>

#include <FDGL/OpenGLUtils.h>

namespace FDGL
{
    class OpenGLFrameBufferWrapper : public FDGL::OpenGLObjectWrapper
    {
        public:
            explicit OpenGLFrameBufferWrapper(uint32_t id = 0) : OpenGLObjectWrapper(id) {}
            OpenGLFrameBufferWrapper(const OpenGLFrameBufferWrapper &other) : OpenGLObjectWrapper(other) {}
            OpenGLFrameBufferWrapper(const OpenGLObjectWrapper &other) : OpenGLObjectWrapper(other) {}

            OpenGLFrameBufferWrapper(OpenGLFrameBufferWrapper &&other);

            OpenGLFrameBufferWrapper(OpenGLObjectWrapper &&other);

            OpenGLFrameBufferWrapper &operator=(const OpenGLObjectWrapper &other);

            OpenGLFrameBufferWrapper &operator=(OpenGLObjectWrapper &&other);

            OpenGLFrameBufferWrapper &operator=(const OpenGLFrameBufferWrapper &other);

            OpenGLFrameBufferWrapper &operator=(OpenGLFrameBufferWrapper &&other);

            bool create();

            void destroy() override;

            void bind(FDGL::FrameBufferTarget target);
            void unbind(FDGL::FrameBufferTarget target);

            bool isComplete(FrameBufferTarget target) const;

            void attachTexture(OpenGLTextureObjectWrapper tex, FrameBufferAttachment attachment, int level);
            void attachRenderBuffer(OpenGLRenderBufferWrapper rbo, FrameBufferAttachment attachment);
    };

    template<>
    bool is<OpenGLFrameBufferWrapper>(const OpenGLObjectWrapper &res);

    template<>
    const OpenGLFrameBufferWrapper as<OpenGLFrameBufferWrapper>(const OpenGLObjectWrapper &res);

    template<>
    OpenGLFrameBufferWrapper as<OpenGLFrameBufferWrapper>(OpenGLObjectWrapper &res);

    typedef OwnedObject<OpenGLFrameBufferWrapper> OpenGLFrameBuffer;

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
