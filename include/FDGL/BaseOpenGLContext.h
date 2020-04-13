#ifndef BASEOPENGLCONTEXT_H
#define BASEOPENGLCONTEXT_H

#include <cstdint>
#include <functional>

#include <FDCore/AssociativeContainer.h>
#include <FDGL/OpenGLResource.h>
#include <FDGL/OpenGLUtilsForward.h>

namespace FDGL
{
    class BaseOpenGLWindow;

    class BaseOpenGLContext
    {
        public:
            typedef void* (*GetProcAddressFunc) (const char*);

        protected:
            FDCore::AssociativeContainer<std::string, OpenGLResourceWrapper> m_glResources;

        public:
            BaseOpenGLContext();
            virtual ~BaseOpenGLContext();

            void enableDebugOutut();
            void isDebugOutputEnabled() const;
            void disableDebugOutut();

            void enableDepth();
            bool isDepthEnabled() const;
            void disableDepth();

            void enableDepthMask();
            void disableDepthMask();

            void enableBlend();
            bool isBlendEnabled() const;
            void disableBlend();

            void enableFaceCulling();
            bool isFaceCullingEnabled() const;
            void disableFaceCulling();

            void cullFace(FDGL::CullFace face);

            void enableMultiSampling();
            bool isMultiSamplingEnabled() const;
            void disableMultiSampling();

            void enable(uint32_t capability);
            void enable(uint32_t capability, uint32_t index);

            bool isEnabled(uint32_t capability) const;
            bool isEnabled(uint32_t capability, uint32_t index) const;

            void disable(uint32_t capability);
            void disable(uint32_t capability, uint32_t index);

            bool hasResource(const std::string &key) const;
            OpenGLResourceWrapper getRessource(const std::string &key);
            const OpenGLResourceWrapper getRessource(const std::string &key) const;
            void addRessource(const std::string &key, const OpenGLResourceWrapper &resource);
            void setRessource(const std::string &key, const OpenGLResourceWrapper &resource);
            void removeResource(const std::string &key);

            virtual bool loadOpenGLFunctions(GetProcAddressFunc f) const;

            virtual bool init() = 0;
            virtual bool quit() = 0;
            virtual void setCurrentContext(BaseOpenGLWindow &window) = 0;
    };
}

#endif // BASEOPENGLCONTEXT_H
