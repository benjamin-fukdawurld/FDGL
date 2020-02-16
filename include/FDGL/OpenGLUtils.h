#ifndef OPENGLUTILS_H
#define OPENGLUTILS_H

#include <vector>
#include <glad/glad.h>

#include <FDGL/OpenGLUtilsForward.h>

namespace FDGL
{
    enum class BufferTarget : uint32_t
    {
        Invalid = GL_INVALID_ENUM,
        VertexAttribute = GL_ARRAY_BUFFER,
        AtomicCounter = GL_ATOMIC_COUNTER_BUFFER,
        CopyRead = GL_COPY_READ_BUFFER,
        CopyWrite = GL_COPY_WRITE_BUFFER,
        DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER,
        DrawIndirect = GL_DRAW_INDIRECT_BUFFER,
        VertexIndex = GL_ELEMENT_ARRAY_BUFFER,
        PixelPack = GL_PIXEL_PACK_BUFFER,
        PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
        QueryResult = GL_QUERY_BUFFER,
        ShaderStorage = GL_SHADER_STORAGE_BUFFER,
        TextureData = GL_TEXTURE_BUFFER,
        TranformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
        UniformBlock = GL_UNIFORM_BUFFER
    };

    enum class BufferUsage : uint32_t
    {
        Invalid = GL_INVALID_ENUM,
        StreamDraw = GL_STREAM_DRAW,
        StreamRead = GL_STREAM_READ,
        StreamCopy = GL_STREAM_COPY,
        StaticDraw = GL_STATIC_DRAW,
        StaticRead = GL_STATIC_READ,
        StaticCopy = GL_STATIC_COPY,
        DynamicDraw = GL_DYNAMIC_DRAW,
        DynamicRead = GL_DYNAMIC_READ,
        DynamicCopy = GL_DYNAMIC_COPY
    };

    enum BufferMappingAccessFlag : uint32_t
    {
        Invalid = GL_INVALID_ENUM,
        Write = GL_MAP_WRITE_BIT,
        Read = GL_MAP_READ_BIT,
        ReadWrite = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT,
        Persistent = GL_MAP_PERSISTENT_BIT,
        Coherent = GL_MAP_COHERENT_BIT,
        ExplicitFlush = GL_MAP_FLUSH_EXPLICIT_BIT
    };

    enum class FrameBufferTarget : uint32_t
    {
        Invalid = GL_INVALID_ENUM,
        Write = GL_DRAW_FRAMEBUFFER,
        Read = GL_READ_FRAMEBUFFER,
        ReadWrite = GL_FRAMEBUFFER
    };

    enum class FrameBufferAttachment : uint32_t
    {
        Depth = GL_DEPTH_ATTACHMENT,
        Stencil = GL_STENCIL_ATTACHMENT,
        DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT,

        color0 = GL_COLOR_ATTACHMENT0,
        color1 = GL_COLOR_ATTACHMENT1,
        color2 = GL_COLOR_ATTACHMENT2,
        color3 = GL_COLOR_ATTACHMENT3,
        color4 = GL_COLOR_ATTACHMENT4,
        color5 = GL_COLOR_ATTACHMENT5,
        color6 = GL_COLOR_ATTACHMENT6,
        color7 = GL_COLOR_ATTACHMENT7,
        color8 = GL_COLOR_ATTACHMENT8,
        color9 = GL_COLOR_ATTACHMENT9,

        color10 = GL_COLOR_ATTACHMENT10,
        color11 = GL_COLOR_ATTACHMENT11,
        color12 = GL_COLOR_ATTACHMENT12,
        color13 = GL_COLOR_ATTACHMENT13,
        color14 = GL_COLOR_ATTACHMENT14,
        color15 = GL_COLOR_ATTACHMENT15,
        color16 = GL_COLOR_ATTACHMENT16,
        color17 = GL_COLOR_ATTACHMENT17,
        color18 = GL_COLOR_ATTACHMENT18,
        color19 = GL_COLOR_ATTACHMENT19,

