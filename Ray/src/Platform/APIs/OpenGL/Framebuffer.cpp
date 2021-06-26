#include "Platform/APIs/OpenGL/Texture.hpp"
#include "Platform/APIs/OpenGL/Framebuffer.hpp"

namespace Ray::OpenGL
{
    Framebuffer::Framebuffer(const FramebufferSpecification &specs)
        : m_rendererID(0), m_specs(specs),
          m_colorAttachments(),
          m_depthAttachment(nullptr)
    {
        Invalidate();
    }

    Framebuffer::~Framebuffer()
    {
        Release();
    }

    void Framebuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
        glViewport(0, 0, m_specs.Width, m_specs.Height);
    }
    void Framebuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void Framebuffer::Resize(uint32_t width, uint32_t height)
    {
        for (auto &colorAttachment : m_colorAttachments)
            std::dynamic_pointer_cast<Ray::OpenGL::Texture2D>(colorAttachment)->Resize(width, height);
        if (m_depthAttachment)
            std::dynamic_pointer_cast<Ray::OpenGL::Texture2D>(m_depthAttachment)->Resize(width, height);

        m_specs.Width = width;
        m_specs.Height = height;
        Invalidate();
    }
    void Framebuffer::Invalidate()
    {
        if (m_rendererID)
            Release();
        glCreateFramebuffers(1, &m_rendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
        auto colorAttachmentIndex = 0u;
        for (auto &attachmentSpecs : m_specs.Attachments)
        {
            Texture2DSpecification spec{
                .Width = m_specs.Width,
                .Height = m_specs.Height,
                .Format = attachmentSpecs.Format,
                .WrappingU = attachmentSpecs.WrappingU,
                .WrappingV = attachmentSpecs.WrappingV,
                .MinFilter = attachmentSpecs.MinFilter,
                .MagFilter = attachmentSpecs.MagFilter,
                .Mipmaps = 0, //Will be zero for all Framebuffer attachments
            };
            if (spec.Format == Texture::Format::DEPTH || spec.Format == Texture::Format::DEPTH_STENCIL)
            {
                if (m_depthAttachment)
                    throw std::runtime_error("There can only be 1 Depth Attachment to a Framebuffer");
                m_depthAttachment = CreateRef<Ray::OpenGL::Texture2D>(spec, m_specs.Samples);
                auto attachmentID = static_cast<uint32_t>(m_depthAttachment->GetRendererID());
                glFramebufferTexture2D(GL_FRAMEBUFFER,
                                       spec.Format == Texture::Format::DEPTH ? GL_DEPTH_ATTACHMENT : GL_DEPTH_STENCIL_ATTACHMENT,
                                       (m_specs.Samples > 1) ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D,
                                       attachmentID, 0);
            }
            else
            {
                m_colorAttachments.push_back(CreateRef<Ray::OpenGL::Texture2D>(spec, m_specs.Samples));

                auto attachmentID = static_cast<uint32_t>(m_colorAttachments.back()->GetRendererID());
                glFramebufferTexture2D(GL_FRAMEBUFFER,
                                       GL_COLOR_ATTACHMENT0 + colorAttachmentIndex,
                                       (m_specs.Samples > 1) ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D,
                                       attachmentID, 0);
                ++colorAttachmentIndex;
            }
        }
    }
    void Framebuffer::Release()
    {
        glDeleteFramebuffers(1, &m_rendererID);
        m_rendererID = 0;
        m_colorAttachments.clear();
        m_depthAttachment.reset();
    }
}