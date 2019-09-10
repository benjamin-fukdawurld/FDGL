#include <FDGL/OpenGLUtils.h>


std::vector<GLenum> FDGL::getLastOpenGLErrors()
{
    std::vector<GLenum> result;
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
        result.push_back(err);

    return result;
}
