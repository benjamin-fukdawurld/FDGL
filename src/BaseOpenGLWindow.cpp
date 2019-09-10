#include <FDGL/BaseOpenGLWindow.h>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

FDGL::BaseOpenGLWindow::BaseOpenGLWindow()
{

}

FDGL::BaseOpenGLWindow::~BaseOpenGLWindow()
{

}

void FDGL::BaseOpenGLWindow::clear() const
{
    glClear(getClearMask());
}

glm::vec4 FDGL::BaseOpenGLWindow::getClearColor() const
{
    glm::vec4 result;
    glGetFloatv(GL_COLOR_CLEAR_VALUE, glm::value_ptr(result));
    return result;
}

void FDGL::BaseOpenGLWindow::setClearColor(const glm::vec4 &color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void FDGL::BaseOpenGLWindow::setViewPort(int x, int y, int w, int h)
{
    glViewport(x, y, w, h);
}

void FDGL::BaseOpenGLWindow::setDefaultViewPort()
{
    setViewPort(0, 0, getWidth(), getHeight());
}
