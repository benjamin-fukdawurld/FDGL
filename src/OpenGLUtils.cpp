#include <FDGL/OpenGLUtils.h>

#include <glm/gtc/type_ptr.hpp>

std::vector<GLenum> FDGL::getLastOpenGLErrors()
{
    std::vector<GLenum> result;
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
        result.push_back(err);

    return result;
}

template<>
bool FDGL::setUniform<double>(int location, const double &value)
{
    glUniform1d(location, value);
    return true;
}

template<>
bool FDGL::setUniform<float>(int location, const float &value)
{
    glUniform1f(location, value);
    return true;
}

template<>
bool FDGL::setUniform<int>(int location, const int &value)
{
    glUniform1i(location, value);
    return true;
}

template<>
bool FDGL::setUniform<uint>(int location, const uint &value)
{
    glUniform1ui(location, value);
    return true;
}

template<>
bool FDGL::setUniform<double>(int location, const double &value1, const double &value2)
{
    glUniform2d(location, value1, value2);
    return true;
}

template<>
bool FDGL::setUniform<float>(int location, const float &value1, const float &value2)
{
    glUniform2f(location, value1, value2);
    return true;
}

template<>
bool FDGL::setUniform<int>(int location, const int &value1, const int &value2)
{
    glUniform2i(location, value1, value2);
    return true;
}

template<>
bool FDGL::setUniform<uint>(int location, const uint &value1, const uint &value2)
{
    glUniform2ui(location, value1, value2);
    return true;
}

template<>
bool FDGL::setUniform<double>(int location, const double &value1, const double &value2, const double &value3)
{
    glUniform3d(location, value1, value2, value3);
    return true;
}

template<>
bool FDGL::setUniform<float>(int location, const float &value1, const float &value2, const float &value3)
{
    glUniform3f(location, value1, value2, value3);
    return true;
}

template<>
bool FDGL::setUniform<int>(int location, const int &value1, const int &value2, const int &value3)
{
    glUniform3i(location, value1, value2, value3);
    return true;
}

template<>
bool FDGL::setUniform<uint>(int location, const uint &value1, const uint &value2, const uint &value3)
{
    glUniform3ui(location, value1, value2, value3);
    return true;
}

template<>
bool FDGL::setUniform<double>(int location, const double &value1, const double &value2, const double &value3, const double &value4)
{
    glUniform4d(location, value1, value2, value3, value4);
    return true;
}

template<>
bool FDGL::setUniform<float>(int location, const float &value1, const float &value2, const float &value3, const float &value4)
{
    glUniform4f(location, value1, value2, value3, value4);
    return true;
}

template<>
bool FDGL::setUniform<int>(int location, const int &value1, const int &value2, const int &value3, const int &value4)
{
    glUniform4i(location, value1, value2, value3, value4);
    return true;
}

template<>
bool FDGL::setUniform<uint>(int location, const uint &value1, const uint &value2, const uint &value3, const uint &value4)
{
    glUniform4ui(location, value1, value2, value3, value4);
    return true;
}

