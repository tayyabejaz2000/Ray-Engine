#include "Window.hpp"

#include "Events/EventDispatcher.hpp"
#include "LayerStack.hpp"

#ifdef RAY_PLATFORM_LINUX
#include "Platform/Linux/LinuxWindow.hpp"
#endif

namespace Ray
{
    Window::Window(const WindowSpecifications &specs) : m_specs(specs)
    {
        if (!s_Window)
            s_Window = CreateObserver<Window>(this);
        else
            throw std::runtime_error("Window Already created");
    }
    Object<Window> Window::Create(const WindowSpecifications &specs)
    {
#ifdef RAY_PLATFORM_LINUX
        return CreateObject<LinuxWindow>(specs);
#else
        return nullptr;
#endif
    }

    WindowSpecifications &Window::GetSpecifications()
    {
        return m_specs;
    }
}