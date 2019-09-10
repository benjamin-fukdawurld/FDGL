#ifndef OPENGLSHADERPROGRAM_H
#define OPENGLSHADERPROGRAM_H

#include <FDGL/OpenGLResource.h>
#include <FDGL/OpenGLShader.h>

#include <FDGL/OpenGLUtils.h>

namespace FDGL
{
    class OpenGLShaderProgramWrapper : public FDGL::OpenGLResourceWrapper
    {
        public:
            explicit OpenGLShaderProgramWrapper(uint32_t id = 0) : OpenGLResourceWrapper(id) {}
            OpenGLShaderProgramWrapper(const OpenGLShaderProgramWrapper &other) : OpenGLResourceWrapper(other) {}
            OpenGLShaderProgramWrapper(const OpenGLResourceWrapper &other) : OpenGLResourceWrapper(other) {}

            OpenGLShaderProgramWrapper(OpenGLShaderProgramWrapper &&other);

            OpenGLShaderProgramWrapper(OpenGLResourceWrapper &&other);

            OpenGLShaderProgramWrapper &operator=(const OpenGLResourceWrapper &other);

            OpenGLShaderProgramWrapper &operator=(OpenGLResourceWrapper &&other);

            OpenGLShaderProgramWrapper &operator=(const OpenGLShaderProgramWrapper &other);

            OpenGLShaderProgramWrapper &operator=(OpenGLShaderProgramWrapper &&other);

            bool create();

            void destroy() override;

            void attach(const OpenGLShaderWrapper &shader);

            bool link();

            std::string getLinkErrors() const;

            void bind();
            void unbind();
    };

    template<>
    bool is<OpenGLShaderProgramWrapper>(const OpenGLResourceWrapper &res);

    template<>
    const OpenGLShaderProgramWrapper as<OpenGLShaderProgramWrapper>(const OpenGLResourceWrapper &res);

    template<>
    OpenGLShaderProgramWrapper as<OpenGLShaderProgramWrapper>(OpenGLResourceWrapper &res);

    typedef OwnedRessource<OpenGLShaderProgramWrapper> OpenGLShaderProgram;
}

#endif // OPENGLSHADERPROGRAM_H
