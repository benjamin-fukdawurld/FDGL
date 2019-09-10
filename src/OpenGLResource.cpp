#include <FDGL/OpenGLResource.h>

#include <glad/glad.h>

FDGL::OpenGLResourceWrapper &FDGL::OpenGLResourceWrapper::operator=(FDGL::OpenGLResourceWrapper &&other)
{
    if(this == &other)
        return *this;

    setId(other.m_id);
    other.m_id = 0;
    return *this;
}

FDGL::OpenGLResourceWrapper &FDGL::OpenGLResourceWrapper::operator=(const FDGL::OpenGLResourceWrapper &other)
{
    setId(other.m_id);
    return *this;
}

FDGL::OpenGLResourceWrapper::~OpenGLResourceWrapper()
{

}

void FDGL::OpenGLResourceWrapper::destroy()
{
    if(m_id == 0)
        return;

    if(glIsBuffer(m_id))
        glDeleteBuffers(1, &m_id);
    else if(glIsProgram(m_id))
        glDeleteProgram(m_id);
    else if(glIsShader(m_id))
        glDeleteShader(m_id);
    else if(glIsSampler(m_id))
        glDeleteSamplers(1, &m_id);
    else if(glIsTexture(m_id))
        glDeleteTextures(1, &m_id);
    else if(glIsFramebuffer(m_id))
        glDeleteFramebuffers(1, &m_id);
    else if (glIsVertexArray(m_id))
        glDeleteVertexArrays(1, &m_id);
    else if(glIsRenderbuffer(m_id))
        glDeleteRenderbuffers(1, &m_id);
}

void FDGL::OpenGLResourceWrapper::release()
{
    m_id = 0;
}

void FDGL::OpenGLResourceWrapper::setId(uint32_t id)
{
    release();
    m_id = id;
}

void FDGL::OpenGLResourceWrapper::swap(FDGL::OpenGLResourceWrapper &other)
{
    std::swap(m_id, other.m_id);
}
