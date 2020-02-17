#include <iostream>

#include <FD3D/SceneGraph/SceneLoader.h>
#include <FDGL/OpenGLBuffer.h>
#include <FDGL/OpenGLVertexArray.h>
#include <FDGL/OpenGLUtils.h>

#include "GLFWImpl.h"
#include "GLUtils.h"

using namespace std;

static float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


int draw_cube(int, char* [])
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

    FDGL::OpenGLShaderProgram program = createShaderProgram();
    FDGL::OpenGLTexture tex = loadTexture("../../FDGL/test/resources/wall.jpg");

    /*FD3D::SceneLoader loader;
    loader.setTextureLoader([](const std::string &path){
        return loadTexture(path);
    });
    loader.setEmbeddedTextureLoader([](const aiTexture *texture){
        return loadTexture(texture);
    });

    FD3D::Scene scene;
    assert(loader.loadScene(scene,
        "/home/ben/Bureau/dev/FanatikDevelopment/FDGL/test/resources/crate/CrateModel.obj"
    ));*/


    /*FD3D::Camera cam;
    FD3D::Projection proj;
    
    cam.setPosition({0, 0, 3});
    proj.setType(FD3D::ProjectionType::Perspective);
    proj.setFar(100.0f);
    proj.setNear(0.1f);
    proj.setHeight(w.getHeight());
    proj.setWidth(w.getWidth());
    FD3D::Transform model;

    FDGL::OpenGLBuffer vbo;
    vbo.create();
    vbo.bind(FDGL::BufferTarget::VertexAttribute);
    vbo.allocate(sizeof(float) * 180, FDGL::BufferUsage::StaticDraw, vertices);

    FDGL::OpenGLVertexArray vao;
    vao.create();
    vao.setFunction([](FDGL::OpenGLBuffer &vbo)
    {
        vbo.bind(FDGL::BufferTarget::VertexAttribute);
        FDGL::setAttribFromBuffer<GL_FLOAT, 3, false>(0, 5 * sizeof(float), 0);
        FDGL::setAttribFromBuffer<GL_FLOAT, 2, false>(1, 5 * sizeof(float), sizeof(float) * 3);

        FDGL::enableAttrib(0);
    }, std::ref(vbo));

    while (w.isOpen())
    {
        w.processInput();
        w.clear();

        // render
        program.bind();
        program.setUniform(0, 1, model.getMatrixPtr());
        program.setUniform(1, 1, cam.getMatrixPtr());
        program.setUniform(1, 1, proj.getMatrixPtr());
        tex.activeTexture();
        tex.bind(FDGL::TextureTarget::Texture2D);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float)*5, vertices);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float)*5, vertices + 3);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        

        w.swapBuffer();
    }*/

    FDGL::OpenGLBuffer vbo;
    vbo.create();
    vbo.bind(FDGL::BufferTarget::VertexAttribute);
    vbo.allocate(sizeof(float) * 180, FDGL::BufferUsage::StaticDraw, vertices);

    FDGL::OpenGLVertexArray vao;
    vao.create();
    vao.setFunction([](FDGL::OpenGLBuffer &vbo)
    {
        vbo.bind(FDGL::BufferTarget::VertexAttribute);
        FDGL::setAttribFromBuffer<GL_FLOAT, 3, false>(0, 5 * sizeof(float), 0);
        FDGL::setAttribFromBuffer<GL_FLOAT, 2, false>(1, 5 * sizeof(float), sizeof(float) * 3);

        FDGL::enableAttrib(0);
        FDGL::enableAttrib(1);
    }, std::ref(vbo));

    program.bind();


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    program.setUniform("texture", 1, 0);

    // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
    // -----------------------------------------------------------------------------------------------------------
    FD3D::Camera cam;
    FD3D::Projection &proj = cam.projection;
    proj.setFov(glm::radians(45.0f));
    proj.setWidth(w.getWidth());
    proj.setHeight(w.getHeight());
    proj.setNear(0.1f);
    proj.setFar(100.0f);
    proj.setType(FD3D::ProjectionType::Perspective);
    program.setUniform(2, proj.getMatrix());

    // render loop
    // -----------
    while (w.isOpen())
    {
        w.processInput();
        w.clear();

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);

        // activate shader
        program.bind();

        // camera/view transformation
        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        float radius = 10.0f;
        float camX   = sin(glfwGetTime()) * radius;
        float camZ   = cos(glfwGetTime()) * radius;
        //cam.setPosition(glm::vec3(camX, 0.0f, camZ));
        view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(model));
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        w.swapBuffer();
    }

    return 0;
}


int draw_triangle()
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

    w.setClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
    w.setClearMask(GL_COLOR_BUFFER_BIT);

    FDGL::OpenGLShaderProgram program = createShaderProgram();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };

    FDGL::OpenGLBuffer vbo;
    vbo.create();
    vbo.bind(FDGL::BufferTarget::VertexAttribute);
    vbo.allocate(sizeof(float) * 9, FDGL::BufferUsage::StaticDraw, vertices);

    FDGL::OpenGLVertexArray vao;
    vao.create();
    vao.setFunction([](FDGL::OpenGLBuffer &vbo){
        vbo.bind(FDGL::BufferTarget::VertexAttribute);
        FDGL::setAttribFromBuffer<GL_FLOAT, 3, false>(0, 3 * sizeof(float), 0);

        FDGL::enableAttrib(0);
    }, std::ref(vbo));

    while (w.isOpen())
    {
        w.processInput();
        w.clear();

        program.bind();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        w.swapBuffer();
    }

    return 0;
}

int main(int argc, char *argv[])
{
    return draw_cube(argc, argv);
}
