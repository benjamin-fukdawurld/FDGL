#include <FDGL/BaseOpenGLContext.h>

#include <glad/glad.h>

#include <iostream>

FDGL::BaseOpenGLContext::BaseOpenGLContext() {}

FDGL::BaseOpenGLContext::~BaseOpenGLContext() {}

void FDGL::BaseOpenGLContext::enableDebugOutut()
{
    enable(GL_DEBUG_OUTPUT);
}

void FDGL::BaseOpenGLContext::isDebugOutputEnabled() const
{
    isEnabled(GL_DEBUG_OUTPUT);
}

void FDGL::BaseOpenGLContext::disableDebugOutut()
{
    disable(GL_DEBUG_OUTPUT);
}

void FDGL::BaseOpenGLContext::enableDepth()
{
    enable(GL_DEPTH);
}

bool FDGL::BaseOpenGLContext::isDepthEnabled() const
{
    return isEnabled(GL_DEPTH);
}

void FDGL::BaseOpenGLContext::disableDepth()
{
    disable(GL_DEPTH);
}

void FDGL::BaseOpenGLContext::enableDepthMask()
{
    glDepthMask(GL_TRUE);
}

void FDGL::BaseOpenGLContext::disableDepthMask()
{
    glDepthMask(GL_FALSE);
}

void FDGL::BaseOpenGLContext::enableBlend()
{
    enable(GL_BLEND);
}

bool FDGL::BaseOpenGLContext::isBlendEnabled() const
{
    return isEnabled(GL_BLEND);
}

void FDGL::BaseOpenGLContext::disableBlend()
{
    disable(GL_BLEND);
}

void FDGL::BaseOpenGLContext::enableFaceCulling()
{
    enable(GL_CULL_FACE);
}

bool FDGL::BaseOpenGLContext::isFaceCullingEnabled() const
{
    return isEnabled(GL_CULL_FACE);
}

void FDGL::BaseOpenGLContext::disableFaceCulling()
{
    disable(GL_CULL_FACE);
}

void FDGL::BaseOpenGLContext::enableMultiSampling()
{
    enable(GL_MULTISAMPLE);
}

bool FDGL::BaseOpenGLContext::isMultiSamplingEnabled() const
{
    return isEnabled(GL_MULTISAMPLE);
}

void FDGL::BaseOpenGLContext::disableMultiSampling()
{
    disable(GL_MULTISAMPLE);
}

void FDGL::BaseOpenGLContext::enable(uint32_t capability)
{
    glEnable(static_cast<GLenum>(capability));
}

void FDGL::BaseOpenGLContext::enable(uint32_t capability, uint32_t index)
{
    glEnablei(static_cast<GLenum>(capability), static_cast<GLuint>(index));
}

bool FDGL::BaseOpenGLContext::isEnabled(uint32_t capability) const
{
    return glIsEnabled(static_cast<GLenum>(capability)) == GL_TRUE;
}

bool FDGL::BaseOpenGLContext::isEnabled(uint32_t capability, uint32_t index) const
{
    return glIsEnabledi(static_cast<GLenum>(capability), static_cast<GLuint>(index)) == GL_TRUE;
}

void FDGL::BaseOpenGLContext::disable(uint32_t capability)
{
    glDisable(static_cast<GLenum>(capability));
}

void FDGL::BaseOpenGLContext::disable(uint32_t capability, uint32_t index)
{
    glDisablei(static_cast<GLenum>(capability), static_cast<GLuint>(index));
}

bool FDGL::BaseOpenGLContext::loadOpenGLFunctions(FDGL::BaseOpenGLContext::GetProcAddressFunc f) const
{
    if(!gladLoadGLLoader(f))
    {
        std::cerr << __func__ << ": Failed to load Open GL Functions" << std::endl;
        return false;
    }

    return true;
}
