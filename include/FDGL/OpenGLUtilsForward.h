#ifndef OPENGLUTILSFORWARD_H
#define OPENGLUTILSFORWARD_H

#include <cstdlib>
#include <glm/matrix.hpp>
#include <string>

namespace FDGL
{
    template<typename T, size_t nb_component, bool normalize = false>
    bool setAttrib(int location, size_t stride, const T *value);

    template<typename T>
    bool setUniform(int location, const T &value);

    template<typename T>
    bool setUniform(int location, const T &value1, const T &value2);

    template<typename T>
    bool setUniform(int location, const T &value1, const T &value2, const T &value3);

    template<typename T>
    bool setUniform(int location, const T &value1, const T &value2, const T &value3, const T &value4);

    template<typename T, size_t size = 1>
    bool setUniform(int location, size_t count, const T *value);

    template<>
    bool setUniform<double>(int location, const double &value);

    template<>
    bool setUniform<float>(int location, const float &value);

    template<>
    bool setUniform<int>(int location, const int &value);

    template<>
    bool setUniform<uint>(int location, const uint &value);

    template<>
    bool setUniform<double>(int location, const double &value1, const double &value2);

    template<>
    bool setUniform<float>(int location, const float &value1, const float &value2);

    template<>
    bool setUniform<int>(int location, const int &value1, const int &value2);

    template<>
    bool setUniform<uint>(int location, const uint &value1, const uint &value2);

    template<>
    bool setUniform<double>(int location, const double &value1, const double &value2, const double &value3);

    template<>
    bool setUniform<float>(int location, const float &value1, const float &value2, const float &value3);

    template<>
    bool setUniform<int>(int location, const int &value1, const int &value2, const int &value3);

    template<>
    bool setUniform<uint>(int location, const uint &value1, const uint &value2, const uint &value3);

    template<>
    bool setUniform<double>(int location, const double &value1, const double &value2, const double &value3, const double &value4);

    template<>
    bool setUniform<float>(int location, const float &value1, const float &value2, const float &value3, const float &value4);

    template<>
    bool setUniform<int>(int location, const int &value1, const int &value2, const int &value3, const int &value4);

    template<>
    bool setUniform<uint>(int location, const uint &value1, const uint &value2, const uint &value3, const uint &value4);

    template<>
    bool setUniform<double, 1>(int location, size_t count, const double *value);

    template<>
    bool setUniform<double, 2>(int location, size_t count, const double *value);

    template<>
    bool setUniform<double, 3>(int location, size_t count, const double *value);

    template<>
    bool setUniform<double, 4>(int location, size_t count, const double *value);

    template<>
    bool setUniform<float, 1>(int location, size_t count, const float *value);

    template<>
    bool setUniform<float, 2>(int location, size_t count, const float *value);

    template<>
    bool setUniform<float, 3>(int location, size_t count, const float *value);

    template<>
    bool setUniform<float, 4>(int location, size_t count, const float *value);

    template<>
    bool setUniform<int, 1>(int location, size_t count, const int *value);

    template<>
    bool setUniform<int, 2>(int location, size_t count, const int *value);

    template<>
    bool setUniform<int, 3>(int location, size_t count, const int *value);

    template<>
    bool setUniform<int, 4>(int location, size_t count, const int *value);

    template<>
    bool setUniform<uint, 1>(int location, size_t count, const uint *value);

    template<>
    bool setUniform<uint, 2>(int location, size_t count, const uint *value);

    template<>
    bool setUniform<uint, 3>(int location, size_t count, const uint *value);

    template<>
    bool setUniform<uint, 4>(int location, size_t count, const uint *value);

    template<>
    bool setUniform<glm::vec2>(int location, size_t count, const glm::vec2 *value);

    template<>
    bool setUniform<glm::vec3>(int location, size_t count, const glm::vec3 *value);

    template<>
    bool setUniform<glm::vec4>(int location, size_t count, const glm::vec4 *value);

    template<>
    bool setUniform<glm::mat2>(int location, size_t count, const glm::mat2 *value);

    template<>
    bool setUniform<glm::mat2x3>(int location, size_t count, const glm::mat2x3 *value);

    template<>
    bool setUniform<glm::mat2x4>(int location, size_t count, const glm::mat2x4 *value);

    template<>
    bool setUniform<glm::mat3>(int location, size_t count, const glm::mat3 *value);

    template<>
    bool setUniform<glm::mat3x2>(int location, size_t count, const glm::mat3x2 *value);

    template<>
    bool setUniform<glm::vec2>(int location, const glm::vec2 &value);

    template<>
    bool setUniform<glm::vec3>(int location, const glm::vec3 &value);

    template<>
    bool setUniform<glm::vec4>(int location, const glm::vec4 &value);

    template<>
    bool setUniform<glm::mat2>(int location, const glm::mat2 &value);

    template<>
    bool setUniform<glm::mat2x3>(int location, const glm::mat2x3 &value);

    template<>
    bool setUniform<glm::mat2x4>(int location, const glm::mat2x4 &value);

    template<>
    bool setUniform<glm::mat3>(int location, const glm::mat3 &value);

    template<>
    bool setUniform<glm::mat3x2>(int location, const glm::mat3x2 &value);

    template<>
    bool setUniform<glm::mat3x4>(int location, const glm::mat3x4 &value);

