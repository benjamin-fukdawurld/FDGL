#ifndef OPENGLTEXTUREOBJECTBINDGUARD_H
#define OPENGLTEXTUREOBJECTBINDGUARD_H

#include <FDGL/OpenGLUtils.h>

namespace FDGL
{
    class OpenGLTextureObjectWrapper;

    class OpenGLTextureObjectBindGuard
    {
        protected:
            OpenGLTextureObjectWrapper &m_wrapper;
            TextureTarget m_target;

        public:
            OpenGLTextureObjectBindGuard(OpenGLTextureObjectWrapper &wrapper, TextureTarget target);

            ~OpenGLTextureObjectBindGuard();

            OpenGLTextureObjectWrapper &getWrapper() const;
            TextureTarget getTarget() const;
    };
}

#endif // OPENGLTEXTUREOBJECTBINDGUARD_H
