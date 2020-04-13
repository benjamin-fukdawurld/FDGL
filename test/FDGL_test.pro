TARGET = FDGL_test

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../../build/bin
MAKEFILE = ../../build/makefiles/$${TARGET}
OBJECTS_DIR = ../../build/.obj/$${TARGET}

LIBS += -L../../build/lib -lglad -lFDGL -lFD3D -lFDCore
LIBS += -lglfw -lGL -lpthread -ldl -lX11 -lXrandr -lstdc++ -lpython3.7m
LIBS += -L../../thirdparty/assimp/bin -lassimp


INCLUDEPATH += \
    ../include \
    ../../FDCore/include \
    ../../FD3D/include \
    ../../thirdparty/glad/include \
    ../../thirdparty/pybind11/include \
    ../../thirdparty/glm \
    ../../thirdparty/assimp/include \
    ../../thirdparty/ \
    /usr/include/python3.7m \
    /usr/include/x86_64-linux-gnu/python3.7m \

SOURCES += \
    GLFWImpl.cpp \
    GLUtils.cpp \
    main.cpp \
    Renderer.cpp \
    Engine.cpp

HEADERS += \
    GLFWImpl.h \
    GLUtils.h \
    Renderer.h \
    Engine.h

OTHER_FILES += \
    resources/vertex.vert \
    resources/frag.frag \
    resources/wall.jpg

DISTFILES += \
    resources/light.vert \
    resources/light.frag \
    resources/crate/CrateModel.obj \
    resources/crate/cratemodel.mtl
