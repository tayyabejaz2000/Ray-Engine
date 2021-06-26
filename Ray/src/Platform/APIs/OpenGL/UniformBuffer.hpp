#pragma once

#include "Core/Core.hpp"

#include "Renderer/UniformBuffer.hpp"

namespace Ray::OpenGL
{
    class UniformBuffer : public Ray::UniformBuffer
    {
    public:
        UniformBuffer(const UniformBufferLayout &, uint32_t);
        virtual ~UniformBuffer();

        virtual void SetData(void *) override;
        //Set Uniform by Index in Uniform Buffer Layout
        virtual void UpdateUniform(uint32_t, void *) override;
        //Set Uniform by Name in Uniform Buffer Layout
        virtual void UpdateUniform(const std::string &, void *) override;

        virtual const UniformBufferLayout &GetLayout() const override { return m_layout; }

        virtual intptr_t GetRendererID() const override { return m_rendererID; }

    private:
        uid_t m_rendererID;

        ///TODO: Store Size and other data for UniformBufferLayout in its own class instead of being only a std::vector
        UniformBufferLayout m_layout;
        uint32_t m_layoutSize;
    };
}