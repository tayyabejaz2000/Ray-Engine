#pragma once

#include "Core/Core.hpp"
#include "Renderer/Texture.hpp"

namespace Ray
{
    using TextureAttachmentsSpecifications = std::vector<Texture2DSpecification>;

    struct FramebufferSpecification
    {
        uint32_t Width, Height;

        TextureAttachmentsSpecifications RenderTexturesSpecs;

        uint32_t Samples = 1;
    };

    class Framebuffer
    {
    public:
        Framebuffer() = default;
        virtual ~Framebuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void Resize(uint32_t, uint32_t) = 0;

        virtual void ClearAttachment(uint32_t) = 0;
        virtual std::vector<Texture2D> GetColorAttachments() = 0;
        virtual std::vector<Texture2D> GetDepthAttachments() = 0;

        virtual const FramebufferSpecification &GetSpecification() const = 0;

    public:
        static Ref<Framebuffer> Create(const FramebufferSpecification &);
    };
}