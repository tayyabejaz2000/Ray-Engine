#include <glad/glad.h>

#include "GraphicsContext.hpp"

namespace Ray::OpenGL
{
    GraphicsContext::GraphicsContext(void *window) : m_windowHandle(static_cast<GLFWwindow *>(window))
    {
    }
    GraphicsContext::~GraphicsContext()
    {
    }
    void GraphicsContext::Init()
    {
        glfwMakeContextCurrent(m_windowHandle);
        auto status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!status)
            throw std::runtime_error("Failed to initialize GLAD");
        std::cout << "OpenGL Version: " << GLVersion.major << '.' << GLVersion.minor << '\n';
    }
    void GraphicsContext::SwapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }
}