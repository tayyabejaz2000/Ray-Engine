#pragma once

#include <GLFW/glfw3.h>

#include "Core/Core.hpp"
#include "Core/Window.hpp"
#include "Core/LayerStack.hpp"

#include "Renderer/GraphicsContext.hpp"

namespace Ray
{
    using WindowHandle = GLFWwindow;
    class RAYAPI LinuxWindow : public Window
    {
    public:
        LinuxWindow(const WindowSpecifications &);
        virtual ~LinuxWindow();

        virtual void VSync(bool) override;
        virtual void OnUpdate() override;
        virtual bool IsRunning() override;
        virtual void *GetNativeWindowHandle() override;

    private:
        void InitGLFW();

        virtual void Init(const WindowSpecifications &);
        virtual void Shutdown();

    private:
        WindowHandle *m_windowHandle;
        Object<GraphicsContext> m_context;
    };
}