    template<>
    bool setUniform<glm::mat4>(int location, const glm::mat4 &value);

    template<>
    bool setUniform<glm::mat4x2>(int location, const glm::mat4x2 &value);

    template<>
    bool setUniform<glm::mat4x3>(int location, const glm::mat4x3 &value);

    template<>
    bool setAttrib<float, 1, false>(int location, size_t stride, const float *value);

    template<>
    bool setAttrib<float, 2, false>(int location, size_t stride, const float *value);

    template<>
    bool setAttrib<float, 3, false>(int location, size_t stride, const float *value);

    template<>
    bool setAttrib<float, 4, false>(int location, size_t stride, const float *value);

    template<>
    bool setAttrib<float, 1, true>(int location, size_t stride, const float *value);

    template<>
    bool setAttrib<float, 2, true>(int location, size_t stride, const float *value);

    template<>
    bool setAttrib<float, 3, true>(int location, size_t stride, const float *value);

    template<>
    bool setAttrib<float, 4, true>(int location, size_t stride, const float *value);

    template<>
    bool setAttrib<int8_t, 1, false>(int location, size_t stride, const int8_t *value);

    template<>
    bool setAttrib<int8_t, 2, false>(int location, size_t stride, const int8_t *value);

    template<>
    bool setAttrib<int8_t, 3, false>(int location, size_t stride, const int8_t *value);

    template<>
    bool setAttrib<int8_t, 4, false>(int location, size_t stride, const int8_t *value);

    template<>
    bool setAttrib<int16_t, 1, false>(int location, size_t stride, const int16_t *value);

    template<>
    bool setAttrib<int16_t, 2, false>(int location, size_t stride, const int16_t *value);

    template<>
    bool setAttrib<int16_t, 3, false>(int location, size_t stride, const int16_t *value);

    template<>
    bool setAttrib<int16_t, 4, false>(int location, size_t stride, const int16_t *value);

    template<>
    bool setAttrib<int32_t, 1, false>(int location, size_t stride, const int32_t *value);

    template<>
    bool setAttrib<int32_t, 2, false>(int location, size_t stride, const int32_t *value);

    template<>
    bool setAttrib<int32_t, 3, false>(int location, size_t stride, const int32_t *value);

    template<>
    bool setAttrib<int32_t, 4, false>(int location, size_t stride, const int32_t *value);

    template<>
    bool setAttrib<uint8_t, 1, false>(int location, size_t stride, const uint8_t *value);

    template<>
    bool setAttrib<uint8_t, 2, false>(int location, size_t stride, const uint8_t *value);

    template<>
    bool setAttrib<uint8_t, 3, false>(int location, size_t stride, const uint8_t *value);

    template<>
    bool setAttrib<uint8_t, 4, false>(int location, size_t stride, const uint8_t *value);

    template<>
    bool setAttrib<uint16_t, 1, false>(int location, size_t stride, const uint16_t *value);

    template<>
    bool setAttrib<uint16_t, 2, false>(int location, size_t stride, const uint16_t *value);

    template<>
    bool setAttrib<uint16_t, 3, false>(int location, size_t stride, const uint16_t *value);

    template<>
    bool setAttrib<uint16_t, 4, false>(int location, size_t stride, const uint16_t *value);

    template<>
    bool setAttrib<uint32_t, 1, false>(int location, size_t stride, const uint32_t *value);

    template<>
    bool setAttrib<uint32_t, 2, false>(int location, size_t stride, const uint32_t *value);

    template<>
    bool setAttrib<uint32_t, 3, false>(int location, size_t stride, const uint32_t *value);

    template<>
    bool setAttrib<uint32_t, 4, false>(int location, size_t stride, const uint32_t *value);

    template<>
    bool setAttrib<glm::vec2, 2, false>(int location, size_t stride, const glm::vec2 *value);

    template<>
    bool setAttrib<glm::vec3, 3, false>(int location, size_t stride, const glm::vec3 *value);

    template<>
    bool setAttrib<glm::vec4, 4, false>(int location, size_t stride, const glm::vec4 *value);

    template<>
    bool setAttrib<glm::vec2, 2, true>(int location, size_t stride, const glm::vec2 *value);

    template<>
    bool setAttrib<glm::vec3, 3, true>(int location, size_t stride, const glm::vec3 *value);

    template<>
    bool setAttrib<glm::vec4, 4, true>(int location, size_t stride, const glm::vec4 *value);

    template<>
    bool setAttrib<glm::ivec2, 2, false>(int location, size_t stride, const glm::ivec2 *value);

    template<>
    bool setAttrib<glm::ivec3, 3, false>(int location, size_t stride, const glm::ivec3 *value);

    template<>
    bool setAttrib<glm::ivec4, 4, false>(int location, size_t stride, const glm::ivec4 *value);

    template<typename ...Args>
    bool setUniform(uint32_t shader, const std::string &name, const Args... value);

    template<typename T, size_t size = 1>
    bool setUniform(uint32_t shader, const std::string &name, size_t count, const T *value);

    template<typename T, size_t nb_component, bool normalize = false>
    bool setAttrib(uint32_t shader, const std::string &name, size_t stride, const T *value);
}

#endif // OPENGLUTILSFORWARD_H
