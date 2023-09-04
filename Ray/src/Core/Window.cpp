#include "Window.hpp"

#include "Events/EventDispatcher.hpp"
#include "LayerStack.hpp"

#ifdef RAY_PLATFORM_LINUX
#include "Platform/Linux/LinuxWindow.hpp"
#endif

namespace Ray
{
    uint16_t Window::Instances = 0;

    Object<Window> Window::Create(const WindowSpecifications &specs)
    {
#ifdef RAY_PLATFORM_LINUX
        return CreateObject<LinuxWindow>(specs);
#else
        return nullptr;
#endif
    }
}