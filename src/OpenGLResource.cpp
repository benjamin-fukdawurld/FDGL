#include <FDGL/OpenGLResource.h>

#include <cassert>
#include <glad/glad.h>

FDGL::BaseOpenGLResource::BaseOpenGLResource() :
    BaseOpenGLResource("")
{}

FDGL::BaseOpenGLResource::BaseOpenGLResource(std::string_view resourceName):
    AbstractResource(),
    m_resourceName(resourceName),
    m_resourceHash(std::hash<std::string>()(m_resourceName))
{}

FDGL::BaseOpenGLResource::BaseOpenGLResource(FDGL::BaseOpenGLResource &&res):
    m_resourceName(std::move(res.m_resourceName)),
    m_resourceHash(res.m_resourceHash)
{}

std::string_view FDGL::BaseOpenGLResource::getResourcePath() const { return ""; }

void FDGL::BaseOpenGLResource::setResourcePath(std::string_view)
{
    static_assert("OpenGLResource has no path");
}

FDGL::BaseOpenGLResource &FDGL::BaseOpenGLResource::operator=(FDGL::BaseOpenGLResource &&res)
{
    release();
    m_resourceHash = res.m_resourceHash;
    m_resourceName = std::move(res.m_resourceName);
    return *this;
}

std::string_view FDGL::BaseOpenGLResource::getResourceName() const
{
    return m_resourceName;
}

void FDGL::BaseOpenGLResource::setResourceName(std::string_view resourceName)
{
    m_resourceName = resourceName;
    m_resourceHash = std::hash<std::string>()(m_resourceName);
}

size_t FDGL::BaseOpenGLResource::getResourceHash() const
{
    return  m_resourceHash;
}

const char *FDGL::BaseOpenGLResource::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FDGL::BaseOpenGLResource>::code;
}

size_t FDGL::BaseOpenGLResource::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FDGL::BaseOpenGLResource>::hash();
}

bool FDGL::BaseOpenGLResource::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FDGL::BaseOpenGLResource>::hash()
            || FDCore::AbstractResource::matchTypeCodeHash(hash);
}