template<>
bool FDGL::setUniform<double, 1>(int location, size_t count, const double *value)
{
    glUniform1dv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<double, 2>(int location, size_t count, const double *value)
{
    glUniform2dv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<double, 3>(int location, size_t count, const double *value)
{
    glUniform3dv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<double, 4>(int location, size_t count, const double *value)
{
    glUniform4dv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<float, 1>(int location, size_t count, const float *value)
{
    glUniform1fv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<float, 2>(int location, size_t count, const float *value)
{
    glUniform2fv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<float, 3>(int location, size_t count, const float *value)
{
    glUniform3fv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<float, 4>(int location, size_t count, const float *value)
{
    glUniform4fv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<int, 1>(int location, size_t count, const int *value)
{
    glUniform1iv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<int, 2>(int location, size_t count, const int *value)
{
    glUniform2iv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<int, 3>(int location, size_t count, const int *value)
{
    glUniform3iv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<int, 4>(int location, size_t count, const int *value)
{
    glUniform4iv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<uint, 1>(int location, size_t count, const uint *value)
{
    glUniform1uiv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<uint, 2>(int location, size_t count, const uint *value)
{
    glUniform2uiv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<uint, 3>(int location, size_t count, const uint *value)
{
    glUniform3uiv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<uint, 4>(int location, size_t count, const uint *value)
{
    glUniform4uiv(location, static_cast<GLsizei>(count), value);
    return true;
}

template<>
bool FDGL::setUniform<glm::vec2>(int location, size_t count, const glm::vec2 *value)
{
    glUniform2fv(location, static_cast<GLsizei>(count), glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setUniform<glm::vec3>(int location, size_t count, const glm::vec3 *value)
{
    glUniform3fv(location, static_cast<GLsizei>(count), glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setUniform<glm::vec4>(int location, size_t count, const glm::vec4 *value)
{
    glUniform4fv(location, static_cast<GLsizei>(count), glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat2>(int location, size_t count, const glm::mat2 *value)
{
    glUniformMatrix2fv(location, static_cast<GLsizei>(count), false, glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat2x3>(int location, size_t count, const glm::mat2x3 *value)
{
    glUniformMatrix2x3fv(location, static_cast<GLsizei>(count), false, glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat2x4>(int location, size_t count, const glm::mat2x4 *value)
{
    glUniformMatrix2x4fv(location, static_cast<GLsizei>(count), false, glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat3>(int location, size_t count, const glm::mat3 *value)
{
    glUniformMatrix3fv(location, static_cast<GLsizei>(count), false, glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat3x2>(int location, size_t count, const glm::mat3x2 *value)
{
    glUniformMatrix3x2fv(location, static_cast<GLsizei>(count), false, glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat3x4>(int location, size_t count, const glm::mat3x4 *value)
{
    glUniformMatrix3x4fv(location, static_cast<GLsizei>(count), false, glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat4>(int location, size_t count, const glm::mat4 *value)
{
    glUniformMatrix4fv(location, static_cast<GLsizei>(count), false, glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat4x2>(int location, size_t count, const glm::mat4x2 *value)
{
    glUniformMatrix4x2fv(location, static_cast<GLsizei>(count), false, glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat4x3>(int location, size_t count, const glm::mat4x3 *value)
{
    glUniformMatrix4x3fv(location, static_cast<GLsizei>(count), false, glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setUniform<glm::vec2>(int location, const glm::vec2 &value)
{
    glUniform2fv(location, 1, glm::value_ptr(value));
    return true;
}

template<>
bool FDGL::setUniform<glm::vec3>(int location, const glm::vec3 &value)
{
    glUniform3fv(location, 1, glm::value_ptr(value));
    return true;
}

template<>
bool FDGL::setUniform<glm::vec4>(int location, const glm::vec4 &value)
{
    glUniform4fv(location, 1, glm::value_ptr(value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat2>(int location, const glm::mat2 &value)
{
    glUniformMatrix2fv(location, 1, false, glm::value_ptr(value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat2x3>(int location, const glm::mat2x3 &value)
{
    glUniformMatrix2x3fv(location, 1, false, glm::value_ptr(value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat2x4>(int location, const glm::mat2x4 &value)
{
    glUniformMatrix2x4fv(location, 1, false, glm::value_ptr(value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat3>(int location, const glm::mat3 &value)
{
    glUniformMatrix3fv(location, 1, false, glm::value_ptr(value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat3x2>(int location, const glm::mat3x2 &value)
{
    glUniformMatrix3x2fv(location, 1, false, glm::value_ptr(value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat3x4>(int location, const glm::mat3x4 &value)
{
    glUniformMatrix3x4fv(location, 1, false, glm::value_ptr(value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat4>(int location, const glm::mat4 &value)
{
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat4x2>(int location, const glm::mat4x2 &value)
{
    glUniformMatrix4x2fv(location, 1, false, glm::value_ptr(value));
    return true;
}

template<>
bool FDGL::setUniform<glm::mat4x3>(int location, const glm::mat4x3 &value)
{
    glUniformMatrix4x3fv(location, 1, false, glm::value_ptr(value));
    return true;
}

template<>
bool FDGL::setAttrib<float, 1, false>(int location, size_t stride, const float *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 1,
                           GL_FLOAT, false, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<float, 2, false>(int location, size_t stride, const float *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 2,
                           GL_FLOAT, false, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<float, 3, false>(int location, size_t stride, const float *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 3,
                           GL_FLOAT, false, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<float, 4, false>(int location, size_t stride, const float *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 4,
                           GL_FLOAT, false, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<float, 1, true>(int location, size_t stride, const float *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 1,
                           GL_FLOAT, true, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<float, 2, true>(int location, size_t stride, const float *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 2,
                           GL_FLOAT, true, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<float, 3, true>(int location, size_t stride, const float *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 3,
                           GL_FLOAT, true, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<float, 4, true>(int location, size_t stride, const float *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 4,
                           GL_FLOAT, true, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<int8_t, 1, false>(int location, size_t stride, const int8_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 1,
                           GL_BYTE, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<int8_t, 2, false>(int location, size_t stride, const int8_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 2,
                           GL_BYTE, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<int8_t, 3, false>(int location, size_t stride, const int8_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 3,
                           GL_BYTE, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<int8_t, 4, false>(int location, size_t stride, const int8_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 4,
                           GL_BYTE, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<uint8_t, 1, false>(int location, size_t stride, const uint8_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 1,
                           GL_UNSIGNED_BYTE, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<uint8_t, 2, false>(int location, size_t stride, const uint8_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 2,
                           GL_UNSIGNED_BYTE, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<uint8_t, 3, false>(int location, size_t stride, const uint8_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 3,
                           GL_UNSIGNED_BYTE, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<uint8_t, 4, false>(int location, size_t stride, const uint8_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 4,
                           GL_UNSIGNED_BYTE, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<int16_t, 1, false>(int location, size_t stride, const int16_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 1,
                           GL_SHORT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<int16_t, 2, false>(int location, size_t stride, const int16_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 2,
                           GL_SHORT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<int16_t, 3, false>(int location, size_t stride, const int16_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 3,
                           GL_SHORT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<int16_t, 4, false>(int location, size_t stride, const int16_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 4,
                           GL_SHORT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<uint16_t, 1, false>(int location, size_t stride, const uint16_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 1,
                           GL_UNSIGNED_SHORT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<uint16_t, 2, false>(int location, size_t stride, const uint16_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 2,
                           GL_UNSIGNED_SHORT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<uint16_t, 3, false>(int location, size_t stride, const uint16_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 3,
                           GL_UNSIGNED_SHORT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<uint16_t, 4, false>(int location, size_t stride, const uint16_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 4,
                           GL_UNSIGNED_SHORT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<int32_t, 1, false>(int location, size_t stride, const int32_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 1,
                           GL_INT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<int32_t, 2, false>(int location, size_t stride, const int32_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 2,
                           GL_INT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<int32_t, 3, false>(int location, size_t stride, const int32_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 3,
                           GL_INT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<int32_t, 4, false>(int location, size_t stride, const int32_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 4,
                           GL_INT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<uint32_t, 1, false>(int location, size_t stride, const uint32_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 1,
                           GL_UNSIGNED_INT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<uint32_t, 2, false>(int location, size_t stride, const uint32_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 2,
                           GL_UNSIGNED_INT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<uint32_t, 3, false>(int location, size_t stride, const uint32_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 3,
                           GL_UNSIGNED_INT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<uint32_t, 4, false>(int location, size_t stride, const uint32_t *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 4,
                           GL_UNSIGNED_INT, static_cast<GLsizei>(stride), value);
    return true;
}

template<>
bool FDGL::setAttrib<glm::vec2, 2, false>(int location, size_t stride, const glm::vec2 *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 2,
                           GL_FLOAT, false, static_cast<GLsizei>(stride), glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setAttrib<glm::vec3, 3, false>(int location, size_t stride, const glm::vec3 *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 3,
                           GL_FLOAT, false, static_cast<GLsizei>(stride), glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setAttrib<glm::vec4, 4, false>(int location, size_t stride, const glm::vec4 *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 4,
                           GL_FLOAT, false, static_cast<GLsizei>(stride), glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setAttrib<glm::vec2, 2, true>(int location, size_t stride, const glm::vec2 *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 2,
                           GL_FLOAT, true, static_cast<GLsizei>(stride), glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setAttrib<glm::vec3, 3, true>(int location, size_t stride, const glm::vec3 *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 3,
                           GL_FLOAT, true, static_cast<GLsizei>(stride), glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setAttrib<glm::vec4, 4, true>(int location, size_t stride, const glm::vec4 *value)
{
    glVertexAttribPointer(static_cast<uint>(location), 4,
                           GL_FLOAT, true, static_cast<GLsizei>(stride), glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setAttrib<glm::ivec2, 2, false>(int location, size_t stride, const glm::ivec2 *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 2,
                           GL_INT, static_cast<GLsizei>(stride), glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setAttrib<glm::ivec3, 3, false>(int location, size_t stride, const glm::ivec3 *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 3,
                           GL_INT, static_cast<GLsizei>(stride), glm::value_ptr(*value));
    return true;
}

template<>
bool FDGL::setAttrib<glm::ivec4, 4, false>(int location, size_t stride, const glm::ivec4 *value)
{
    glVertexAttribIPointer(static_cast<uint>(location), 4,
                           GL_INT, static_cast<GLsizei>(stride), glm::value_ptr(*value));
    return true;
}
