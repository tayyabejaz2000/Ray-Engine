#pragma once

#include "Core/Core.hpp"
#include "Core/RayObject.hpp"

namespace Ray
{
    class RAYAPI Renderer : public RayObject
    {
    public:
        Renderer();
        ~Renderer() = default;
    };
}