#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

#include "OpenGLResource.h"

namespace FDGL
{
    class OpenGLVertexArrayWrapper : public FDGL::OpenGLObjectWrapper
    {
        public:
        public:
            OpenGLVertexArrayWrapper(uint32_t id = 0) : OpenGLObjectWrapper(id) {}
            OpenGLVertexArrayWrapper(const OpenGLVertexArrayWrapper &other) : OpenGLObjectWrapper(other) {}
            OpenGLVertexArrayWrapper(const OpenGLObjectWrapper &other) : OpenGLObjectWrapper(other) {}

            OpenGLVertexArrayWrapper(OpenGLVertexArrayWrapper &&other);

            OpenGLVertexArrayWrapper(OpenGLObjectWrapper &&other);

            OpenGLVertexArrayWrapper &operator=(const OpenGLObjectWrapper &other);

            OpenGLVertexArrayWrapper &operator=(OpenGLObjectWrapper &&other);

            OpenGLVertexArrayWrapper &operator=(const OpenGLVertexArrayWrapper &other);

            OpenGLVertexArrayWrapper &operator=(OpenGLVertexArrayWrapper &&other);

            bool create();

            void destroy() override;

            void bind();
            void unbind();

            template<typename VAOFunction, typename ...Args>
            void setFunction(VAOFunction f, Args ...args)
            {
                bind();
                f(args...);
                unbind();
            }
    };

    template<>
    bool is<OpenGLVertexArrayWrapper>(const OpenGLObjectWrapper &res);

    template<>
    const OpenGLVertexArrayWrapper as<OpenGLVertexArrayWrapper>(const OpenGLObjectWrapper &res);

    template<>
    OpenGLVertexArrayWrapper as<OpenGLVertexArrayWrapper>(OpenGLObjectWrapper &res);

    typedef OwnedObject<OpenGLVertexArrayWrapper> OpenGLVertexArray;
}

#endif // OPENGLVERTEXARRAY_H
