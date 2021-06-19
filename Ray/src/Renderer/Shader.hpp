#pragma once

#include <glm/glm.hpp>

#include "Core/Core.hpp"

namespace Ray
{
    class Shader
    {
    public:
        Shader() = default;
        virtual ~Shader() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

    public:
        template <class... ShaderSources>
        static Ref<Shader> Create(const ShaderSources &...);
    };

    //Takes in string data of shader code (Seperate for OpenGL i.e. Vertex and Fragment Shader in different files)
    template <class... ShaderSources>
    Ref<Shader> Shader::Create(const ShaderSources &...sources)
    {
        return nullptr;
    }
}