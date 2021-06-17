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

        inline void PushLayer(Ref<Layer> layer) { LayerStack::PushLayer(layer); }
        inline void PushOverlay(Ref<Layer> layer) { LayerStack::PushOverlay(layer); }
        inline Ref<Layer> PopLayer(Ref<Layer> layer) { return LayerStack::PopLayer(layer); }
        inline Ref<Layer> PopOverlay(Ref<Layer> layer) { return LayerStack::PopOverlay(layer); }

        void OnEvent(WindowMinimizeEvent &);
        void OnEvent(WindowResizeEvent &);
        void OnEvent(WindowCloseEvent &);

        inline Object<Window> &GetWindow() { return m_Window; }

        static const Application *GetApplication();

        friend int main(int argc, char **argv, char **envp);

    private:
        bool m_running, m_minimized;
        Object<Window> m_Window;
        static Application *s_Application;
    };
    Object<Application> CreateApplication();
}