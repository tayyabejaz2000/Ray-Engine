#include "GraphicsContext.hpp"

#include "Platform/APIs/OpenGL/GraphicsContext.hpp"

namespace Ray
{
    Object<GraphicsContext> GraphicsContext::Create(void *window)
    {
        return CreateObject<Ray::OpenGL::GraphicsContext>(window);
    }
}