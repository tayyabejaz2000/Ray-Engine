#pragma once

#include "Core/Core.hpp"
#include "Renderer/Texture.hpp"

namespace Ray
{
    struct FramebufferAttachmentSpecification
    {
        Texture::Format Format;

        Texture::Wrap WrappingU = Texture::Wrap::REPEAT;
        Texture::Wrap WrappingV = Texture::Wrap::REPEAT;

        Texture::Filter MinFilter = Texture::Filter::NEAREST;
        Texture::Filter MagFilter = Texture::Filter::NEAREST;

        uint32_t Layers = 1;
    };

    using FramebufferAttachments = std::vector<FramebufferAttachmentSpecification>;

    struct FramebufferSpecification
    {
        uint32_t Width, Height;

        FramebufferAttachments Attachments;

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

        virtual intptr_t GetRendererID() const = 0;

        virtual const FramebufferSpecification &GetSpecification() const = 0;

    public:
        static Ref<Framebuffer> Create(const FramebufferSpecification &);
    };
}