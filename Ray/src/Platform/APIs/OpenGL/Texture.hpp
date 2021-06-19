#pragma once

#include <glad/glad.h>

#include "Core/Core.hpp"
#include "Renderer/Texture.hpp"

namespace Ray::OpenGL
{
    class Texture2D : public Ray::Texture2D
    {
    public:
        Texture2D(uint32_t, uint32_t);
        Texture2D(const std::string &);
        virtual ~Texture2D();

        virtual uint32_t GetWidth() const override { return m_width; }
        virtual uint32_t GetHeight() const override { return m_height; }

        virtual void Bind(uint32_t = 0) const override;

        virtual void SetData(void *, uint32_t) override;

    private:
        uid_t m_rendererID;
        uint32_t m_width, m_height;
        GLenum m_internalFormat, m_dataFormat;
    };
}