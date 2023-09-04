#include "ApplicationLayer.hpp"

namespace Ray
{
    ApplicationLayer::ApplicationLayer() : Layer()
    {
    }
    void ApplicationLayer::OnEvent(KeyEvent &e)
    {
        if (e.GetEventType() == KEY_PRESSED_EVENT)
        {
            auto &keyPressed = dynamic_cast<KeyPressedEvent &>(e);
            if (keyPressed.modifier == KeyModifier::CTRL && keyPressed.keycode == Key::KEY_Q)
                Application::GetApplication().GetWindow().Close();
        }
    }
    void ApplicationLayer::OnEvent(WindowCloseEvent &e)
    {
        Application::GetApplication().OnEvent(e);
    }
    void ApplicationLayer::OnEvent(WindowResizeEvent &e)
    {
        Application::GetApplication().OnEvent(e);
    }
    void ApplicationLayer::OnEvent(WindowMinimizeEvent &e)
    {
        Application::GetApplication().OnEvent(e);
    }
}