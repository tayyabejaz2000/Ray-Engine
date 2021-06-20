#pragma once

#include "Core/Core.hpp"
#include "Renderer/Texture.hpp"

namespace Ray
{
    struct FramebufferAttachmentSpecification
    {
        Texture::Format Format;

        Texture::Wrap WrappingR = Texture::Wrap::CLAMP_TO_EDGE;
        Texture::Wrap WrappingS = Texture::Wrap::CLAMP_TO_EDGE;
        Texture::Wrap WrappingT = Texture::Wrap::CLAMP_TO_EDGE;

        Texture::Filter MinFilter = Texture::Filter::LINEAR;
        Texture::Filter MagFilter = Texture::Filter::LINEAR;

        struct
        {
            uint32_t width = 0, height = 0;
            uint32_t samples = 0;
        } framebufferSpecs;
    };
    using ColorAttachmentsSpecifications = std::vector<FramebufferAttachmentSpecification>;

    class ColorAttachments
    {
    public:
        ColorAttachments() = default;
        virtual ~ColorAttachments() = default;

        virtual void Bind(uint32_t) = 0;

        virtual void Clear(uint32_t, int32_t = 0) = 0;

        virtual const ColorAttachmentsSpecifications &GetSpecifications() = 0;

    public:
        static Ref<ColorAttachments> Create(const ColorAttachmentsSpecifications &);
    };

    class DepthAttachment
    {
    public:
        DepthAttachment() = default;
        virtual ~DepthAttachment() = default;

        virtual void Bind() = 0;

        virtual void Clear(int32_t = 0) = 0;

        virtual const FramebufferAttachmentSpecification &GetSpecification() = 0;

    public:
        static Ref<DepthAttachment> Create(const FramebufferAttachmentSpecification &);
    };

    struct FramebufferSpecification
    {
        uint32_t Width, Height;
        std::optional<ColorAttachmentsSpecifications> ColorAttachmentsSpecs = std::nullopt;
        std::optional<FramebufferAttachmentSpecification> DepthAttachmentSpecs = std::nullopt;
        uint32_t Samples = 1;

        bool SwapChainTarget = false;
    };

    class Framebuffer
    {
    public:
        Framebuffer() = default;
        virtual ~Framebuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void Resize(uint32_t, uint32_t) = 0;
        virtual void ClearColorAttachment(uint32_t, int32_t = 0) = 0;
        virtual void ClearDepthAttachment(int32_t = 0) = 0;

        virtual const Ref<ColorAttachments> &GetColorAttachments() = 0;
        virtual const Ref<DepthAttachment> &GetDepthAttachment() = 0;

        virtual const FramebufferSpecification &GetSpecification() const = 0;

    public:
        static Ref<Framebuffer> Create(const FramebufferSpecification &);
    };
}