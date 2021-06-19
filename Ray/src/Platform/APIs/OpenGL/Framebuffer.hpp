#pragma once

#include "Renderer/Framebuffer.hpp"

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
        virtual void ClearAttachment(uint32_t, int32_t) override;

        virtual const FramebufferSpecification &GetSpecification() const override;

    private:
        void Invalidate();
        void Release();

        void AttachColorTexture(uint32_t, uint32_t, RenderTextureSpecification, bool = false);
        void AttachDepthTexture(uint32_t, RenderTextureSpecification, bool = false);

    private:
        uid_t m_rendererID;
        FramebufferSpecification m_specs;

        ///TODO: Create RenderTexture class and hold its Reference
        std::vector<uid_t> m_colorAttachments;
        uid_t m_depthAttachment;
    };
}