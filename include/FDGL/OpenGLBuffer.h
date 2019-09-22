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

            size_t size() const;
            BufferUsage getUsage() const;

            OpenGLBufferWrapper copy() const;
            void copy(OpenGLBufferWrapper &buffer, size_t readOffset = 0, size_t writeOffset = 0) const
            {
                copy(buffer, readOffset, writeOffset, buffer.size() - writeOffset);
            }

            void copy(OpenGLBufferWrapper &buffer, size_t readOffset, size_t writeOffset, size_t size) const;

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

            OpenGLBufferWrapper &getWrapper();
            const OpenGLBufferWrapper &getWrapper() const;
            BufferTarget getTarget() const;
    };

    template<BufferMappingAccessFlag access = BufferMappingAccessFlag::ReadWrite>
    class OpenGLBufferMap
    {
        protected:
            OpenGLBufferWrapper &m_wrapper;
            void *m_map;
            size_t m_offset;
            size_t m_size;

        public:
            OpenGLBufferMap(OpenGLBufferWrapper &wrapper) :
                m_wrapper(wrapper),
                m_map(nullptr),
                m_offset(0),
                m_size(wrapper.size())
            {
                m_map = glMapNamedBuffer(*m_wrapper, access);
            }

            OpenGLBufferMap(OpenGLBufferWrapper &wrapper, size_t offset, size_t size) :
                m_wrapper(wrapper),
                m_map(nullptr),
                m_offset(offset),
                m_size(size)
            {
                m_map = glMapNamedBufferRange(*m_wrapper, static_cast<GLintptr>(m_offset),
                                              static_cast<GLsizeiptr>(m_size),  access);
            }

            ~OpenGLBufferMap()
            {
                glUnmapNamedBuffer(*m_wrapper);
            }

            void flush()
            {
                glFlushMappedNamedBufferRange(*m_wrapper, m_offset, m_size);
            }

            OpenGLBufferWrapper &getWrapper()
            {
                return m_wrapper;
            }

            size_t size() const
            {
                return m_wrapper.size();
            }

            template<typename T>
            size_t count() const
            {
                return m_wrapper.size() / sizeof(T);
            }

            template<typename T = void>
            T *get(size_t byte_offset)
            {
                return reinterpret_cast<T*>(m_map + byte_offset);
            }

            template<typename T = void>
            const T *get(size_t byte_offset) const
            {
                return reinterpret_cast<T*>(m_map + byte_offset);
            }

            template<typename T>
            T &operator[] (size_t position)
            {
                return *(reinterpret_cast<T*>(m_map) + position);
            }

            template<typename T>
            const T &operator[] (size_t position) const
            {
                return *(reinterpret_cast<T*>(m_map) + position);
            }
    };
}

#endif // BUFFERWRAPPER_H
