#pragma once

#include "Renderer/Framebuffer.hpp"
#include "Platform/APIs/OpenGL/Texture.hpp"

namespace Ray::OpenGL
{
    class Framebuffer : public Ray::Framebuffer
    {
    public:
        Framebuffer(const FramebufferSpecification &);
        virtual ~Framebuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void Resize(uint32_t, uint32_t) override;
        virtual void ClearColorAttachment(uint32_t index, int32_t value = 0) override
        {
            if (index < m_colorAttachments.size())
                std::dynamic_pointer_cast<Ray::OpenGL::Texture2D>(m_colorAttachments[index])->Clear(value);
        }
        virtual void ClearDepthAttachment(int32_t value = 0) override
        {
            if (m_depthAttachment)
                std::dynamic_pointer_cast<Ray::OpenGL::Texture2D>(m_depthAttachment)->Clear(value);
        }

        virtual const std::vector<Ref<Ray::Texture2D>> &GetColorAttachments() override { return m_colorAttachments; }
        virtual const Ref<Ray::Texture2D> &GetDepthAttachment() override { return m_depthAttachment; }

        virtual intptr_t GetRendererID() const override { return m_rendererID; }

        virtual const FramebufferSpecification &GetSpecification() const override { return m_specs; }

    private:
        void Invalidate();
        void Release();

    private:
        uid_t m_rendererID;
        FramebufferSpecification m_specs;

        std::vector<Ref<Ray::Texture2D>> m_colorAttachments;
        Ref<Ray::Texture2D> m_depthAttachment;
    };
}