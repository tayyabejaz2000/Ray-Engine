#include "stb_image.h"
#include "Platform/APIs/OpenGL/Texture.hpp"

namespace Ray::OpenGL
{
    Texture2D::Texture2D(uint32_t width, uint32_t height) : m_width(width), m_height(height)
    {
        m_internalFormat = GL_RGBA8;
        m_dataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
        glTextureStorage2D(m_rendererID, 1, m_internalFormat, m_width, m_height);

        glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    Texture2D::Texture2D(const std::string &path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc *data = nullptr;
        data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (!data)
            throw std::runtime_error("Failed to load Image");
        m_width = width;
        m_height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        m_internalFormat = internalFormat;
        m_dataFormat = dataFormat;

        if (!(internalFormat & dataFormat))
            throw std::runtime_error("Format not Supported");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
        glTextureStorage2D(m_rendererID, 1, m_internalFormat, m_width, m_height);

        glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);

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
        auto bpp = m_dataFormat == GL_RGBA ? 4u : 3u;
        if (size != m_width * m_height * bpp)
            throw std::runtime_error("Data must be entire Texture");
        glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
    }
}