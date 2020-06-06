#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

#include <FDGL/OpenGLResource.h>

#include <FDGL/OpenGLUtils.h>

#include <string>

namespace FDGL
{
    class OpenGLShaderWrapper : public FDGL::OpenGLObjectWrapper
    {
        public:
            explicit OpenGLShaderWrapper(uint32_t id = 0) : OpenGLObjectWrapper(id) {}
            OpenGLShaderWrapper(const OpenGLShaderWrapper &other) : OpenGLObjectWrapper(other) {}
            OpenGLShaderWrapper(const OpenGLObjectWrapper &other) : OpenGLObjectWrapper(other) {}

            OpenGLShaderWrapper(OpenGLShaderWrapper &&other);

            OpenGLShaderWrapper(OpenGLObjectWrapper &&other);

            OpenGLShaderWrapper &operator=(const OpenGLObjectWrapper &other);

            OpenGLShaderWrapper &operator=(OpenGLObjectWrapper &&other);

            OpenGLShaderWrapper &operator=(const OpenGLShaderWrapper &other);

            OpenGLShaderWrapper &operator=(OpenGLShaderWrapper &&other);

            bool create(ShaderType type);

            void destroy() override;

            void setSource(const std::string &source);

            bool compile();

            std::string getCompileErrors() const;

            static OpenGLShaderWrapper createShader(ShaderType type, const std::string &source, std::string *err = nullptr);
            static OpenGLShaderWrapper loadShader(ShaderType type, const std::string &filePath, std::string *err = nullptr);
    };

    template<>
    bool is<OpenGLShaderWrapper>(const OpenGLObjectWrapper &res);

    template<>
    const OpenGLShaderWrapper as<OpenGLShaderWrapper>(const OpenGLObjectWrapper &res);

    template<>
    OpenGLShaderWrapper as<OpenGLShaderWrapper>(OpenGLObjectWrapper &res);

    typedef OwnedObject<OpenGLShaderWrapper> OpenGLShader;

    OpenGLShaderWrapper operator ""_vert(const char *filePath, size_t);

    OpenGLShaderWrapper operator ""_tesc(const char *filePath, size_t);

    OpenGLShaderWrapper operator ""_tese(const char *filePath, size_t);

    OpenGLShaderWrapper operator ""_geom(const char *filePath, size_t);

    OpenGLShaderWrapper operator ""_frag(const char *filePath, size_t);

    OpenGLShaderWrapper operator ""_comp(const char *filePath, size_t);
}

#endif // OPENGLSHADER_H
