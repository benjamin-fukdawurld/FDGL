#include <FDGL/OpenGLTextureObjectBindGuard.h>

#include <FDGL/OpenGLTextureObjectWrapper.h>

FDGL::OpenGLTextureObjectBindGuard::OpenGLTextureObjectBindGuard(FDGL::OpenGLTextureObjectWrapper &wrapper, FDGL::TextureTarget target) : m_wrapper(wrapper), m_target(target)
{
    wrapper.bind(m_target);
}

FDGL::OpenGLTextureObjectBindGuard::~OpenGLTextureObjectBindGuard()
{
    m_wrapper.unbind(m_target);
}

FDGL::OpenGLTextureObjectWrapper &FDGL::OpenGLTextureObjectBindGuard::getWrapper() const
{
    return m_wrapper;
}

FDGL::TextureTarget FDGL::OpenGLTextureObjectBindGuard::getTarget() const
{
    return m_target;
}
