#ifndef FDGL_OPENGLOBJECT_H
#define FDGL_OPENGLOBJECT_H

#include <FDGL/OpenGLObjectWrapper.h>

namespace FDGL
{
    template<typename ResourceType>
    class OwnedObject : public ResourceType
    {
        public:
            explicit OwnedObject(uint32_t id = 0): ResourceType(id) {}

            OwnedObject(const OwnedObject &) = delete;

            OwnedObject(ResourceType &&other) { *this = std::move(other); }

            OwnedObject(OwnedObject &&other) { *this = std::move(other); }

            ~OwnedObject() override
            {
                static_cast<ResourceType*>(this)->destroy();
            }

            OwnedObject<ResourceType> &operator=(const OwnedObject &) = delete;

            OwnedObject<ResourceType> &operator=(ResourceType &&other)
            {
                ResourceType &res = static_cast<ResourceType&>(*this);
                res.destroy();
                res = std::move(other);
                return *this;
            }

            OwnedObject<ResourceType> &operator=(OwnedObject &&other)
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

    typedef OwnedObject<OpenGLObjectWrapper> OpenGLObject;
}

#endif // FDGL_OPENGLOBJECT_H
