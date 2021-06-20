#include "Renderer/Shader.hpp"
#include "Platform/APIs/OpenGL/Shader.hpp"

namespace Ray
{
    Ref<Shader> Shader::Create(const std::string &vsSource, const std::string &fsSource)
    {
        return CreateRef<Ray::OpenGL::Shader>(vsSource, fsSource);
    }
}