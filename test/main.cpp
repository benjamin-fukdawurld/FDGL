#include <iostream>

#include "GLFWImpl.h"

#include <FD3D/Mesh/ModelLoader.h>

using namespace std;

int main(int, char* [])
{
    Context ctx;
    if(!ctx.init())
        return -1;

    Window w;
    if(!w.create(800, 600, "Test window"))
        return -1;

    ctx.setCurrentContext(w);
    if (!ctx.loadOpenGLFunctions(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        return -1;

    ctx.enableDepth();
    ctx.enableFaceCulling();

    w.setClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
    w.setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    FD3D::ModelLoader loader;

    auto model = loader.loadModel<FD3D::Model<FD3D::Mesh<FD3D::Vertex>>>(
        "/home/ben/Bureau/dev/FanatikDevelopment/FDGL/test/resources/nano_suit/source/scene.fbx"
    );

    while (w.isOpen())
    {
        w.processInput();
        w.clear();

        // render

        w.swapBuffer();
    }

    return 0;
}
