#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SandboxLayer.hpp"

#include "Platform/APIs/OpenGL/Texture.hpp"

namespace Ray
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec2 texCoord;
        float texIndex = 0.0f;
        float tilingFactor = 1.0f;
    };

    SandboxLayer::SandboxLayer() : Layer()
    {
        Vertex vertices[] = {
            {.position = {0.5f, 0.5f, 0.0f}, .texCoord = {1.0f, 1.0f}, .texIndex = 0.0f, .tilingFactor = 2.0f},
            {.position = {0.5f, -0.5f, 0.0f}, .texCoord = {1.0f, 0.0f}, .texIndex = 0.0f, .tilingFactor = 2.0f},
            {.position = {-0.5f, -0.5f, 0.0f}, .texCoord = {0.0f, 0.0f}, .texIndex = 0.0f, .tilingFactor = 2.0f},
            {.position = {-0.5f, 0.5f, 0.0f}, .texCoord = {0.0f, 1.0f}, .texIndex = 0.0f, .tilingFactor = 2.0f},
        };
        uint32_t indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        m_VAO = VertexArray::Create();

        auto VBO = VertexBuffer::Create(vertices, sizeof(vertices));
        VBO->SetLayout({
            {"a_Position", ShaderDatatype::Float3},
            {"a_TexCoord", ShaderDatatype::Float2},
            {"a_TexIndex", ShaderDatatype::Float},
            {"a_TilingFactor", ShaderDatatype::Float},
        });
        m_VAO->AddVertexBuffer(VBO);

        auto IBO = IndexBuffer::Create(indices, 6);
        m_VAO->SetIndexBuffer(IBO);

        auto vertSource = std::ifstream("Sandbox/assets/Shaders/vert.vs");
        auto fragSource = std::ifstream("Sandbox/assets/Shaders/frag.fs");
        if (!vertSource.is_open() || !fragSource.is_open())
            throw std::runtime_error("Cant Read Vertex or Fragment Shader");

        auto vsSourceReader = std::ostringstream();
        auto fsSourceReader = std::ostringstream();
        vsSourceReader << vertSource.rdbuf();
        fsSourceReader << fragSource.rdbuf();

        m_flatColorShader = Shader::Create(vsSourceReader.str(), fsSourceReader.str());

        auto uniformBufferLayout = UniformBufferLayout{
            {"u_ViewProjection", ShaderDatatype::Mat4},
        };
        m_uniformBuffer = UniformBuffer::Create(uniformBufferLayout, 0);
        m_TileTexture = Texture2D::Create("Sandbox/assets/Textures/OIP.jpg"s);
    }
    SandboxLayer::~SandboxLayer()
    {
    }

    void SandboxLayer::OnUpdate(float delta_time)
    {
        auto transform = glm::mat4(1.0f);
        m_uniformBuffer->SetData(glm::value_ptr(transform));

        m_VAO->Bind();
        m_TileTexture->Bind();
        m_flatColorShader->Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void SandboxLayer::OnEvent(KeyEvent &e)
    {
        std::cout << e.scancode << '\n';
    }
}