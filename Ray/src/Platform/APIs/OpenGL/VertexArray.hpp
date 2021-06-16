#pragma

#include "Core/Core.hpp"
#include "Renderer/VertexArray.hpp"

namespace Ray::OpenGL
{
    class VertexArray : public Ray::VertexArray
    {
    public:
        VertexArray() = default;
        virtual ~VertexArray() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer> &) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer> &) = 0;

    public:
        static Ref<VertexArray> Create();
    };
}