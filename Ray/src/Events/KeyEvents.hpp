#pragma once

#include "Event.hpp"
#include "KeyCodes.hpp"

namespace Ray
{
    class RAYAPI KeyEvent : public Event
    {
    public:
        KeyEvent(uint32_t _scancode) : Event(), scancode(_scancode) {}
        const uint32_t GetScanCode() const { return scancode; }
        virtual const EventType GetEventType() const override { return EventType::KEY_EVENT; }
        virtual std::string ToString() const
        {
            return "Key Event";
        }

    public:
        const uint32_t scancode;
    };

    class RAYAPI KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(Key _keycode, uint32_t scancode, KeyModifier mod, uint16_t _repeatCount) : KeyEvent(scancode), keycode(_keycode), modifier(mod), repeatCount(_repeatCount) {}
        const Key &GetKeyCode() const { return keycode; }
        const KeyModifier &GetKeyModifier() const { return modifier; }
        const uint16_t &GetRepeatCount() const { return repeatCount; }
        virtual const EventType GetEventType() const override { return EventType::KEY_PRESSED_EVENT; }
        virtual std::string ToString() const
        {
            return "Key Pressed Event";
        }

    public:
        const Key keycode;
        const KeyModifier modifier;
        const uint16_t repeatCount;
    };

    class RAYAPI KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(Key _keycode, int _scancode, KeyModifier mod) : KeyEvent(_scancode), keycode(_keycode), modifier(mod) {}
        const Key &GetKeyCode() const { return keycode; }
        const KeyModifier &GetKeyModifier() const { return modifier; }
        virtual const EventType GetEventType() const override { return EventType::KEY_RELEASED_EVENT; }
        virtual std::string ToString() const
        {
            return "Key Released Event";
        }

    public:
        const Key keycode;
        const KeyModifier modifier;
    };

    class RAYAPI KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(uint scancode) : KeyEvent(scancode) {}
        virtual const EventType GetEventType() const override { return EventType::KEY_TYPED_EVENT; }

        virtual std::string ToString() const
        {
            return "Key Typed Event";
        }
    };
}