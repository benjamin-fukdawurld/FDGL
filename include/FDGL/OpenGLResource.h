#ifndef OPENGLRESOURCE_H
#define OPENGLRESOURCE_H

#include <cstdint>
#include <utility> // std::move

namespace FDGL
{
    class OpenGLResourceWrapper
    {
        protected:
            uint32_t m_id;

        public:
            explicit OpenGLResourceWrapper(uint32_t id = 0) : m_id(id) {}
            OpenGLResourceWrapper(const OpenGLResourceWrapper &other) : m_id(other.m_id) {}
            OpenGLResourceWrapper(OpenGLResourceWrapper &&other) : OpenGLResourceWrapper()
            {
                *this = std::move(other);
            }

            OpenGLResourceWrapper &operator=(const OpenGLResourceWrapper &other);

            OpenGLResourceWrapper &operator=(OpenGLResourceWrapper &&other);

            virtual ~OpenGLResourceWrapper();

            virtual void destroy();
            virtual void reset(uint32_t id);
            virtual uint32_t release();

            uint32_t getId() const { return m_id; }
            virtual void setId(uint32_t id);
            virtual void swap(OpenGLResourceWrapper &other);

            operator bool() const { return m_id != 0; }
            uint32_t operator*() const { return m_id; }
            uint32_t *get() { return &m_id; }
            const uint32_t *get() const { return &m_id; }

            bool operator==(uint32_t id) const { return m_id == id; }
            bool operator!=(uint32_t id) const { return m_id != id; }
            bool operator==(const OpenGLResourceWrapper &other) const { return *this == other.m_id; }
            bool operator!=(const OpenGLResourceWrapper &other) const { return *this != other.m_id; }
            bool operator==(std::nullptr_t) const { return m_id == 0; }
            bool operator!=(std::nullptr_t) const { return m_id != 0; }
    };

    template<typename ResourceType>
    class OwnedRessource : public ResourceType
    {
        public:
            explicit OwnedRessource(uint32_t id = 0): ResourceType(id) {}

            OwnedRessource(const OwnedRessource &) = delete;

            OwnedRessource(ResourceType &&other) { *this = std::move(other); }

            OwnedRessource(OwnedRessource &&other) { *this = std::move(other); }

            ~OwnedRessource() override
            {
                static_cast<ResourceType*>(this)->destroy();
            }

            OwnedRessource<ResourceType> &operator=(const OwnedRessource &) = delete;

            OwnedRessource<ResourceType> &operator=(ResourceType &&other)
            {
                ResourceType &res = static_cast<ResourceType&>(*this);
                res.destroy();
                res = std::move(other);
                return *this;
            }

            OwnedRessource<ResourceType> &operator=(OwnedRessource &&other)
            {
                static_cast<ResourceType*>(this)->swap(other); // if m_id != 0 the ressource wil be released.
                return *this;
            }

            void reset(uint32_t id) override
            {
                ResourceType::destroy();
                ResourceType::reset(id);
            }
    };

    typedef OwnedRessource<OpenGLResourceWrapper> OpenGLResource;

    template<typename T>
    bool is(const OpenGLResourceWrapper &)
    {
        return false;
    }

    template<typename T>
    const T as(const OpenGLResourceWrapper &)
    {
        return T();
    }

    template<typename T>
    T as(OpenGLResourceWrapper &)
    {
        return T();
    }
}

#endif // OPENGLRESOURCE_H
