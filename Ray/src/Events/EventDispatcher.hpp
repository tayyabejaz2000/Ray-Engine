#pragma once

#include "Core/Core.hpp"
#include "Core/LayerStack.hpp"

#include "Event.hpp"
#include "KeyEvents.hpp"
#include "MouseEvents.hpp"
#include "WindowEvents.hpp"

namespace Ray
{
    class RAYAPI EventDispatcher
    {
    public:
        EventDispatcher();
        ~EventDispatcher();

        void Dispatch(KeyEvent &) const;
        void Dispatch(MouseScrolledEvent &) const;
        void Dispatch(MouseButtonEvent &) const;
        void Dispatch(WindowResizeEvent &) const;
        void Dispatch(WindowMinimizeEvent &) const;
        void Dispatch(WindowCloseEvent &) const;

        static inline constexpr const Observer<EventDispatcher> &GetEventDispatcher() { return s_singletonInstance; }

    private:
        static Observer<EventDispatcher> s_singletonInstance;
    };
}