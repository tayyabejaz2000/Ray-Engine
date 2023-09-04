#pragma once

#include "Core.hpp"
#include "Window.hpp"

#include "LayerStack.hpp"
#include "Events/EventDispatcher.hpp"

namespace Ray
{
    class RAYAPI Application
    {
    public:
        Application(const std::string_view &);
        virtual ~Application();

        void Run();

        inline LayerStack &GetLayerStack() { return m_layerStack; }
        inline void PushLayer(Ref<Layer> layer) { m_layerStack.PushLayer(layer); }
        inline void PushOverlay(Ref<Layer> layer) { m_layerStack.PushOverlay(layer); }
        inline Ref<Layer> PopLayer(Ref<Layer> layer) { return m_layerStack.PopLayer(layer); }
        inline Ref<Layer> PopOverlay(Ref<Layer> layer) { return m_layerStack.PopOverlay(layer); }

        void OnEvent(WindowMinimizeEvent &);
        void OnEvent(WindowResizeEvent &);
        void OnEvent(WindowCloseEvent &);

        inline Window &GetWindow() { return *m_window; }

    public:
        static Application &GetApplication();

    private:
        bool m_running, m_minimized;
        Object<Window> m_window;
        LayerStack m_layerStack;

    private:
        static Application *s_application;

        friend int main(int, char **, char **);
    };
    Object<Application> CreateApplication();
}