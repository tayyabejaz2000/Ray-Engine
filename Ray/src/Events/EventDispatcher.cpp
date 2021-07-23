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
        auto &layers = Application::GetApplication().GetLayerStack().GetLayers();
        auto &overlays = Application::GetApplication().GetLayerStack().GetOverlays();

        for (auto &overlay : overlays)
        {
            overlay->OnEvent(e);
            if (e.handled)
                return;
        }
        for (auto &layer : layers)
        {
            layer->OnEvent(e);
            if (e.handled)
                return;
        }
    }
    void EventDispatcher::Dispatch(MouseScrolledEvent &e) const
    {
        auto &layers = Application::GetApplication().GetLayerStack().GetLayers();
        auto &overlays = Application::GetApplication().GetLayerStack().GetOverlays();

        for (auto &overlay : overlays)
        {
            overlay->OnEvent(e);
            if (e.handled)
                return;
        }
        for (auto &layer : layers)
        {
            layer->OnEvent(e);
            if (e.handled)
                return;
        }
    }
    void EventDispatcher::Dispatch(MouseButtonEvent &e) const
    {
        auto &layers = Application::GetApplication().GetLayerStack().GetLayers();
        auto &overlays = Application::GetApplication().GetLayerStack().GetOverlays();

        for (auto &overlay : overlays)
        {
            overlay->OnEvent(e);
            if (e.handled)
                return;
        }
        for (auto &layer : layers)
        {
            layer->OnEvent(e);
            if (e.handled)
                return;
        }
    }

    void EventDispatcher::Dispatch(WindowResizeEvent &e) const
    {
        auto &layers = Application::GetApplication().GetLayerStack().GetLayers();
        auto &overlays = Application::GetApplication().GetLayerStack().GetOverlays();

        for (auto &overlay : overlays)
        {
            overlay->OnEvent(e);
            if (e.handled)
                return;
        }
        for (auto &layer : layers)
        {
            layer->OnEvent(e);
            if (e.handled)
                return;
        }
    }
    void EventDispatcher::Dispatch(WindowMinimizeEvent &e) const
    {
        auto &layers = Application::GetApplication().GetLayerStack().GetLayers();
        auto &overlays = Application::GetApplication().GetLayerStack().GetOverlays();

        for (auto &overlay : overlays)
        {
            overlay->OnEvent(e);
            if (e.handled)
                return;
        }
        for (auto &layer : layers)
        {
            layer->OnEvent(e);
            if (e.handled)
                return;
        }
    }
    void EventDispatcher::Dispatch(WindowCloseEvent &e) const
    {
        auto &layers = Application::GetApplication().GetLayerStack().GetLayers();
        auto &overlays = Application::GetApplication().GetLayerStack().GetOverlays();

        for (auto &overlay : overlays)
        {
            overlay->OnEvent(e);
            if (e.handled)
                return;
        }
        for (auto &layer : layers)
        {
            layer->OnEvent(e);
            if (e.handled)
                return;
        }
    }
}