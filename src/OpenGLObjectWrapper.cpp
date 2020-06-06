#include <FDGL/OpenGLObjectWrapper.h>

#include <glad/glad.h>

FDGL::OpenGLObjectWrapper &FDGL::OpenGLObjectWrapper::operator=(FDGL::OpenGLObjectWrapper &&other)
{
    if(this == &other)
        return *this;

    setId(other.m_id);
    other.m_id = 0;
    return *this;
}

FDGL::OpenGLObjectWrapper &FDGL::OpenGLObjectWrapper::operator=(const FDGL::OpenGLObjectWrapper &other)
{
    setId(other.m_id);
    return *this;
}

void FDGL::OpenGLObjectWrapper::destroy()
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

void FDGL::OpenGLObjectWrapper::reset(uint32_t id)
{
    m_id = id;
}

uint32_t FDGL::OpenGLObjectWrapper::release()
{
    uint32_t id = m_id;
    m_id = 0;

    return id;
}

void FDGL::OpenGLObjectWrapper::setId(uint32_t id)
{
    reset(id);
}

void FDGL::OpenGLObjectWrapper::swap(FDGL::OpenGLObjectWrapper &other)
{
    std::swap(m_id, other.m_id);
}
