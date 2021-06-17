#include "EventDispatcher.hpp"

namespace Ray
{
    EventDispatcher *EventDispatcher::s_singletonInstance;

    EventDispatcher::EventDispatcher()
    {
        if (s_singletonInstance)
            throw std::runtime_error("Event Dispatcher already Initialized");
        else
        {
            s_singletonInstance = this;
        }
    }
    EventDispatcher::~EventDispatcher()
    {
    }

    void EventDispatcher::Dispatch(KeyEvent &e) const
    {
        for (auto &overlay : LayerStack::GetOverlays())
        {
            overlay->OnEvent(e);
            if (e.handled)
                return;
        }
        for (auto &layer : LayerStack::GetLayers())
        {
            layer->OnEvent(e);
            if (e.handled)
                return;
        }
    }
    void EventDispatcher::Dispatch(MouseScrolledEvent &e) const
    {
        for (auto &overlay : LayerStack::GetOverlays())
        {
            overlay->OnEvent(e);
            if (e.handled)
                return;
        }
        for (auto &layer : LayerStack::GetLayers())
        {
            layer->OnEvent(e);
            if (e.handled)
                return;
        }
    }
    void EventDispatcher::Dispatch(MouseButtonEvent &e) const
    {
        for (auto &overlay : LayerStack::GetOverlays())
        {
            overlay->OnEvent(e);
            if (e.handled)
                return;
        }
        for (auto &layer : LayerStack::GetLayers())
        {
            layer->OnEvent(e);
            if (e.handled)
                return;
        }
    }

    void EventDispatcher::Dispatch(WindowResizeEvent &e) const
    {
        for (auto &overlay : LayerStack::GetOverlays())
        {
            overlay->OnEvent(e);
            if (e.handled)
                return;
        }
        for (auto &layer : LayerStack::GetLayers())
        {
            layer->OnEvent(e);
            if (e.handled)
                return;
        }
    }
    void EventDispatcher::Dispatch(WindowMinimizeEvent &e) const
    {
        for (auto &overlay : LayerStack::GetOverlays())
        {
            overlay->OnEvent(e);
            if (e.handled)
                return;
        }
        for (auto &layer : LayerStack::GetLayers())
        {
            layer->OnEvent(e);
            if (e.handled)
                return;
        }
    }
    void EventDispatcher::Dispatch(WindowCloseEvent &e) const
    {
        for (auto &overlay : LayerStack::GetOverlays())
        {
            overlay->OnEvent(e);
            if (e.handled)
                return;
        }
        for (auto &layer : LayerStack::GetLayers())
        {
            layer->OnEvent(e);
            if (e.handled)
                return;
        }
    }
}