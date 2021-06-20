#include "Renderer/Texture.hpp"
#include "Platform/APIs/OpenGL/Texture.hpp"

namespace Ray
{
    Ref<Texture2D> Texture2D::Create(const Texture2DSpecification &specs)
    {
        return CreateRef<Ray::OpenGL::Texture2D>(specs);
    }
    Ref<Texture2D> Texture2D::Create(const std::string &path)
    {
        return CreateRef<Ray::OpenGL::Texture2D>(path);
    }
}