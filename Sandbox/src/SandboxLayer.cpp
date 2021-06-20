#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SandboxLayer.hpp"

#include "Core/Input.hpp"
#include "Platform/APIs/OpenGL/Texture.hpp"

#include <GL/gl.h>

namespace Ray
{
    static const auto maxBufferSize = 100000u;
    SandboxLayer::SandboxLayer() : Layer(), rand_dev(std::random_device{}()), dist(0.0f, 1.0f)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPointSize(2.0f);

        particlesBuffer.resize(maxBufferSize, ParticleVertex{});
        transforms.resize(maxBufferSize, glm::mat4(1.0f));

        m_VAO = VertexArray::Create();
        m_VBO = VertexBuffer::Create(maxBufferSize * sizeof(ParticleVertex));

        m_VBO->SetLayout({
            {"a_Position", ShaderDatatype::Float3},
        });

        m_VBO->SetData(particlesBuffer.data(), particlesBuffer.size() * sizeof(ParticleVertex));

        m_VAO->AddVertexBuffer(m_VBO);

        auto vertSource = std::ifstream("Sandbox/assets/Shaders/Particle.vs");
        auto fragSource = std::ifstream("Sandbox/assets/Shaders/Particle.fs");
        if (!vertSource.is_open() || !fragSource.is_open())
            throw std::runtime_error("Cant Read Vertex or Fragment Shader");

        auto vsSourceReader = std::ostringstream();
        auto fsSourceReader = std::ostringstream();
        vsSourceReader << vertSource.rdbuf();
        fsSourceReader << fragSource.rdbuf();

        m_particleShader = Shader::Create(vsSourceReader.str(), fsSourceReader.str());

        m_uniformBuffer[0] = UniformBuffer::Create({{"u_ViewProjection", ShaderDatatype::Mat4}}, 0);
        m_uniformBuffer[1] = UniformBuffer::Create({{"u_Color", ShaderDatatype::Float4}}, 1);

        auto color = glm::vec4(0.0f, 0.5f, 0.8f, 1.0f);
        m_uniformBuffer[1]->SetData(glm::value_ptr(color));
    }
    SandboxLayer::~SandboxLayer()
    {
    }

    void SandboxLayer::OnUpdate(float delta_time)
    {
        auto transform = glm::mat4(1.0f);
        m_uniformBuffer[0]->SetData(glm::value_ptr(transform));
        auto i = 0;

        if (Input::IsMouseButtonPressed(MouseButton::BUTTON_LEFT))
        {
            auto pos = Input::GetMousePosition();
            auto screenX = Application::GetApplication().GetWindow().GetSpecifications().width;
            auto screenY = Application::GetApplication().GetWindow().GetSpecifications().height;
            auto mousePos = glm::vec2(((pos.x) / screenX) * 2.0f - 1.0f, ((screenY - pos.y) / screenY) * 2.0f - 1.0f);
            for (auto &point : particlesBuffer)
            {
                point.position.y -= dist(rand_dev) * 0.08f;

                if (rand_dev() % 2 == 0)
                    point.position.x += dist(rand_dev) * 0.05f;
                else
                    point.position.x -= dist(rand_dev) * 0.05f;

                auto distance = glm::distance(mousePos, glm::vec2(point.position));
                if (point.position.y < -1.0f)
                    point.position = glm::vec3(0.0f, -point.position.y, 0.0f);
                else if (distance < 0.1f)
                    point.position = glm::vec3(0.0f, 1.0f, 0.0f);
                ++i;
            }
        }
        else
        {
            for (auto &point : particlesBuffer)
            {
                if (rand_dev() % 2 == 0)
                    point.position.x += dist(rand_dev) * 0.05f;
                else
                    point.position.x -= dist(rand_dev) * 0.05f;
                point.position.y -= dist(rand_dev) * 0.1f;
                if (point.position.y < -1.0f)
                    point.position = glm::vec3(0.0f, -point.position.y, 0.0f);
                ++i;
            }
        }

        m_VBO->SetData(particlesBuffer.data(), particlesBuffer.size() * sizeof(ParticleVertex));
        m_VAO->Bind();
        m_particleShader->Bind();
        glDrawArrays(GL_POINTS, 0, maxBufferSize);
    }

    void SandboxLayer::OnEvent(KeyEvent &e)
    {
        std::cout << e.scancode << '\n';
    }

}