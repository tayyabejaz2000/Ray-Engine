#include <GLFW/glfw3.h>

#include "Core/Input.hpp"
#include "Core/Application.hpp"

#include "LinuxWindow.hpp"
#include "LinuxKeyCodes.hpp"

namespace Ray
{
    MouseVec2 Input::GetMousePosition()
    {
        double x, y;
        GLFWwindow *window = static_cast<GLFWwindow *>(Application::GetApplication().GetWindow().GetNativeWindowHandle());
        glfwGetCursorPos(window, &x, &y);
        return {static_cast<float>(x), static_cast<float>(y)};
    }
    bool Input::IsMouseButtonPressed(MouseButton button)
    {
        GLFWwindow *window = static_cast<GLFWwindow *>(Application::GetApplication().GetWindow().GetNativeWindowHandle());
        auto check = glfwGetMouseButton(window, (int)button);
        return (check == GLFW_PRESS || check == GLFW_REPEAT);
    }
}