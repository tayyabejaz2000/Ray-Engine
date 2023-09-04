#include "Application.hpp"
#include "Layers/ApplicationLayer.hpp"

///Temporary
#include <glad/glad.h>

namespace Ray
{
    Application *Application::s_application = nullptr;

    Application::Application(const std::string_view &windowName) : m_running(false), m_minimized(false)
    {
        if (!s_application)
            s_application = this;
        else
            throw std::runtime_error("Application already created");

        PushLayer(CreateRef<ApplicationLayer>());

        WindowSpecifications specs;
        specs.title = windowName;
        specs.resolution = Resolution::RESOLUTION_HD;
        specs.samples = 4;
        specs.vsync = true;
        m_window = Window::Create(specs);

        m_running = true;
    }
    Application::~Application()
    {
        s_application = nullptr;
    }
    void Application::Run()
    {
        //std::function<void(WindowResizeEvent &)> temp = Application::OnEvent;
        void (Application::*temp)(Ray::WindowMinimizeEvent &) = Application::OnEvent;

        auto lastFrameTime = std::chrono::system_clock::now();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        while (m_running)
        {
            auto currentTime = std::chrono::system_clock::now();
            auto deltaTime = (currentTime - lastFrameTime).count() / 1e6f;
            lastFrameTime = currentTime;
            if (!m_minimized)
            {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                GetLayerStack().OnUpdate(deltaTime);
            }
            GetWindow().OnUpdate();
        }
    }

    void Application::OnEvent(WindowMinimizeEvent &e)
    {
        m_minimized = true;
        e.handled = true;
        GetWindow().Minimize();
    }

    void Application::OnEvent(WindowResizeEvent &e)
    {
        m_minimized = false;
        e.handled = true;
        GetWindow().Resize(e.width, e.height);
    }

    void Application::OnEvent(WindowCloseEvent &e)
    {
        m_running = false;
        e.handled = true;
        GetLayerStack().OnDetach();
    }

    Application &Application::GetApplication()
    {
        return *s_application;
    }

}