#pragma once

#include "Event.hpp"

namespace Ray
{
    class RAYAPI WindowEvent : public Event
    {
    public:
        WindowEvent() : Event() {}
        virtual const EventType GetEventType() const override { return EventType::WINDOW_EVENT; }
        virtual std::string ToString() const override
        {
            return "Window Event";
        }
    };

    class RAYAPI WindowCloseEvent : public WindowEvent
    {
    public:
        WindowCloseEvent() : WindowEvent() {}
        virtual const EventType GetEventType() const override { return EventType::WINDOW_CLOSE_EVENT; }
        virtual std::string ToString() const override
        {
            return "Window Close Event";
        }
    };

    class RAYAPI WindowResizeEvent : public WindowEvent
    {
    public:
        WindowResizeEvent(uint16_t w, uint16_t h) : WindowEvent(), width(w), height(h) {}
        const uint16_t &GetWindowWidth() const { return width; }
        const uint16_t &GetWindowHeight() const { return height; }
        virtual const EventType GetEventType() const override { return EventType::WINDOW_RESIZE_EVENT; }
        virtual std::string ToString() const override
        {
            return "Window Resize Event";
        }

    public:
        const uint16_t width, height;
    };

    class RAYAPI WindowMinimizeEvent : public WindowEvent
    {
    public:
        WindowMinimizeEvent() : WindowEvent() {}
        virtual const EventType GetEventType() const override { return EventType::WINDOW_MINIMIZE_EVENT; }
        virtual std::string ToString() const override
        {
            return "Window Minimize Event";
        }
    };
}