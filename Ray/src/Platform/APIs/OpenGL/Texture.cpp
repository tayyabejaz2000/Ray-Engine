#include "stb_image.h"
#include "Platform/APIs/OpenGL/Texture.hpp"

namespace Ray::OpenGL
{
    uint32_t TextureSpecificationToGLTypes::s_formatLookup[] = {
        [(uint32_t)Ray::Texture::Format::R8] = GL_R8,
        [(uint32_t)Ray::Texture::Format::R8I] = GL_R8I,
        [(uint32_t)Ray::Texture::Format::R32I] = GL_R32I,
        [(uint32_t)Ray::Texture::Format::R32F] = GL_R32F,

        [(uint32_t)Ray::Texture::Format::RG8] = GL_RG8,
        [(uint32_t)Ray::Texture::Format::RG8I] = GL_RG8I,
        [(uint32_t)Ray::Texture::Format::RG32I] = GL_RG32I,
        [(uint32_t)Ray::Texture::Format::RG32F] = GL_RG32F,

        [(uint32_t)Ray::Texture::Format::RGB8] = GL_RGB8,
        [(uint32_t)Ray::Texture::Format::RGB8I] = GL_RGB8I,
        [(uint32_t)Ray::Texture::Format::RGB32I] = GL_RGB32I,
        [(uint32_t)Ray::Texture::Format::RGB32F] = GL_RGB32F,

        [(uint32_t)Ray::Texture::Format::RGBA8] = GL_RGBA8,
        [(uint32_t)Ray::Texture::Format::RGBA8I] = GL_RGBA8I,
        [(uint32_t)Ray::Texture::Format::RGBA16] = GL_RGBA16,
        [(uint32_t)Ray::Texture::Format::RGBA16F] = GL_RGBA16F,
        [(uint32_t)Ray::Texture::Format::RGBA32I] = GL_RGBA32I,
        [(uint32_t)Ray::Texture::Format::RGBA32F] = GL_RGBA32F,

        [(uint32_t)Ray::Texture::Format::DEPTH] = GL_DEPTH_COMPONENT,
        [(uint32_t)Ray::Texture::Format::DEPTH_STENCIL] = GL_DEPTH_STENCIL,
    };
    uint8_t TextureSpecificationToGLTypes::s_componentCountLookup[] = {
        [(uint32_t)Ray::Texture::Format::R8] = 1,
        [(uint32_t)Ray::Texture::Format::R8I] = 1,
        [(uint32_t)Ray::Texture::Format::R32I] = 4,
        [(uint32_t)Ray::Texture::Format::R32F] = 4,

        [(uint32_t)Ray::Texture::Format::RG8] = 2,
        [(uint32_t)Ray::Texture::Format::RG8I] = 2,
        [(uint32_t)Ray::Texture::Format::RG32I] = 8,
        [(uint32_t)Ray::Texture::Format::RG32F] = 8,

        [(uint32_t)Ray::Texture::Format::RGB8] = 3,
        [(uint32_t)Ray::Texture::Format::RGB8I] = 3,
        [(uint32_t)Ray::Texture::Format::RGB32I] = 12,
        [(uint32_t)Ray::Texture::Format::RGB32F] = 12,

        [(uint32_t)Ray::Texture::Format::RGBA8] = 4,
        [(uint32_t)Ray::Texture::Format::RGBA8I] = 4,
        [(uint32_t)Ray::Texture::Format::RGBA16] = 8,
        [(uint32_t)Ray::Texture::Format::RGBA16F] = 8,
        [(uint32_t)Ray::Texture::Format::RGBA32I] = 16,
        [(uint32_t)Ray::Texture::Format::RGBA32F] = 16,

        [(uint32_t)Ray::Texture::Format::DEPTH] = 4,
        [(uint32_t)Ray::Texture::Format::DEPTH_STENCIL] = 4,
    };
    uint32_t TextureSpecificationToGLTypes::GetTextureFilter(const Ray::Texture::Filter &filter)
    {
        switch (filter)
        {
        case Ray::Texture::Filter::NEAREST:
            return GL_NEAREST;
        case Ray::Texture::Filter::BILINEAR:
            return GL_LINEAR;
        case Ray::Texture::Filter::TRILINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;
        }
        return GL_NEAREST;
    }
    uint32_t TextureSpecificationToGLTypes::GetTextureWrapping(const Ray::Texture::Wrap &wrapping)
    {
        switch (wrapping)
        {
        case Ray::Texture::Wrap::REPEAT:
            return GL_REPEAT;
        case Ray::Texture::Wrap::CLAMP:
            return GL_CLAMP_TO_EDGE;
        case Ray::Texture::Wrap::MIRROR:
            return GL_MIRRORED_REPEAT;
        case Ray::Texture::Wrap::MIRROR_ONCE:
            return GL_MIRROR_CLAMP_TO_EDGE;
        }
        return GL_REPEAT;
    }
    uint32_t TextureSpecificationToGLTypes::GetTextureDataFormat(const Ray::Texture::Format &format)
    {
        switch (format)
        {
        case Ray::Texture::Format::RGBA8... Ray::Texture::Format::RGBA32F:
            return GL_RGBA;
        case Ray::Texture::Format::RGB8... Ray::Texture::Format::RGB32F:
            return GL_RGB;
        case Ray::Texture::Format::DEPTH_STENCIL:
            return GL_DEPTH_STENCIL;
        case Ray::Texture::Format::R8... Ray::Texture::Format::R32F:
            return GL_RED;
        case Ray::Texture::Format::DEPTH:
            return GL_DEPTH;
        case Ray::Texture::Format::RG8... Ray::Texture::Format::RG32F:
            return GL_RG;
        };
        return GL_NONE;
    }

