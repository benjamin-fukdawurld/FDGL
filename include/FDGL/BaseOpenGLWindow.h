#ifndef BASEOPENGLWINDOW_H
#define BASEOPENGLWINDOW_H

#include <string>
#include <cstdint>
#include <glm/vec4.hpp>
#include <glad/glad.h>

namespace FDGL
{
    class BaseOpenGLWindow
    {
        protected:
            GLbitfield m_clearMask;

        public:
            BaseOpenGLWindow();
            virtual ~BaseOpenGLWindow();

            uint32_t getClearMask() const { return m_clearMask; }
            void setClearMask(uint32_t mask) { m_clearMask = mask; }

            virtual void clear() const;
            virtual glm::vec4 getClearColor() const;
            virtual void setClearColor(const glm::vec4 &color);

            virtual void setViewPort(int x, int y, int w, int h);
            virtual void setDefaultViewPort();


            virtual bool create(int width, int height, const std::string &title) = 0;
            virtual void destroy() = 0;
            virtual bool isOpen() const = 0;
            virtual void processInput() = 0;

            virtual void swapBuffer() const = 0;

            virtual std::string getTitle() const = 0;
            virtual void setTitle(const std::string &title) = 0;

            virtual int getWidth() const = 0;
            virtual void setWidth(int w) = 0;

            virtual int getHeight() const = 0;
            virtual void setHeight(int h) = 0;
    };
}

#endif // BASEOPENGLWINDOW_H
