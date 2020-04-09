#include "include/FDGL/ShaderComponent.h"


FDGL::ShaderComponent::ShaderComponent(uint32_t program):
    m_program(program)
{}

FDGL::OpenGLShaderProgramWrapper FDGL::ShaderComponent::getShaderProgram() const
{
    return FDGL::OpenGLShaderProgramWrapper(m_program);
}

void FDGL::ShaderComponent::setShaderProgram(FDGL::OpenGLShaderProgramWrapper program)
{
    m_program = program.getId();
}

const char *FDGL::ShaderComponent::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FDGL::ShaderComponent>::code;
}

size_t FDGL::ShaderComponent::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FDGL::ShaderComponent>::hash();
}

bool FDGL::ShaderComponent::matchTypeCodeHash(size_t hash) const
{
    return hash == FDGL::ShaderComponent::getTypeCodeHash() || Component::matchTypeCodeHash(hash);
}
