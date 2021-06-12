#pragma once

#include "Core/Layer.hpp"
#include "Core/Application.hpp"

namespace Ray
{
    //Core Application
    class RAYAPI ApplicationLayer : public Layer
    {
    public:
        ApplicationLayer();
        virtual ~ApplicationLayer() = default;

        //virtual void OnUpdate(float delta_time) override;
        virtual void OnEvent(WindowCloseEvent &e) override;
        virtual void OnEvent(WindowResizeEvent &e) override;
        virtual void OnEvent(WindowMinimizeEvent &e) override;
    };
}