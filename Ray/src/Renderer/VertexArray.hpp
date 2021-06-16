#pragma once

#include "Core/Core.hpp"
#include "Core/RayObject.hpp"

namespace Ray
{
    class VertexArray : public Ray::RayObject
    {
    public:
        VertexArray() = default;
        virtual ~VertexArray() = default;
    };
}