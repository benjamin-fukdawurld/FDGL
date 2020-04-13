#ifndef BASEOPENGLWINDOW_H
#define BASEOPENGLWINDOW_H

#include <string>
#include <cstdint>
#include <glm/vec4.hpp>
#include <functional>


namespace FDGL
{
    class BaseOpenGLWindow
    {
        public:
            typedef std::function<void(BaseOpenGLWindow&)> InitializeCallback;
            typedef std::function<void(BaseOpenGLWindow&)> QuitCallback;
            typedef std::function<void(BaseOpenGLWindow&)> RenderCallback;
            typedef std::function<void(BaseOpenGLWindow&, int, int)> ResizeCallback;
            typedef std::function<void(FDGL::BaseOpenGLWindow&)> InputCallback;

        protected:
            InitializeCallback m_initStrategy;
            QuitCallback m_quitStrategy;
            RenderCallback m_renderStrategy;
            ResizeCallback m_resizeStrategy;
            InputCallback m_inputStrategy;

            uint32_t m_clearMask;

        public:
            BaseOpenGLWindow(RenderCallback renderStrategy = {});
            virtual ~BaseOpenGLWindow() = default;

            uint32_t getClearMask() const { return m_clearMask; }
            void setClearMask(uint32_t mask) { m_clearMask = mask; }

            InitializeCallback getInitializeStrategy() const;

            template<typename StrategyType, typename ...Args>
            void setInitializeStrategy(StrategyType strategy, Args ...args)
            {
                m_initStrategy = std::bind(strategy, args..., std::placeholders::_1);
            }

            QuitCallback getQuitStrategy() const;

            template<typename StrategyType, typename ...Args>
            void setQuitStrategy(StrategyType strategy, Args ...args)
            {
                m_quitStrategy = std::bind(strategy, args..., std::placeholders::_1);
            }

            RenderCallback getRenderStrategy() const;

            template<typename StrategyType>
            void setRenderStrategy(StrategyType strategy)
            {
                m_renderStrategy = strategy;
            }

            template<typename StrategyType, typename ...Args>
            void setRenderStrategy(StrategyType strategy, Args ...args)
            {
                m_renderStrategy = std::bind(strategy, args..., std::placeholders::_1);
            }

            ResizeCallback getResizeStrategy() const;

            template<typename StrategyType>
            void setResizeStrategy(StrategyType strategy)
            {
                m_resizeStrategy = strategy;
            }

            template<typename StrategyType, typename ...Args>
            void setResizeStrategy(StrategyType strategy, Args ...args)
            {
                m_resizeStrategy = std::bind(strategy, args..., std::placeholders::_1,
                                             std::placeholders::_2, std::placeholders::_3);
            }

            InputCallback getInputStrategy();

            template<typename Strategy>
            void setInputStrategy(Strategy strategy)
            {
                m_inputStrategy = strategy;
            }

            template<typename Strategy, typename ...Args>
            void setInputStrategy(Strategy strategy, Args ...args)
            {
                m_inputStrategy = std::bind(strategy, args..., std::placeholders::_1);
            }

            template<typename T>
            void setRenderer(T &renderer)
            {
                setInitializeStrategy(&T::onInit, &renderer);
                setQuitStrategy(&T::onQuit, &renderer);
                setRenderStrategy(&T::onRender, &renderer);
                setResizeStrategy(&T::onResize, &renderer);
            }

            void init();
            void quit();
            void onResize(int width, int height);
            void render();
            void processInput();

            virtual void clear() const;
            virtual glm::vec4 getClearColor() const;
            virtual void setClearColor(const glm::vec4 &color);

            virtual void setViewPort(int x, int y, int w, int h);
            virtual void setDefaultViewPort();


            virtual bool create(int width, int height, const std::string &title) = 0;
            virtual void destroy() = 0;
            virtual bool isOpen() const = 0;

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
