#pragma once

#include "Core/Core.hpp"

namespace Ray
{
    class RAYAPI GraphicsContext
    {
    public:
        GraphicsContext() = default;
        virtual ~GraphicsContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

    public:
        static Object<GraphicsContext> Create(void *);
    };
}