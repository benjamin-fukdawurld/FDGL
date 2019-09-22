#ifndef GLUTILS_H
#define GLUTILS_H

#include <string>

#include <FDGL/OpenGLTexture.h>
#include <FDGL/OpenGLShaderProgram.h>

std::string loadFile(const std::string &filePath);

FDGL::OpenGLTextureWrapper loadTexture(const std::string &filePath);

FDGL::OpenGLShaderProgramWrapper createShaderProgram();


#endif // GLUTILS_H
