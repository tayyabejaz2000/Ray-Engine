#pragma once

#include "Core/Layer.hpp"

namespace Ray
{
    class SandboxLayer : public Layer
    {
    public:
        SandboxLayer();
        virtual ~SandboxLayer();

        virtual void OnUpdate(float delta_time) override;

        virtual void OnEvent(KeyEvent &) override;

    private:
    };
}