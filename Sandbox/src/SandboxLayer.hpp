#pragma once

#include "Ray.hpp"

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
        Ref<VertexArray> m_VAO;
        Ref<Shader> m_flatColorShader;
        Ref<UniformBuffer> m_uniformBuffer;
        Ref<Texture2D> m_TileTexture;
    };
}