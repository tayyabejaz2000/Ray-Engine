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
        LinuxWindow(const WindowSpecifications &, Window &);
        virtual ~LinuxWindow();

        virtual void Minimize() override;
        virtual void Maximize() override;
        virtual void Restore() override;
        virtual void Resize(uint32_t, uint32_t) override;
        virtual void Move(uint32_t, uint32_t) override;
        virtual void Close() override;

        virtual bool IsOpen() override;

        virtual void VSync(bool) override;
        virtual bool VSync() override { return m_specs.vsync; }

        virtual void *GetNativeWindowHandle() override;

        virtual void OnUpdate() override;

        virtual Object<GraphicsContext> &GetContext() override { return m_context; }
        virtual WindowSpecifications &GetSpecifications() override { return m_specs; }

    private:
        void InitGLFW();

        virtual void Init();
        virtual void Shutdown();

    private:
        WindowHandle *m_windowHandle;
        WindowSpecifications m_specs;

        Object<GraphicsContext> m_context;
        Window *m_sharedWindow;
    };
}
