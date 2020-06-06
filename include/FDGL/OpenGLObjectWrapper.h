#ifndef FDGL_OPENGLOBJECTWRAPPER_H
#define FDGL_OPENGLOBJECTWRAPPER_H

#include <cstdint>
#include <utility> // std::move

namespace FDGL
{
    class OpenGLObjectWrapper
    {
        protected:
            uint32_t m_id;

        public:
            explicit OpenGLObjectWrapper(uint32_t id = 0) : m_id(id) {}
            OpenGLObjectWrapper(const OpenGLObjectWrapper &other) : m_id(other.m_id) {}
            OpenGLObjectWrapper(OpenGLObjectWrapper &&other) : OpenGLObjectWrapper()
            {
                *this = std::move(other);
            }

            OpenGLObjectWrapper &operator=(const OpenGLObjectWrapper &other);

            OpenGLObjectWrapper &operator=(OpenGLObjectWrapper &&other);

            virtual ~OpenGLObjectWrapper() = default;

            virtual void destroy();
            virtual void reset(uint32_t id);
            virtual uint32_t release();

            uint32_t getId() const { return m_id; }
            virtual void setId(uint32_t id);
            virtual void swap(OpenGLObjectWrapper &other);

            operator bool() const { return m_id != 0; }
            uint32_t operator*() const { return m_id; }
            uint32_t *get() { return &m_id; }
            const uint32_t *get() const { return &m_id; }

            bool operator==(uint32_t id) const { return m_id == id; }
            bool operator!=(uint32_t id) const { return m_id != id; }
            bool operator==(const OpenGLObjectWrapper &other) const { return *this == other.m_id; }
            bool operator!=(const OpenGLObjectWrapper &other) const { return *this != other.m_id; }
            bool operator==(std::nullptr_t) const { return m_id == 0; }
            bool operator!=(std::nullptr_t) const { return m_id != 0; }
    };

    template<typename T>
    bool is(const OpenGLObjectWrapper &)
    {
        return false;
    }

    template<typename T>
    const T as(const OpenGLObjectWrapper &)
    {
        return T();
    }

    template<typename T>
    T as(OpenGLObjectWrapper &)
    {
        return T();
    }
}

#endif // FDGL_OPENGLOBJECTWRAPPER_H
