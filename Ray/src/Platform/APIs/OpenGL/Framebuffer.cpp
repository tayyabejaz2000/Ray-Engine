#include "Platform/APIs/OpenGL/Texture.hpp"
#include "Platform/APIs/OpenGL/Framebuffer.hpp"

namespace Ray::OpenGL
{
    Framebuffer::Framebuffer(const FramebufferSpecification &specs) : m_rendererID(0), m_specs(specs), m_depthAttachment(uint32_t(-1))
    {
        Invalidate();
    }
    Framebuffer::~Framebuffer()
    {
        Release();
    }
    void Framebuffer::AttachColorTexture(uint32_t rendererID, uint32_t index, RenderTextureSpecification specs, bool multisampled)
    {
        auto target = (multisampled) ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
        if (multisampled)
        {
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_specs.Samples,
                                    TextureSpecificationToGLTypes::GetTextureFormat(specs.Format),
                                    m_specs.Width, m_specs.Height,
                                    GL_FALSE);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0,
                         TextureSpecificationToGLTypes::GetTextureFormat(specs.Format),
                         m_specs.Width, m_specs.Height, 0,
                         TextureSpecificationToGLTypes::GetTextureDataFormat(specs.Format),
                         GL_UNSIGNED_BYTE, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, TextureSpecificationToGLTypes::GetTextureWrapping(specs.WrappingR));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureSpecificationToGLTypes::GetTextureWrapping(specs.WrappingS));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureSpecificationToGLTypes::GetTextureWrapping(specs.WrappingT));
        }
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, target, rendererID, 0);
    }
    void Framebuffer::AttachDepthTexture(uint32_t rendererID, RenderTextureSpecification specs, bool multisampled)
    {
        auto target = (multisampled) ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
        if (multisampled)
        {
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_specs.Samples,
                                    TextureSpecificationToGLTypes::GetTextureFormat(specs.Format),
                                    m_specs.Width, m_specs.Height,
                                    GL_FALSE);
        }
        else
        {
            glTexStorage2D(GL_TEXTURE_2D, 1,
                           TextureSpecificationToGLTypes::GetTextureFormat(specs.Format),
                           m_specs.Width, m_specs.Height);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, TextureSpecificationToGLTypes::GetTextureWrapping(specs.WrappingR));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureSpecificationToGLTypes::GetTextureWrapping(specs.WrappingS));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureSpecificationToGLTypes::GetTextureWrapping(specs.WrappingT));
        }

        switch (specs.Format)
        {
        case TextureFormat::STENCIL8:
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, target, rendererID, 0);
            break;
        case TextureFormat::DEPTH24STENCIL8:
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, target, rendererID, 0);
            break;
        case TextureFormat::DEPTH32:
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, target, rendererID, 0);
            break;
        default:
            throw std::runtime_error("Unsupported Depth Attachment");
        }
    }
    void Framebuffer::Invalidate()
    {
        if (m_rendererID)
            Release();
        auto &textureSpecs = m_specs.RenderTexturesSpecs;

        for (auto &textureSpec : textureSpecs)
        {
            switch (textureSpec.Format)
            {
            case TextureFormat::R8... TextureFormat::RGBA32F:
                m_colorAttachmentsSpecs.push_back(textureSpec);
                break;
            case TextureFormat::STENCIL8... TextureFormat::DEPTH32:
                m_depthAttachmentSpecs = textureSpec;
                m_depthAttachment = 0;
                break;
            }
        }

        m_colorAttachments.resize(m_colorAttachmentsSpecs.size());

        glCreateFramebuffers(1, &m_rendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);

        bool multisample = m_specs.Samples > 1;
        auto target = (multisample) ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;

        glCreateTextures(target, m_colorAttachments.size(), m_colorAttachments.data());
        glCreateTextures(target, 1, &m_depthAttachment);

        auto i = 0u;
        for (auto &colorAttachmentSpec : m_colorAttachmentsSpecs)
        {
            glBindTexture(target, m_colorAttachments[i]);
            AttachColorTexture(m_colorAttachments[i], i, colorAttachmentSpec, multisample);
            ++i;
        }
        if (m_depthAttachment == 0u)
        {
            glBindTexture(target, m_depthAttachment);
            AttachDepthTexture(m_depthAttachment, m_depthAttachmentSpecs, multisample);
        }

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            throw std::runtime_error("Framebuffer is Incomplete");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void Framebuffer::Release()
    {
        glDeleteFramebuffers(1, &m_rendererID);
        glDeleteTextures(m_colorAttachments.size(), m_colorAttachments.data());
        glDeleteTextures(1, &m_depthAttachment);

        m_colorAttachments.clear();
        m_rendererID = 0;
        m_depthAttachment = uint32_t(-1);
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
        m_specs.Width = width;
        m_specs.Height = height;

        Invalidate();
    }
    void Framebuffer::ClearColorAttachment(uint32_t index, int32_t value)
    {
        glClearTexImage(m_colorAttachments[index], 0,
                        TextureSpecificationToGLTypes::GetTextureFormat(m_colorAttachmentsSpecs[index].Format),
                        GL_INT, &value);
    }
}