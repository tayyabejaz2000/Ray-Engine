#include "stb_image.h"
#include "Platform/APIs/OpenGL/Texture.hpp"

namespace Ray::OpenGL
{
    uint8_t TextureSpecificationToGLTypes::s_formatLookup[] = {
        [TextureFormat::R8] = GL_R8,
        [TextureFormat::R8I] = GL_R8I,
        [TextureFormat::R32F] = GL_R32F,

        [TextureFormat::RG8] = GL_RG8,
        [TextureFormat::RG8I] = GL_RG8I,
        [TextureFormat::RG32F] = GL_RG32F,

        [TextureFormat::RGB8] = GL_RGB8,
        [TextureFormat::RGB32F] = GL_RGB32F,

        [TextureFormat::RGBA8] = GL_RGBA8,
        [TextureFormat::RGBA16] = GL_RGBA16,
        [TextureFormat::RGBA16F] = GL_RGBA16F,
        [TextureFormat::RGB32I] = GL_RGB32I,
        [TextureFormat::RGBA32F] = GL_RGBA32F,

        [TextureFormat::STENCIL8] = GL_STENCIL_INDEX8,
        [TextureFormat::DEPTH24STENCIL8] = GL_DEPTH24_STENCIL8,
        [TextureFormat::DEPTH32] = GL_DEPTH_COMPONENT32F, //Check this either GL_DEPTH or GL_DEPTH_COMPONENT32F
    };

    uint32_t TextureSpecificationToGLTypes::GetTextureWrapping(const TextureWrap &wrapping)
    {
        switch (wrapping)
        {
        case TextureWrap::REPEAT:
            return GL_REPEAT;
        case TextureWrap::MIRRORED_REPEAT:
            return GL_MIRRORED_REPEAT;
        case TextureWrap::CLAMP_TO_EDGE:
            return GL_CLAMP_TO_EDGE;
        case TextureWrap::MIRROR_CLAMP_TO_EDGE:
            return GL_MIRROR_CLAMP_TO_EDGE;
        case TextureWrap::CLAMP_TO_BORDER:
            return GL_CLAMP_TO_BORDER;
        }
    }
    static uint32_t GetTextureDataFormat(const TextureFormat &format)
    {
        switch (format)
        {
        case TextureFormat::R8... TextureFormat::R32F:
            return GL_RED;
        case TextureFormat::RG8... TextureFormat::RG32F:
            return GL_RG;
        case TextureFormat::RGB8... TextureFormat::RGB32F:
            return GL_RGB;
        case TextureFormat::RGBA8... TextureFormat::RGBA32F:
            return GL_RGBA;
        case TextureFormat::STENCIL8:
            return GL_STENCIL;
        case TextureFormat::DEPTH24STENCIL8:
            return GL_DEPTH_STENCIL;
        case TextureFormat::DEPTH32:
            return GL_DEPTH;
        };
    }

    Texture2D::Texture2D(const Texture2DSpecification &specs) : m_specs(specs)
    {
        auto internalFormat = TextureSpecificationToGLTypes::GetTextureFormat(m_specs.Format);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
        glTextureStorage2D(m_rendererID, 1, internalFormat, m_specs.Width, m_specs.Height);

        glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, TextureSpecificationToGLTypes::GetTextureWrapping(m_specs.WrappingS));
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, TextureSpecificationToGLTypes::GetTextureWrapping(m_specs.WrappingT));
    }
    Texture2D::Texture2D(const std::string &path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc *data = nullptr;
        data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (!data)
            throw std::runtime_error("Failed to load Image");

        m_specs.Width = width;
        m_specs.Height = height;
        uint32_t internalFormat = 0, dataFormat = 0;
        switch (channels)
        {
        case 3:
            dataFormat = GL_RGB;
            internalFormat = GL_RGB8;
            break;
        case 4:
            dataFormat = GL_RGBA;
            internalFormat = GL_RGBA8;
            break;
        case 2:
            dataFormat = GL_RG;
            internalFormat = GL_RG8;
            break;
        case 1:
            dataFormat = GL_RED;
            internalFormat = GL_R8;
            break;
        }

        if (!(internalFormat & dataFormat))
            throw std::runtime_error("Format not Supported");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
        glTextureStorage2D(m_rendererID, 1, internalFormat, m_specs.Width, m_specs.Height);

        glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_rendererID, 0, 0, 0, m_specs.Width, m_specs.Height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_rendererID);
    }

    void Texture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_rendererID);
    }

    void Texture2D::SetData(void *data, uint32_t size)
    {
        auto dataFormat = TextureSpecificationToGLTypes::GetTextureDataFormat(m_specs.Format);
        auto bpp = (dataFormat == GL_RGBA) ? 4u : 3u;
        if (size != m_specs.Width * m_specs.Height * bpp)
            throw std::runtime_error("Data must be entire Texture");
        glTextureSubImage2D(m_rendererID, 0, 0, 0, m_specs.Width, m_specs.Height, dataFormat, GL_UNSIGNED_BYTE, data);
    }

    void Texture2D::Clear(uint32_t value)
    {
        glClearTexImage(m_rendererID, 0,
                        TextureSpecificationToGLTypes::GetTextureFormat(m_specs.Format),
                        GL_INT, &value);
    }
}