    /////////////////////////////////
    /////////TEXTURE 2D IMPL/////////
    /////////////////////////////////
    Texture2D::Texture2D(const Texture2DSpecification &specs, uint8_t Samples)
        : m_rendererID(0), m_specs(specs),
          m_samples(Samples)
    {
        Invalidate();
    }
    Texture2D::Texture2D(const std::string &path, uint8_t mipmaps)
        : m_rendererID(0), m_specs(),
          m_samples(1)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (!data)
            throw std::runtime_error("Failed to load Image");

        m_specs.Width = width;
        m_specs.Height = height;
        m_specs.Mipmaps = mipmaps;

        uint32_t internalFormat = 0, dataFormat = 0;
        switch (channels)
        {
        case 3:
            m_specs.Format = Texture::Format::COLOR3;
            dataFormat = GL_RGB;
            internalFormat = GL_RGB8;
            break;
        case 4:
            m_specs.Format = Texture::Format::COLOR4;
            dataFormat = GL_RGBA;
            internalFormat = GL_RGBA8;
            break;
        case 2:
            m_specs.Format = Texture::Format::COLOR2;
            dataFormat = GL_RG;
            internalFormat = GL_RG8;
            break;
        case 1:
            m_specs.Format = Texture::Format::RED_INTEGER;
            dataFormat = GL_RED;
            internalFormat = GL_R8;
            break;
        }

        if (!(internalFormat & dataFormat))
            throw std::runtime_error("Format not Supported");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);

        glTextureStorage2D(m_rendererID, m_specs.Mipmaps + 1, internalFormat, m_specs.Width, m_specs.Height);
        glTextureSubImage2D(m_rendererID, 0,
                            0, 0, m_specs.Width, m_specs.Height,
                            dataFormat,
                            GL_UNSIGNED_BYTE, static_cast<void *>(data));

        if (m_specs.Mipmaps > 0)
        {
            glGenerateTextureMipmap(m_rendererID);
            glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            m_specs.MinFilter = Texture::Filter::TRILINEAR;
        }
        else
        {
            glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            m_specs.MinFilter = Texture::Filter::NEAREST;
        }

        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        m_specs.MagFilter = Texture::Filter::NEAREST;

        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        m_specs.WrappingU = Texture::Wrap::REPEAT;
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
        m_specs.WrappingV = Texture::Wrap::REPEAT;

        stbi_image_free(data);
    }

    Texture2D::~Texture2D()
    {
        Release();
    }

    void Texture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_rendererID);
    }

    void Texture2D::Clear(int32_t value, uint8_t mipmap_layer)
    {
        if (mipmap_layer > m_specs.Mipmaps)
            throw std::runtime_error("Mipmap layer doesn't exist");

        glClearTexImage(m_rendererID, mipmap_layer,
                        TextureSpecificationToGLTypes::GetTextureFormat(m_specs.Format),
                        GL_INT, &value);
    }

    void Texture2D::SetData(void *data, uint32_t size, uint8_t mipmap_layer)
    {
        if (mipmap_layer > m_specs.Mipmaps)
            throw std::runtime_error("Mipmap layer doesn't exist");

        auto components = TextureSpecificationToGLTypes::GetTextureComponentCount(m_specs.Format);
        if (size != m_specs.Width * m_specs.Height * components)
            throw std::runtime_error("Data must be entire Texture");

        auto dataFormat = TextureSpecificationToGLTypes::GetTextureDataFormat(m_specs.Format);
        glTextureSubImage2D(m_rendererID, mipmap_layer, 0, 0, m_specs.Width, m_specs.Height, dataFormat, GL_UNSIGNED_BYTE, data);

        ///TODO: Check at a later stage
        //Would you need to always generate mipmaps, why not only clear data and leave mipmaps as be
        if (mipmap_layer == 0 && m_specs.Mipmaps > 0)
            glGenerateTextureMipmap(m_rendererID);
    }

    void Texture2D::Invalidate()
    {
        if (m_rendererID)
            Release();

        auto internalFormat = TextureSpecificationToGLTypes::GetTextureFormat(m_specs.Format);
        if (m_samples > 1)
        {
            glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &m_rendererID);
            glTextureStorage2DMultisample(m_rendererID, m_samples, internalFormat, m_specs.Width, m_specs.Height, GL_FALSE);
        }
        else
        {
            glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
            glTextureStorage2D(m_rendererID, m_specs.Mipmaps + 1, internalFormat, m_specs.Width, m_specs.Height);

            if (m_specs.Mipmaps > 0)
                glGenerateTextureMipmap(m_rendererID);

            glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, TextureSpecificationToGLTypes::GetTextureFilter(m_specs.MinFilter));
            glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, TextureSpecificationToGLTypes::GetTextureFilter(m_specs.MagFilter));

            glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, TextureSpecificationToGLTypes::GetTextureWrapping(m_specs.WrappingU));
            glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, TextureSpecificationToGLTypes::GetTextureWrapping(m_specs.WrappingV));
        }
    }

    void Texture2D::Release()
    {
        glDeleteTextures(1, &m_rendererID);
        m_rendererID = 0;
    }

    void Texture2D::Resize(uint32_t width, uint32_t height)
    {
        m_specs.Width = width;
        m_specs.Height = height;
        Invalidate();
    }
}