        color20 = GL_COLOR_ATTACHMENT20,
        color21 = GL_COLOR_ATTACHMENT21,
        color22 = GL_COLOR_ATTACHMENT22,
        color23 = GL_COLOR_ATTACHMENT23,
        color24 = GL_COLOR_ATTACHMENT24,
        color25 = GL_COLOR_ATTACHMENT25,
        color26 = GL_COLOR_ATTACHMENT26,
        color27 = GL_COLOR_ATTACHMENT27,
        color28 = GL_COLOR_ATTACHMENT28,
        color29 = GL_COLOR_ATTACHMENT29,

        color30 = GL_COLOR_ATTACHMENT30,
        color31 = GL_COLOR_ATTACHMENT31
    };

    enum class ShaderType : uint32_t
    {
        Invalid = GL_INVALID_ENUM,
        Compute = GL_COMPUTE_SHADER,
        Vertex = GL_VERTEX_SHADER,
        TesselationControl = GL_TESS_CONTROL_SHADER,
        TesselationEvaluation = GL_TESS_EVALUATION_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Fragment = GL_FRAGMENT_SHADER
    };

    enum class TextureTarget : uint32_t
    {
        Invalid = GL_INVALID_ENUM,
        Texture1D = GL_TEXTURE_1D,
        Texture2D = GL_TEXTURE_2D,
        Texture3D = GL_TEXTURE_3D,
        Texture1DArray = GL_TEXTURE_1D_ARRAY,
        Texture2DArray = GL_TEXTURE_2D_ARRAY,
        TextureRectangle = GL_TEXTURE_RECTANGLE,
        TextureCubeMap = GL_TEXTURE_CUBE_MAP,
        TextureCubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
        TextureCubeMapPosX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        TextureCubeMapNegX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        TextureCubeMapPosY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        TextureCubeMapNegY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        TextureCubeMapPosZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        TextureCubeMapNegZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
        TextureBuffer = GL_TEXTURE_BUFFER,
        TextureMultisample2D = GL_TEXTURE_2D_MULTISAMPLE,
        TextureMultisample2DArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
    };

    enum class TextureWrapMode : int32_t
    {
        Invalid = GL_INVALID_ENUM,
        ClampToEdge = GL_CLAMP_TO_EDGE,
        ClampToBorder = GL_CLAMP_TO_BORDER,
        MirroredRepeat = GL_MIRRORED_REPEAT,
        Repeat = GL_REPEAT,
        MirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE
    };

    enum class TextureFilter : int32_t
    {
        Invalid = GL_INVALID_ENUM,
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR,
        NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
        LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
        NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
        LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
    };

    std::vector<GLenum> getLastOpenGLErrors();

    template<typename ...Args>
    bool setUniform(uint32_t shader, const std::string &name, const Args... value)
    {
        int location = glGetUniformLocation(shader, name.c_str());
        if(location < 0)
            return false;

        return setUniform(shader, location, value...);
    }

    template<typename T, size_t size>
    bool setUniform(uint32_t shader, const std::string &name, size_t count, const T *value)
    {
        int location = glGetUniformLocation(shader, name.c_str());
        if(location < 0)
            return false;

        return setUniform<T, size>(location, count, value);
    }

    template<typename T, size_t nb_component, bool normalize>
    bool setAttrib(uint32_t shader, const std::string &name, size_t stride, const T *value)
    {
        int location = glGetAttribLocation(shader, name.c_str());
        if(location < 0)
            return false;

        return setAttrib<T, nb_component, normalize>(location, stride, value);
    }

    template<GLenum type, size_t nb_component, bool normalize = false>
    bool setAttribFromBuffer(int location, size_t stride, const uintptr_t value)
    {
        glVertexAttribPointer(static_cast<uint>(location), nb_component,
                               type, normalize, static_cast<GLsizei>(stride), reinterpret_cast<void*>(value));
        return true;
    }

    template<GLenum type, size_t nb_component, bool normalize = false>
    bool setAttribFromBuffer(uint32_t shader, const std::string &name,
                             size_t stride, const uintptr_t value)
    {
        int location = glGetAttribLocation(shader, name.c_str());
        if(location < 0)
            return false;

        return setAttribFromBuffer<type, nb_component, normalize>(location, stride, value);
    }

    inline void enableAttrib(uint location)
    {
        glEnableVertexAttribArray(location);
    }
}

#endif // OPENGLUTILS_H
