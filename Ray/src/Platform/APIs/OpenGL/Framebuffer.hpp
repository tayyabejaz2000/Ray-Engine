#pragma once

#include "Renderer/Framebuffer.hpp"

namespace Ray::OpenGL
{
    class ColorAttachments : public Ray::ColorAttachments
    {
    public:
        ColorAttachments(const ColorAttachmentsSpecifications &);
        virtual ~ColorAttachments();

        virtual void Bind(uint32_t) override;
        virtual void Clear(uint32_t, int32_t = 0) override;

        virtual const ColorAttachmentsSpecifications &GetSpecifications() override { return m_specs; }

    public:
        void Invalidate();
        void Reset();
        void Resize(uint32_t, uint32_t);
        uid_t GetRendererID(uint32_t index) { return m_rendererIDs[index]; }

    private:
        std::vector<uid_t> m_rendererIDs;
        ColorAttachmentsSpecifications m_specs;
    };

    class DepthAttachment : public Ray::DepthAttachment
    {
    public:
        DepthAttachment(const FramebufferAttachmentSpecification &);
        virtual ~DepthAttachment();

        virtual void Bind() override;
        virtual void Clear(int32_t = 0) override;

        virtual const FramebufferAttachmentSpecification &GetSpecification() override { return m_specs; }

    public:
        void Invalidate();
        void Reset();
        void Resize(uint32_t, uint32_t);
        uid_t GetRendererID() { return m_rendererID; }

    private:
        uid_t m_rendererID;
        FramebufferAttachmentSpecification m_specs;
    };

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
            if (m_colorAttachments)
                m_colorAttachments->Clear(index, value);
        }
        virtual void ClearDepthAttachment(int32_t value = 0) override
        {
            if (m_depthAttachment)
                m_depthAttachment->Clear(value);
        }

        virtual const Ref<Ray::ColorAttachments> &GetColorAttachments() override { return m_colorAttachments; }
        virtual const Ref<Ray::DepthAttachment> &GetDepthAttachment() override { return m_depthAttachment; }

        virtual const FramebufferSpecification &GetSpecification() const override { return m_specs; }

    private:
        void Invalidate();
        void Release();

    private:
        uid_t m_rendererID;
        FramebufferSpecification m_specs;

        Ref<ColorAttachments> m_colorAttachments;
        Ref<DepthAttachment> m_depthAttachment;
    };
}