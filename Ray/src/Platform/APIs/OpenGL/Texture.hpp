#pragma once

#include <glad/glad.h>

#include "Core/Core.hpp"
#include "Renderer/Texture.hpp"

namespace Ray::OpenGL
{
    class TextureSpecificationToGLTypes
    {
    public:
        static uint32_t GetTextureWrapping(const Ray::Texture::Wrap &);
        static uint32_t GetTextureFilter(const Ray::Texture::Filter &);
        static uint32_t GetTextureDataFormat(const Ray::Texture::Format &);
        static uint32_t GetTextureFormat(const Ray::Texture::Format &format) { return s_formatLookup[(uint32_t)format]; }
        static uint32_t GetTextureComponentCount(const Ray::Texture::Format &format) { return static_cast<uint32_t>(s_componentCountLookup[(uint32_t)format]); }

    private:
        //Can save memory by dynamically allocating depending on the Graphics Library being used.
        static uint32_t s_formatLookup[];
        static uint8_t s_componentCountLookup[];
    };

    class Texture2D : public Ray::Texture2D
    {
    public:
        Texture2D(const Texture2DSpecification &, uint8_t = 1);
        Texture2D(const std::string &, uint8_t = 0);
        virtual ~Texture2D();

        virtual const Texture2DSpecification &GetSpecifications() const override { return m_specs; }

        virtual void Bind(uint32_t = 0) const override;

        virtual void Clear(int32_t = 0, uint8_t = 0) override;
        virtual void SetData(void *, uint32_t, uint8_t = 0) override;

        virtual intptr_t GetRendererID() const { return static_cast<intptr_t>(m_rendererID); }

    public:
        bool IsMultisampled() { return m_samples > 1; }
        uint8_t GetSamples() { return m_samples; }

        void Invalidate();
        void Resize(uint32_t, uint32_t);
        void Release();

    private:
        uid_t m_rendererID;
        Texture2DSpecification m_specs;
        uint8_t m_samples;
    };
}