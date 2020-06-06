#include <FDGL/BaseOpenGLContext.h>

#include <glad/glad.h>

#include <FDGL/OpenGLUtils.h>

#include <iostream>

FDGL::BaseOpenGLContext::BaseOpenGLContext() {}

FDGL::BaseOpenGLContext::~BaseOpenGLContext()
{
    for(auto &r: m_glResources)
        r.value.destroy();
}

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
    enable(GL_DEPTH_TEST);
}

bool FDGL::BaseOpenGLContext::isDepthEnabled() const
{
    return isEnabled(GL_DEPTH_TEST);
}

void FDGL::BaseOpenGLContext::disableDepth()
{
    disable(GL_DEPTH_TEST);
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

void FDGL::BaseOpenGLContext::cullFace(FDGL::CullFace face)
{
    glCullFace(static_cast<GLenum>(face));
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

bool FDGL::BaseOpenGLContext::hasResource(const std::string &key) const
{
    return m_glResources.find(key) != m_glResources.end();
}

const FDGL::OpenGLObjectWrapper FDGL::BaseOpenGLContext::getRessource(const std::string &key) const
{
    auto it = m_glResources.find(key);
    if(it == m_glResources.end())
        return OpenGLObjectWrapper();

    return it->value;
}

void FDGL::BaseOpenGLContext::addRessource(const std::string &key, const OpenGLObjectWrapper &resource)
{
    m_glResources.insert(key, resource);
}

void FDGL::BaseOpenGLContext::setRessource(const std::string &key, const FDGL::OpenGLObjectWrapper &resource)
{
    auto it = m_glResources.find(key);
    if(it == m_glResources.end())
        m_glResources.insert(key, resource);
    else
        it->value = resource;
}

void FDGL::BaseOpenGLContext::removeResource(const std::string &key)
{
    m_glResources.erase(key);
}

FDGL::OpenGLObjectWrapper FDGL::BaseOpenGLContext::getRessource(const std::string &key)
{
    auto it = m_glResources.find(key);
    if(it == m_glResources.end())
        return OpenGLObjectWrapper();

    return it->value;
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
