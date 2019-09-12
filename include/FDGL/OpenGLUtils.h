#ifndef OPENGLUTILS_H
#define OPENGLUTILS_H

#include <vector>
#include <glad/glad.h>

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
}

#endif // OPENGLUTILS_H
