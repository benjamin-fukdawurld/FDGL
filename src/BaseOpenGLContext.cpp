#include <FDGL/BaseOpenGLContext.h>

#include <glad/glad.h>

#include <iostream>

FDGL::BaseOpenGLContext::BaseOpenGLContext() {}

FDGL::BaseOpenGLContext::~BaseOpenGLContext() {}

bool FDGL::BaseOpenGLContext::loadOpenGLFunctions(FDGL::BaseOpenGLContext::GetProcAddressFunc f) const
{
    if(!gladLoadGLLoader(f))
    {
        std::cerr << __func__ << ": Failed to load Open GL Functions" << std::endl;
        return false;
    }

    return true;
}
