#pragma once

#include "Core.hpp"
#include "WindowSpecifications.hpp"

namespace Ray
{
    class LayerStack;
    class EventDispatcher;
    class RAYAPI Window
    {
    public:
        Window(const WindowSpecifications &);
        virtual ~Window() = default;

        WindowSpecifications &GetSpecifications();
        bool VSync() { return m_specs.vsync; }

        virtual void VSync(bool) = 0;
        virtual void OnUpdate() = 0;
        virtual bool IsRunning() = 0;
        virtual void *GetNativeWindowHandle() = 0;

        static Object<Window> Create(const WindowSpecifications &);

    private:
        Window *s_Window;

    protected:
        WindowSpecifications m_specs;
    };
}