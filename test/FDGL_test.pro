TARGET = FDGL_test

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../../build/bin
MAKEFILE = ../../build/makefiles/$${TARGET}
OBJECTS_DIR = ../../build/.obj/$${TARGET}

LIBS += -L../../build/lib -lglad -lFDGL -lFD3D -lFDCore
LIBS += -lglfw -lGL -lpthread -ldl -lX11 -lXrandr -lstdc++

DEPENDPATH += \
    ../include \
    ../../thirdparty/glad/include \
    ../../thirdparty/stb/include \
    ../../thirdparty/glm


INCLUDEPATH += \
    ../include \
    ../../thirdparty/glad/include \
    ../../thirdparty/stb/include \
    ../../thirdparty/glm

SOURCES += \
    GLFWImpl.cpp \
    GLUtils.cpp \
    main.cpp

HEADERS += \
    GLFWImpl.h \
    GLUtils.h

DISTFILES += \
    resources/vertex.vert \
    resources/frag.frag \
    resources/wall.jpg