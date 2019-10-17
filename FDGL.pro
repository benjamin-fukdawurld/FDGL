#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T10:57:00
#
#-------------------------------------------------
TARGET = FDGL
TEMPLATE = lib
CONFIG += console c++17
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/.obj/$${TARGET}

DEPENDPATH += \
    include \
    ../FDCore/include \
    ../FD3D/include \
    ../thirdparty/glad/include \
    ../thirdparty/glm \

INCLUDEPATH += \
    include \
    ../FDCore/include \
    ../FD3D/include \
    ../thirdparty/glad/include \
    ../thirdparty/glm \

SOURCES += \
    src/BaseOpenGLContext.cpp \
    src/BaseOpenGLWindow.cpp \
    src/OpenGLBuffer.cpp \
    src/OpenGLResource.cpp \
    src/OpenGLShader.cpp \
    src/OpenGLShaderProgram.cpp \
    src/OpenGLUtils.cpp \
    src/OpenGLVertexArray.cpp \
    src/OpenGLTexture.cpp \
    src/OpenGLFrameBuffer.cpp \
    src/OpenGLRenderBuffer.cpp

HEADERS += \
    include/FDGL/BaseOpenGLContext.h \
    include/FDGL/BaseOpenGLWindow.h \
    include/FDGL/OpenGLBuffer.h \
    include/FDGL/OpenGLResource.h \
    include/FDGL/OpenGLShader.h \
    include/FDGL/OpenGLShaderProgram.h \
    include/FDGL/OpenGLUtils.h \
    include/FDGL/OpenGLUtilsForward.h \
    include/FDGL/OpenGLVertexArray.h \
    include/FDGL/OpenGLTexture.h \
    include/FDGL/OpenGLFrameBuffer.h \
    include/FDGL/OpenGLRenderBuffer.h \
    include/FDGL/BufferedMesh.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
