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

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual intptr_t GetRendererID() const = 0;

    public:
        static Ref<Shader> Create(const std::string &, const std::string &);
    };
}