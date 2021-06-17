#pragma

#include "Core/Core.hpp"
#include "Renderer/VertexArray.hpp"

namespace Ray::OpenGL
{
    class RAYAPI VertexArray : public Ray::VertexArray
    {
    public:
        VertexArray();
        virtual ~VertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const Ref<Ray::VertexBuffer> &) override;
        virtual void SetIndexBuffer(const Ref<Ray::IndexBuffer> &) override;

    private:
        uid_t m_rendererID;
        uint32_t m_vertexBufferIndex;
    };
}