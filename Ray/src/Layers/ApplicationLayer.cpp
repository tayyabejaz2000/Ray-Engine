#include "ApplicationLayer.hpp"

namespace Ray
{
    ApplicationLayer::ApplicationLayer() : Layer()
    {
    }
    void ApplicationLayer::OnEvent(WindowCloseEvent &e)
    {
        Application::GetApplication()->OnEvent(e);
    }
    void ApplicationLayer::OnEvent(WindowResizeEvent &e)
    {
        Application::GetApplication()->OnEvent(e);
    }
    void ApplicationLayer::OnEvent(WindowMinimizeEvent &e)
    {
        Application::GetApplication()->OnEvent(e);
    }
}