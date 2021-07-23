#pragma once

#include "Core/Layer.hpp"

namespace Ray
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
        virtual ~EditorLayer();

        virtual void OnUpdate(float delta_time) override;

        virtual void OnEvent(KeyEvent &) override;

    private:
    };
}