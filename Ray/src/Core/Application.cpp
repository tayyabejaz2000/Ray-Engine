#include "Application.hpp"
#include "Layers/ApplicationLayer.hpp"

#include <glad/glad.h>

namespace Ray
{
    Application *Application::s_Application = nullptr;

    Application::Application(const std::string_view &windowName) : m_running(false), m_minimized(false)
    {
        if (!s_Application)
            s_Application = this;
        else
            throw std::runtime_error("Application already created");

        PushLayer(CreateRef<ApplicationLayer>());

        WindowSpecifications specs;
        specs.title = windowName;
        specs.resolution = Resolution::RESOLUTION_HD;
        specs.samples = 4;
        specs.vsync = true;
        m_Window = Window::Create(specs);

        m_running = true;
    }
    Application::~Application()
    {
        s_Application = nullptr;
    }
    void Application::Run()
    {
        auto lastFrameTime = std::chrono::system_clock::now();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        while (m_running)
        {
            auto currentTime = std::chrono::system_clock::now();
            auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastFrameTime).count() / 1000.0f;
            lastFrameTime = currentTime;
            if (!m_minimized)
            {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                LayerStack::OnUpdate(deltaTime);
            }

            GetWindow().OnUpdate();
        }
    }

    void Application::OnEvent(WindowMinimizeEvent &e)
    {
        m_minimized = true;
        e.handled = true;
    }

    void Application::OnEvent(WindowResizeEvent &e)
    {
        GetWindow().GetSpecifications().width = e.width;
        GetWindow().GetSpecifications().height = e.height;
        m_minimized = false;
        e.handled = true;
    }

    void Application::OnEvent(WindowCloseEvent &e)
    {
        m_running = false;
        e.handled = true;
        LayerStack::OnDetach();
    }

    Application &Application::GetApplication()
    {
        return *s_Application;
    }
}