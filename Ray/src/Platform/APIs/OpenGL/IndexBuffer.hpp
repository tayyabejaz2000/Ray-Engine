#pragma once

#include "Core/Core.hpp"
#include "Renderer/Buffer.hpp"

namespace Ray::OpenGL
{
    class RAYAPI IndexBuffer : public Ray::IndexBuffer
    {
    public:
        IndexBuffer(void *, std::size_t);
        virtual ~IndexBuffer();

    public:
        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetIndices(void *, std::size_t) override;

        virtual intptr_t GetRendererID() const override { return m_rendererID; }

    private:
        uid_t m_rendererID;
    };
}