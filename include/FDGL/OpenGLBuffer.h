#ifndef BUFFERWRAPPER_H
#define BUFFERWRAPPER_H

#include <FDGL/OpenGLResource.h>

#include <FDGL/OpenGLUtils.h>

namespace FDGL
{
    class OpenGLBufferWrapper : public FDGL::OpenGLResourceWrapper
    {
        public:
            explicit OpenGLBufferWrapper(uint32_t id = 0) : OpenGLResourceWrapper(id) {}
            OpenGLBufferWrapper(const OpenGLBufferWrapper &other) : OpenGLResourceWrapper(other) {}
            OpenGLBufferWrapper(const OpenGLResourceWrapper &other) : OpenGLResourceWrapper(other) {}

            OpenGLBufferWrapper(OpenGLBufferWrapper &&other);

            OpenGLBufferWrapper(OpenGLResourceWrapper &&other);

            OpenGLBufferWrapper &operator=(const OpenGLResourceWrapper &other);

            OpenGLBufferWrapper &operator=(OpenGLResourceWrapper &&other);

            OpenGLBufferWrapper &operator=(const OpenGLBufferWrapper &other);

            OpenGLBufferWrapper &operator=(OpenGLBufferWrapper &&other);

            bool create();

            void destroy() override;

            void bind(FDGL::BufferTarget target);
            void unbind(FDGL::BufferTarget target);

            bool allocate(size_t size, BufferUsage usage)
            {
                glNamedBufferData(m_id, static_cast<GLsizeiptr>(size), nullptr, static_cast<GLenum>(usage));
                return getLastOpenGLErrors().empty();
            }

            template<typename T>
            bool allocate(size_t size, BufferUsage usage, const T *data)
            {
                glNamedBufferData(m_id, static_cast<GLsizeiptr>(size), data, static_cast<GLenum>(usage));
                return getLastOpenGLErrors().empty();
            }

            template<typename T>
            bool setData(size_t offset, size_t size, const T *data)
            {
                glGetNamedBufferSubData(m_id, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
                return getLastOpenGLErrors().empty();
            }
    };

    template<>
    bool is<OpenGLBufferWrapper>(const OpenGLResourceWrapper &res);

    template<>
    const OpenGLBufferWrapper as<OpenGLBufferWrapper>(const OpenGLResourceWrapper &res);

    template<>
    OpenGLBufferWrapper as<OpenGLBufferWrapper>(OpenGLResourceWrapper &res);

    typedef OwnedRessource<OpenGLBufferWrapper> OpenGLBuffer;

    class OpenGLBufferBindGuard
    {
        protected:
            OpenGLBufferWrapper &m_wrapper;
            BufferTarget m_target;

        public:
            OpenGLBufferBindGuard(OpenGLBufferWrapper &wrapper, BufferTarget target) : m_wrapper(wrapper), m_target(target)
            {
                wrapper.bind(m_target);
            }

            ~OpenGLBufferBindGuard()
            {
                m_wrapper.unbind(m_target);
            }

            OpenGLBufferWrapper &getWrapper() const;
            BufferTarget getTarget() const;
    };
}

#endif // BUFFERWRAPPER_H