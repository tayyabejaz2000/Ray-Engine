#pragma once

#include "Core/Core.hpp"
#include "Core/RayObject.hpp"

namespace Ray
{
    class RAYAPI GraphicsContext : public RayObject
    {
    public:
        GraphicsContext() = default;
        virtual ~GraphicsContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        static Object<GraphicsContext> Create(void *);
    };
}