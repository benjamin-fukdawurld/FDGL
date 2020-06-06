#ifndef OPENGLRESOURCE_H
#define OPENGLRESOURCE_H

#include <FDGL/OpenGLObject.h>
#include <FDCore/BaseResource.h>

#include <cstdint>
#include <utility> // std::move

namespace FDGL
{
    class BaseOpenGLResource : public FDCore::AbstractResource
    {
        private:
            std::string m_resourceName;
            size_t m_resourceHash;

        public:
            BaseOpenGLResource();
            explicit BaseOpenGLResource(std::string_view resourceName);
            BaseOpenGLResource(std::string_view resourceName, std::string_view resourcePath);

            BaseOpenGLResource(BaseOpenGLResource &&res);
            BaseOpenGLResource(const BaseOpenGLResource &res) = delete;

            ~BaseOpenGLResource() override = default;

            std::string_view getResourcePath() const override;
            void setResourcePath(std::string_view) override;

            BaseOpenGLResource &operator=(BaseOpenGLResource &&res);
            BaseOpenGLResource &operator=(const BaseOpenGLResource &res) = delete;


            std::string_view getResourceName() const override;
            void setResourceName(std::string_view resourceName) override;

            size_t getResourceHash() const override;

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;
    };

    template<typename T>
    class OpenGLResource : BaseOpenGLResource
    {
        public:
            typedef T ObjectType;

        protected:
            ObjectType m_obj;

        public:
            using BaseOpenGLResource::BaseOpenGLResource;

            ObjectType &getObject();
            const ObjectType &getObject() const;

            bool load() override
            {
                return m_obj.create();
            }

            bool isLoaded() const override
            {
                return m_obj == true;
            }

            void release() override
            {
                m_obj.destroy();
            }
    };
}

generateTypeCode(FDGL::BaseOpenGLResource);

#endif // OPENGLRESOURCE_H
