#ifndef OPENGLBUFFER_H
#define OPENGLBUFFER_H

#include <FDGL/OpenGLResource.h>

#include <FDGL/OpenGLUtils.h>

namespace FDGL
{
    class OpenGLBufferWrapper : public FDGL::OpenGLObjectWrapper
    {
        public:
            explicit OpenGLBufferWrapper(uint32_t id = 0) : OpenGLObjectWrapper(id) {}
            OpenGLBufferWrapper(const OpenGLBufferWrapper &other) : OpenGLObjectWrapper(other) {}
            OpenGLBufferWrapper(const OpenGLObjectWrapper &other) : OpenGLObjectWrapper(other) {}

            OpenGLBufferWrapper(OpenGLBufferWrapper &&other);

            OpenGLBufferWrapper(OpenGLObjectWrapper &&other);

            OpenGLBufferWrapper &operator=(const OpenGLObjectWrapper &other);

            OpenGLBufferWrapper &operator=(OpenGLObjectWrapper &&other);

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
                glNamedBufferSubData(m_id, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
                return getLastOpenGLErrors().empty();
            }

            template<typename T>
            bool getData(size_t offset, size_t size, T *data)
            {
                glGetNamedBufferSubData(m_id, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
                return getLastOpenGLErrors().empty();
            }
    };

    template<>
    bool is<OpenGLBufferWrapper>(const OpenGLObjectWrapper &res);

    template<>
    const OpenGLBufferWrapper as<OpenGLBufferWrapper>(const OpenGLObjectWrapper &res);

    template<>
    OpenGLBufferWrapper as<OpenGLBufferWrapper>(OpenGLObjectWrapper &res);

    typedef OwnedObject<OpenGLBufferWrapper> OpenGLBuffer;

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

    template<BufferMappingAccess access = BufferMappingAccess::ReadWrite>
    class OpenGLBufferMappingGuard
    {
        protected:
            void *m_map;
            size_t m_offset;
            size_t m_size;
            uint32_t m_id;

        public:
            OpenGLBufferMappingGuard() :
                m_map(nullptr),
                m_offset(0),
                m_size(0),
                m_id(0)
            {}

            OpenGLBufferMappingGuard(uint32_t id, size_t size, size_t offset = 0) :
                m_map(nullptr),
                m_offset(offset),
                m_size(size),
                m_id(id)
            {
                m_map = glMapNamedBufferRange(m_id, static_cast<GLintptr>(m_offset),
                                              static_cast<GLsizeiptr>(m_size),  static_cast<GLenum>(access));
            }

            OpenGLBufferMappingGuard(const OpenGLBufferMappingGuard<access> &guard) = delete;

            OpenGLBufferMappingGuard(OpenGLBufferMappingGuard<access> &&guard) :
                OpenGLBufferMappingGuard()
            {
                *this = std::move(guard);
            }

            OpenGLBufferMappingGuard &operator=(const OpenGLBufferMappingGuard<access> &guard) = delete;
            OpenGLBufferMappingGuard &operator=(OpenGLBufferMappingGuard<access> &&guard)
            {
                uint32_t id = m_id;
                m_id = guard.m_id;
                m_map = guard.m_map;
                m_offset = guard.m_offset;
                m_size = guard.m_size;
                guard.m_id = id;
            }

            ~OpenGLBufferMappingGuard()
            {
                if(m_id)
                    glUnmapNamedBuffer(m_id);
            }



            void flush()
            {
                if(m_id)
                    glFlushMappedNamedBufferRange(m_id, m_offset, m_size);
            }

            uint32_t getId()
            {
                return m_id;
            }

            OpenGLBufferWrapper getWrapper()
            {
                return { m_id };
            }

            size_t size() const
            {
                if(m_id)
                    return m_size;

                return 0;
            }

            template<typename T>
            size_t count() const
            {
                return size() / sizeof(T);
            }

            template<typename T = void>
            T *get(size_t byte_offset)
            {
                if(m_id)
                    return reinterpret_cast<T*>(m_map + byte_offset);

                return nullptr;
            }

            template<typename T = void>
            const T *get(size_t byte_offset) const
            {
                if(m_id)
                    return reinterpret_cast<T*>(m_map + byte_offset);

                return nullptr;
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

#endif // OPENGLBUFFER_H
