#pragma once

#include "Core/Core.hpp"
#include "Events/KeyEvents.hpp"
#include "Events/MouseEvents.hpp"
#include "Events/WindowEvents.hpp"

namespace Ray
{
    class RAYAPI Layer
    {
    public:
        Layer() : m_eventCallFlags(~0){};
        virtual ~Layer() = default;

        //A Layer can only recieve events without being updated
        //i.e. No OnUpdate Method override will make empty OnUpdate Method, doing nothing
        virtual void OnUpdate(float) {}

        virtual void OnEvent(KeyEvent &) {}
        virtual void OnEvent(MouseButtonEvent &e) {}
        virtual void OnEvent(MouseScrolledEvent &e) {}
        virtual void OnEvent(WindowResizeEvent &e) {}
        virtual void OnEvent(WindowMinimizeEvent &e) {}
        virtual void OnEvent(WindowCloseEvent &e) {}

        virtual void OnAttach() {}
        virtual void OnDetach() {}

        ///TODO: Actually stop events if it is blocked

        //Returns if this layer should recieve as certain Event Type Call
        inline bool ShouldRecieveEvent(EventType flag) { return m_eventCallFlags & flag; }
        //Blocks a certain type of event
        inline void BlockEvent(EventType flag) { m_eventCallFlags &= ~flag; }
        //Unblocks a certain type of event
        inline void UnblockEvent(EventType flag) { m_eventCallFlags |= flag; }
        //Blocks all events belonging to category
        inline void BlockCategory(EventCategory category) { m_eventCallFlags &= ~category; }
        //Unblocks all events belonging to category
        inline void UnblockCategory(EventCategory category) { m_eventCallFlags |= category; }

    private:
        uint16_t m_eventCallFlags;
    };
}