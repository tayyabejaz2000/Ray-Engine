#pragma once

#include <GLFW/glfw3.h>

#include "Renderer/GraphicsContext.hpp"

namespace Ray::OpenGL
{
    class RAYAPI GraphicsContext : public Ray::GraphicsContext
    {
    public:
        GraphicsContext(void *);
        virtual ~GraphicsContext();

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow *m_windowHandle;
    };
}