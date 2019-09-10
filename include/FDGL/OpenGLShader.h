#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include <FDGL/OpenGLResource.h>

#include <FDGL/OpenGLUtils.h>

#include <string>

namespace FDGL
{
    class OpenGLShaderWrapper : public FDGL::OpenGLResourceWrapper
    {
        public:
            explicit OpenGLShaderWrapper(uint32_t id = 0) : OpenGLResourceWrapper(id) {}
            OpenGLShaderWrapper(const OpenGLShaderWrapper &other) : OpenGLResourceWrapper(other) {}
            OpenGLShaderWrapper(const OpenGLResourceWrapper &other) : OpenGLResourceWrapper(other) {}

            OpenGLShaderWrapper(OpenGLShaderWrapper &&other);

            OpenGLShaderWrapper(OpenGLResourceWrapper &&other);

            OpenGLShaderWrapper &operator=(const OpenGLResourceWrapper &other);

            OpenGLShaderWrapper &operator=(OpenGLResourceWrapper &&other);

            OpenGLShaderWrapper &operator=(const OpenGLShaderWrapper &other);

            OpenGLShaderWrapper &operator=(OpenGLShaderWrapper &&other);

            bool create(ShaderType type);

            void destroy() override;

            void setSource(const std::string &source);

            bool compile();

            std::string getCompileErrors() const;
    };

    template<>
    bool is<OpenGLShaderWrapper>(const OpenGLResourceWrapper &res);

    template<>
    const OpenGLShaderWrapper as<OpenGLShaderWrapper>(const OpenGLResourceWrapper &res);

    template<>
    OpenGLShaderWrapper as<OpenGLShaderWrapper>(OpenGLResourceWrapper &res);

    typedef OwnedRessource<OpenGLShaderWrapper> OpenGLShader;
}

#endif // OPENGLSHADER_H
