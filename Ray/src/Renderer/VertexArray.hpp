#pragma once

#include "Core/Core.hpp"

#include "Renderer/Buffer.hpp"

namespace Ray
{
    class RAYAPI VertexArray
    {
    public:
        VertexArray() = default;
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer> &) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer> &) = 0;

        virtual intptr_t GetRendererID() const = 0;

    public:
        static Ref<VertexArray> Create();

    protected:
        std::vector<Ref<VertexBuffer>> m_vertexBuffers;
        Ref<IndexBuffer> m_indexBuffer;
    };
}