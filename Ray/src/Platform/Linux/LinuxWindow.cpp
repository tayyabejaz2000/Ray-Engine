#include "LinuxWindow.hpp"

#include <glad/glad.h>

#include "LinuxKeyCodes.hpp"
#include "Events/KeyEvents.hpp"
#include "Events/MouseEvents.hpp"
#include "Events/WindowEvents.hpp"
#include "Events/EventDispatcher.hpp"

namespace Ray
{
    void RAYAPI GLDebugProc(uint32_t source,
                            uint32_t type,
                            uint32_t id,
                            uint32_t severity,
                            int length,
                            const char *message,
                            const void *userParam)
    {
        std::cout << "---------------------opengl-callback-start---------------------\n";
        std::cout << "message: " << message << '\n';
        std::cout << "type: ";
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "DEPRECATED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "UNDEFINED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "PORTABILITY";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "OTHER";
            break;
        }
        std::cout << "\nid: " << id << '\n';
        std::cout << "severity: ";
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "LOW";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "HIGH";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << "NOTIFICATION";
            break;
        default:
            std::cout << "INFO";
            break;
        }
        std::cout << "\n---------------------opengl-callback-end---------------------\n";
    }

    LinuxWindow::LinuxWindow(const WindowSpecifications &w) : Window(w)
    {
        Init(w);
    }
    LinuxWindow::~LinuxWindow()
    {
        Shutdown();
        glfwTerminate();
    }
    void LinuxWindow::VSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        m_specs.vsync = enabled;
    }
    void LinuxWindow::OnUpdate()
    {
        m_context->SwapBuffers();
        glfwPollEvents();
    }
    bool LinuxWindow::IsRunning()
    {
        return !(glfwWindowShouldClose(m_windowHandle));
    }
    void *LinuxWindow::GetNativeWindowHandle()
    {
        return reinterpret_cast<void *>(m_windowHandle);
    }
    void LinuxWindow::InitGLFW()
    {
        if (!glfwInit())
            throw std::runtime_error("Failed to Initialize GLFW");
    }
    void LinuxWindow::Init(const WindowSpecifications &specs)
    {
        InitGLFW();

        glfwSetErrorCallback([](int errorCode, const char *log)
                             { std::cout << log << '\n'; });

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_SAMPLES, (int)m_specs.samples);            //Setup Anti-Aliasing Samples
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Setup OpenGL Core Profile

#ifdef RAY_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        if (glDebugMessageCallback)
            glDebugMessageCallback(GLDebugProc, NULL);
#endif

        m_windowHandle = glfwCreateWindow(
            m_specs.width,        //Width of Window
            m_specs.height,       //Height of Window
            m_specs.title.data(), //Title of Window
            nullptr,              //Monitor to display the window (nullptr in this case)
            nullptr);             //Parent for current Window (nullptr in this case)

        m_context = GraphicsContext::Create(m_windowHandle);
        m_context->Init();

        if (glfwRawMouseMotionSupported())
            glfwSetInputMode(m_windowHandle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        glfwSetKeyCallback(m_windowHandle, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                           {
                               switch (action)
                               {
                               case GLFW_PRESS:
                               {
                                   KeyPressedEvent e(RayKeyCast(key), scancode, RayKeyModifierCast(mods), 0);
                                   EventDispatcher::GetEventDispatcher()->Dispatch(e);
                               }
                               break;
                               case GLFW_RELEASE:
                               {
                                   KeyReleasedEvent e(RayKeyCast(key), scancode, RayKeyModifierCast(mods));
                                   EventDispatcher::GetEventDispatcher()->Dispatch(e);
                               }
                               break;
                               case GLFW_REPEAT:
                               {
                                   KeyPressedEvent e(RayKeyCast(key), scancode, RayKeyModifierCast(mods), 1);
                                   EventDispatcher::GetEventDispatcher()->Dispatch(e);
                               }
                               break;
                               };
                           });

        glfwSetCharCallback(m_windowHandle, [](GLFWwindow *window, uint scancode)
                            {
                                KeyTypedEvent e(scancode);
                                EventDispatcher::GetEventDispatcher()->Dispatch(e);
                            });

        glfwSetMouseButtonCallback(m_windowHandle, [](GLFWwindow *window, int button, int action, int mods)
                                   {
                                       double x, y;
                                       glfwGetCursorPos(window, &x, &y);
                                       MouseVec2 mousePos{static_cast<float>(x), static_cast<float>(y)};
                                       if (action == GLFW_PRESS)
                                       {
                                           MouseButtonPressedEvent e(mousePos, RayMouseButtonCast(button), RayKeyModifierCast(mods));
                                           EventDispatcher::GetEventDispatcher()->Dispatch(e);
                                       }
                                       else if (action == GLFW_RELEASE)
                                       {
                                           MouseButtonReleasedEvent e(mousePos, RayMouseButtonCast(button), RayKeyModifierCast(mods));
                                           EventDispatcher::GetEventDispatcher()->Dispatch(e);
                                       }
                                   });
        glfwSetScrollCallback(m_windowHandle, [](GLFWwindow *window, double xOffset, double yOffset)
                              {
                                  double x, y;
                                  glfwGetCursorPos(window, &x, &y);
                                  MouseScrolledEvent e(
                                      {static_cast<float>(x), static_cast<float>(y)},
                                      {static_cast<float>(xOffset), static_cast<float>(yOffset)});
                                  EventDispatcher::GetEventDispatcher()->Dispatch(e);
                              });

        glfwSetWindowSizeCallback(m_windowHandle, [](GLFWwindow *window, int width, int height)
                                  {
                                      if (width & height == 0)
                                      {
                                          WindowMinimizeEvent e;
                                          EventDispatcher::GetEventDispatcher()->Dispatch(e);
                                      }
                                      else
                                      {
                                          WindowResizeEvent e((uint16_t)width, (uint16_t)height);
                                          EventDispatcher::GetEventDispatcher()->Dispatch(e);
                                      }
                                  });

        glfwSetWindowCloseCallback(m_windowHandle, [](GLFWwindow *window)
                                   {
                                       WindowCloseEvent e;
                                       EventDispatcher::GetEventDispatcher()->Dispatch(e);
                                   });

        VSync(m_specs.vsync);
    }
    void LinuxWindow::Shutdown()
    {
        if (m_windowHandle)
        {
            glfwDestroyWindow(m_windowHandle);
            m_windowHandle = nullptr;
        }
    }
}