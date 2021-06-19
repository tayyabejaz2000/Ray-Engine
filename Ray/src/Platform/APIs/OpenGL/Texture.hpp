#pragma once

#include <glad/glad.h>

#include "Core/Core.hpp"
#include "Renderer/Texture.hpp"

namespace Ray::OpenGL
{
    class TextureSpecificationToGLTypes
    {
    public:
        static uint32_t GetTextureWrapping(const TextureWrap &);
        static uint32_t GetTextureDataFormat(const TextureFormat &);
        static uint32_t GetTextureFormat(const TextureFormat &format) { return s_formatLookup[(uint32_t)format]; }

    private:
        static uint8_t s_formatLookup[];
    };

    class Texture2D : public Ray::Texture2D
    {
    public:
        Texture2D(const Texture2DSpecification &);
        Texture2D(const std::string &);
        virtual ~Texture2D();

        virtual const Texture2DSpecification &GetSpecifications() const override { return m_specs; }

        virtual void Bind(uint32_t = 0) const override;

        virtual void Clear(uint32_t = 0) override;
        virtual void SetData(void *, uint32_t) override;

    private:
        uid_t m_rendererID;
        Texture2DSpecification m_specs;
    };
}