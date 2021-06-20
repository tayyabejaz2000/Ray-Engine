#include "Renderer/Framebuffer.hpp"
#include "Platform/APIs/OpenGL/Framebuffer.hpp"

namespace Ray
{
    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification &specs)
    {
        return CreateRef<Ray::OpenGL::Framebuffer>(specs);
    }
}