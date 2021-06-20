#pragma once

#include "Ray.hpp"

namespace Ray
{
    struct ParticleVertex
    {
        glm::vec3 position = glm::vec3(0.0f, 1.0f, 0.0f);
        void Reset()
        {
            position = glm::vec3(0, 0, 0);
        }
    };

    class SandboxLayer : public Layer
    {
    public:
        SandboxLayer();
        virtual ~SandboxLayer();

        virtual void OnUpdate(float delta_time) override;

        virtual void OnEvent(KeyEvent &) override;

    private:
        Ref<Shader> m_particleShader;

        Ref<VertexArray> m_VAO;
        Ref<VertexBuffer> m_VBO;
        Ref<UniformBuffer> m_uniformBuffer[2];

        uint32_t frames = 0;

        std::mt19937 rand_dev;
        std::uniform_real_distribution<float> dist;

        std::vector<ParticleVertex> particlesBuffer;
        std::vector<glm::mat4> transforms;
    };
}