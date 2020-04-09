#ifndef SHADERCOMPONENT_H
#define SHADERCOMPONENT_H

#include <FD3D/SceneGraph/Component.h>
#include <FDGL/OpenGLShaderProgram.h>

namespace FDGL
{
    class ShaderComponent : public FD3D::Component
    {
        protected:
            uint32_t m_program;

        public:
            ShaderComponent() :
                ShaderComponent(0)
            {}

            ShaderComponent(uint32_t program);

            ~ShaderComponent() override  = default;

            FDGL::OpenGLShaderProgramWrapper getShaderProgram() const;

            void setShaderProgram(FDGL::OpenGLShaderProgramWrapper program);

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;
    };
}

generateTypeCode(FDGL::ShaderComponent);

#endif // SHADERCOMPONENT_H
