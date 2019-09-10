#ifndef OPENGLVERTEXARRAY_H
#define OPENGLVERTEXARRAY_H

#include "OpenGLResource.h"

namespace FDGL
{
    class OpenGLVertexArrayWrapper : public FDGL::OpenGLResourceWrapper
    {
        public:
        public:
            OpenGLVertexArrayWrapper(uint32_t id = 0) : OpenGLResourceWrapper(id) {}
            OpenGLVertexArrayWrapper(const OpenGLVertexArrayWrapper &other) : OpenGLResourceWrapper(other) {}
            OpenGLVertexArrayWrapper(const OpenGLResourceWrapper &other) : OpenGLResourceWrapper(other) {}

            OpenGLVertexArrayWrapper(OpenGLVertexArrayWrapper &&other);

            OpenGLVertexArrayWrapper(OpenGLResourceWrapper &&other);

            OpenGLVertexArrayWrapper &operator=(const OpenGLResourceWrapper &other);

            OpenGLVertexArrayWrapper &operator=(OpenGLResourceWrapper &&other);

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
    bool is<OpenGLVertexArrayWrapper>(const OpenGLResourceWrapper &res);

    template<>
    const OpenGLVertexArrayWrapper as<OpenGLVertexArrayWrapper>(const OpenGLResourceWrapper &res);

    template<>
    OpenGLVertexArrayWrapper as<OpenGLVertexArrayWrapper>(OpenGLResourceWrapper &res);

    typedef OwnedRessource<OpenGLVertexArrayWrapper> OpenGLVertexArray;
}

#endif // OPENGLVERTEXARRAY_H
