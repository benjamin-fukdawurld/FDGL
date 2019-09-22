#include "GLUtils.h"

#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace std;



std::string loadFile(const std::string &filePath)
{
    FILE* f = fopen(filePath.c_str(), "r");
    if(!f)
        throw runtime_error(filePath + ": not found");

    // Determine file size
    fseek(f, 0, SEEK_END);
    size_t size = static_cast<size_t>(ftell(f));

    std::unique_ptr<char[]> where(new char[size]);

    rewind(f);
    fread(where.get(), sizeof(char), size, f);
    std::string result(where.get(), size);

    return result;
}

FDGL::OpenGLTextureWrapper loadTexture(const std::string &filePath)
{
    size_t size[2];
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    std::unique_ptr<unsigned char, void (*)(unsigned char*)> data(stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0),
                                                                  [](unsigned char *data) { stbi_image_free(data); });
    size[0] = static_cast<size_t>(width);
    size[1] = static_cast<size_t>(height);

    if (!data)
    {
        std::cout << "Failed to load texture" << std::endl;
        return FDGL::OpenGLTextureWrapper();
    }

    FDGL::OpenGLTextureWrapper tex;
    if(!tex.create())
        return FDGL::OpenGLTextureWrapper();

    tex.bind(FDGL::TextureTarget::Texture2D);

    tex.setWrapModeS(FDGL::TextureWrapMode::Repeat);
    tex.setWrapModeT(FDGL::TextureWrapMode::Repeat);

    tex.setMinFilter(FDGL::TextureFilter::LinearMipmapLinear);
    tex.setMagFilter(FDGL::TextureFilter::Linear);
    tex.allocate(FDGL::TextureTarget::Texture2D, 0, GL_RGB, size,  GL_RGB, GL_UNSIGNED_BYTE, data.get());
    tex.generateMipMap();

    return tex;
}

FDGL::OpenGLShaderProgramWrapper createShaderProgram()
{
    FDGL::OpenGLShaderProgramWrapper program;
    FDGL::OpenGLShader v_shad;
    v_shad.create(FDGL::ShaderType::Vertex);
    v_shad.setSource(loadFile("../../resources/vertex.vert"));
    if(!v_shad.compile())
    {
        std::string msg = "Cannot compile vertex shader: ";
        msg += v_shad.getCompileErrors();
        cerr << msg << endl;
        return FDGL::OpenGLShaderProgramWrapper();
    }

    FDGL::OpenGLShader f_shad;
    f_shad.create(FDGL::ShaderType::Fragment);
    f_shad.setSource(loadFile("../../resources/frag.frag"));
    if(!f_shad.compile())
    {
        std::string msg = "Cannot compile fragment shader: ";
        msg += f_shad.getCompileErrors();
        cerr << msg << endl;
        return FDGL::OpenGLShaderProgramWrapper();
    }

    // link shaders
    program.create();
    program.attach(v_shad);
    program.attach(f_shad);
    if(!program.link())
    {
        std::string msg = "Cannot link shader program: ";
        msg += program.getLinkErrors();
        cerr << msg << endl;
        return FDGL::OpenGLShaderProgramWrapper();
    }

    return program;
}
