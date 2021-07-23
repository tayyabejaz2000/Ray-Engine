#pragma once

#include "Core/Core.hpp"

namespace Ray
{
    enum RAYAPI EventType : uint16_t
    {
        EVENT = 0,
        KEY_EVENT = BIT(0),
        KEY_PRESSED_EVENT = BIT(1),
        KEY_RELEASED_EVENT = BIT(2),
        KEY_TYPED_EVENT = BIT(3),

        MOUSE_EVENT = BIT(4),
        MOUSE_SCROLLED_EVENT = BIT(5),
        MOUSE_BUTTON_EVENT = BIT(6),
        MOUSE_BUTTON_PRESSED_EVENT = BIT(7),
        MOUSE_BUTTON_RELEASED_EVENT = BIT(8),

        WINDOW_EVENT = BIT(9),
        WINDOW_RESIZE_EVENT = BIT(10),
        WINDOW_CLOSE_EVENT = BIT(11),
        WINDOW_MINIMIZE_EVENT = BIT(12),
    };
    //Mask to get event category
    enum RAYAPI EventCategory : uint16_t
    {
        NONE = 0,
        INPUT = 0b0000000111111111,
        KEYBOARD = 0b0000000000001111,
        MOUSE = 0b0000000111110000,
        MOUSE_BUTTON = 0b0000000111000000,
        WINDOW = 0b0001111000000000,
    };

    class RAYAPI Event
    {
    public:
        Event() : handled(false) {}
        virtual ~Event() = default;

        inline bool &IsHandled() { return handled; }
        inline const bool &IsHandled() const { return handled; }

        virtual const EventType GetEventType() const { return EventType::EVENT; }
        inline bool IsInCategory(EventCategory cat) const { return ((uint16_t)cat & (uint16_t)GetEventType()); }
        virtual std::string ToString() const = 0;

    public:
        bool handled;
    };
    inline std::ostream &operator<<(std::ostream &out, const Event &e)
    {
        return (out << e.ToString());
    }
}
