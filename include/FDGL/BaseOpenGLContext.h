#ifndef BASEOPENGLCONTEXT_H
#define BASEOPENGLCONTEXT_H

namespace FDGL
{
    class BaseOpenGLWindow;

    class BaseOpenGLContext
    {
        public:
            typedef void* (*GetProcAddressFunc) (const char*);

        public:
            BaseOpenGLContext();
            virtual ~BaseOpenGLContext();

            virtual bool loadOpenGLFunctions(GetProcAddressFunc f) const;

            virtual bool init() = 0;
            virtual bool quit() = 0;
            virtual void setCurrentContext(BaseOpenGLWindow &window) = 0;
    };
}

#endif // BASEOPENGLCONTEXT_H
