#ifndef OPENGLSHADERPROGRAM_H
#define OPENGLSHADERPROGRAM_H

#include <initializer_list>
#include <memory>

#include <FDGL/OpenGLResource.h>
#include <FDGL/OpenGLShader.h>

#include <FDGL/OpenGLUtils.h>

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <type_traits>

namespace FDGL
{
    class OpenGLShaderProgramWrapper : public FDGL::OpenGLObjectWrapper
    {
        public:
            explicit OpenGLShaderProgramWrapper(uint32_t id = 0) : OpenGLObjectWrapper(id) {}
            OpenGLShaderProgramWrapper(const OpenGLShaderProgramWrapper &other) : OpenGLObjectWrapper(other) {}
            OpenGLShaderProgramWrapper(const OpenGLObjectWrapper &other) : OpenGLObjectWrapper(other) {}

            OpenGLShaderProgramWrapper(OpenGLShaderProgramWrapper &&other);

            OpenGLShaderProgramWrapper(OpenGLObjectWrapper &&other);

            OpenGLShaderProgramWrapper(std::initializer_list<OpenGLShader> l);

            OpenGLShaderProgramWrapper &operator=(const OpenGLObjectWrapper &other);

            OpenGLShaderProgramWrapper &operator=(OpenGLObjectWrapper &&other);

            OpenGLShaderProgramWrapper &operator=(const OpenGLShaderProgramWrapper &other);

            OpenGLShaderProgramWrapper &operator=(OpenGLShaderProgramWrapper &&other);

            bool create();

            void destroy() override;

            void attach(const OpenGLShaderWrapper &shader);

            bool link();

            std::string getLinkErrors() const;

            void bind();
            void unbind();

            size_t getBinarySize();
            std::unique_ptr<uint8_t[]> getBinary();
            void loadBinary(uint8_t bin[]);

            template<typename T, size_t nb_component, bool normalize = false>
            bool setAttrib(int location, size_t stride, const T *value)
            {
                return FDGL::setAttrib<T, nb_component, normalize>(location, stride, value);
            }

            template<typename ...Args>
            bool setUniform(int location, const Args... values)
            {
                return FDGL::setUniform(location, values...);
            }

            template<typename T, size_t size = 1>
            bool setUniform(int location, size_t count, const T *value)
            {
                return FDGL::setUniform(location, count, value);
            }

            template<typename ...Args>
            bool setUniform(const std::string &name, const Args... values)
            {
                return FDGL::setUniform<Args...>(m_id, name, values...);
            }

            template<typename T, size_t size = 1>
            bool setUniform(const std::string &name, size_t count, const T *value)
            {
                return FDGL::setUniform<T, size>(m_id, name, count, value);
            }

            template<typename T, size_t nb_component, bool normalize = false>
            bool setAttrib(const std::string &name, size_t stride, const T *value)
            {
                return FDGL::setAttrib<T, nb_component, normalize>(m_id, name, stride, value);
            }

            template<GLenum type, size_t nb_component, bool normalize = false>
            bool setAttribFromBuffer(int location, size_t stride, const uintptr_t value)
            {
                return FDGL::setAttribFromBuffer<type, nb_component, normalize>(
                            location, stride, value);
            }

            template<GLenum type, size_t nb_component, bool normalize = false>
            bool setAttribFromBuffer(const std::string &name, size_t stride, const uintptr_t value)
            {
                return FDGL::setAttribFromBuffer<type, nb_component, normalize>(
                            m_id, name, stride, value);
            }
    };

    template<>
    bool is<OpenGLShaderProgramWrapper>(const OpenGLObjectWrapper &res);

    template<>
    const OpenGLShaderProgramWrapper as<OpenGLShaderProgramWrapper>(const OpenGLObjectWrapper &res);

    template<>
    OpenGLShaderProgramWrapper as<OpenGLShaderProgramWrapper>(OpenGLObjectWrapper &res);

    typedef OwnedObject<OpenGLShaderProgramWrapper> OpenGLShaderProgram;

    OpenGLShaderProgramWrapper operator ""_shad(const char *filePath, size_t);
}

#endif // OPENGLSHADERPROGRAM_H
