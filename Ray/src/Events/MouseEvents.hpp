#pragma once

#include "Event.hpp"
#include "KeyCodes.hpp"
#include "MouseCodes.hpp"

namespace Ray
{
    struct MouseVec2
    {
        float x = INFINITY;
        float y = INFINITY;
        std::string ToString() const
        {
            return '(' + std::to_string(x) + ", " + std::to_string(y) + ')';
        }
    };

    class RAYAPI MouseEvent : public Event
    {
    public:
        MouseEvent(const MouseVec2 &pos) : Event(), position(pos) {}
        MouseEvent(const float &x, const float &y) : position({x, y}) {}
        const float &GetMouseX() const { return position.x; }
        const float &GetMouseY() const { return position.y; }
        const MouseVec2 &GetMousePosition() const { return position; }
        virtual const EventType GetEventType() const override { return EventType::MOUSE_EVENT; }
        virtual std::string ToString() const
        {
            return "Mouse Event";
        }

    public:
        const MouseVec2 position;
    };

    class RAYAPI MouseScrolledEvent : public MouseEvent
    {
    public:
        MouseScrolledEvent(const MouseVec2 &pos, const MouseVec2 &_scroll) : MouseEvent(pos), scroll(_scroll) {}
        const float &GetMouseScrollX() const { return scroll.x; }
        const float &GetMouseScrollY() const { return scroll.y; }
        const MouseVec2 &GetMouseScroll() const { return scroll; }
        virtual const EventType GetEventType() const override { return EventType::MOUSE_SCROLLED_EVENT; }
        virtual std::string ToString() const
        {
            return "Mouse Scrolled Event";
        }

    public:
        const MouseVec2 scroll;
    };

    class RAYAPI MouseButtonEvent : public MouseEvent
    {
    public:
        MouseButtonEvent(const MouseVec2 &pos, MouseButton _button, KeyModifier mod) : MouseEvent(pos), button(_button), modifier(mod) {}
        const MouseButton &GetButton() { return button; }
        const KeyModifier &GetKeyModifier() const { return modifier; }
        virtual const EventType GetEventType() const override { return EventType::MOUSE_BUTTON_EVENT; }
        virtual std::string ToString() const
        {
            return "Mouse Button Event";
        }

    public:
        const MouseButton button;
        const KeyModifier modifier;
    };

    class RAYAPI MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(const MouseVec2 &pos, MouseButton button, KeyModifier mod) : MouseButtonEvent(pos, button, mod) {}
        virtual const EventType GetEventType() const override { return EventType::MOUSE_BUTTON_PRESSED_EVENT; }
        virtual std::string ToString() const
        {
            return "Mouse Button Pressed Event";
        }
    };
    class RAYAPI MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(const MouseVec2 &pos, MouseButton button, KeyModifier mod) : MouseButtonEvent(pos, button, mod) {}
        virtual const EventType GetEventType() const override { return EventType::MOUSE_BUTTON_RELEASED_EVENT; }
        virtual std::string ToString() const
        {
            return "Mouse Button Released Event";
        }
    };
}