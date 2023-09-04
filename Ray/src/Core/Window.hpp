#pragma once

#include "Core.hpp"
#include "WindowSpecifications.hpp"
#include "Renderer/GraphicsContext.hpp"

namespace Ray
{
    class RAYAPI Window
    {
    public:
        Window() { ++Window::Instances; }
        virtual ~Window() { --Window::Instances; }

        virtual void Minimize() = 0;
        virtual void Maximize() = 0;
        virtual void Restore() = 0;
        virtual void Resize(uint32_t, uint32_t) = 0;
        virtual void Move(uint32_t, uint32_t) = 0;
        virtual void Close() = 0;

        virtual bool IsOpen() = 0;

        virtual void VSync(bool) = 0;
        virtual bool VSync() = 0;

        virtual void *GetNativeWindowHandle() = 0;

        virtual void OnUpdate() = 0;

        virtual Object<GraphicsContext> &GetContext() = 0;
        virtual WindowSpecifications &GetSpecifications() = 0;

    public:
        static Object<Window> Create(const WindowSpecifications &);

    public:
        static uint16_t Instances;
    };
}