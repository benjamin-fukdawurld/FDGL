#include <FDGL/BaseOpenGLWindow.h>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

FDGL::BaseOpenGLWindow::BaseOpenGLWindow(RenderCallback renderStrategy) :
    m_renderStrategy(renderStrategy),
    m_clearMask(GL_COLOR_BUFFER_BIT)
{

}

FDGL::BaseOpenGLWindow::InitializeCallback FDGL::BaseOpenGLWindow::getInitializeStrategy() const
{
    return m_initStrategy;
}

FDGL::BaseOpenGLWindow::QuitCallback FDGL::BaseOpenGLWindow::getQuitStrategy() const
{
    return m_quitStrategy;
}

FDGL::BaseOpenGLWindow::RenderCallback FDGL::BaseOpenGLWindow::getRenderStrategy() const
{
    return m_renderStrategy;
}

FDGL::BaseOpenGLWindow::ResizeCallback FDGL::BaseOpenGLWindow::getResizeStrategy() const
{
    return m_resizeStrategy;
}

FDGL::BaseOpenGLWindow::InputCallback FDGL::BaseOpenGLWindow::getInputStrategy()
{
    return m_inputStrategy;
}

void FDGL::BaseOpenGLWindow::init()
{
    if(m_initStrategy)
        m_initStrategy(*this);
}

void FDGL::BaseOpenGLWindow::quit()
{
    if(m_quitStrategy)
        m_quitStrategy(*this);
}

void FDGL::BaseOpenGLWindow::onResize(int width, int height)
{
    if(m_resizeStrategy)
        m_resizeStrategy(*this, width, height);
}

void FDGL::BaseOpenGLWindow::render()
{
    if(m_renderStrategy)
        m_renderStrategy(*this);
}

void FDGL::BaseOpenGLWindow::processInput()
{
    if(m_inputStrategy)
        m_inputStrategy(*this);
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
