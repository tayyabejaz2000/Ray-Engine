#pragma once

#include "Core/Core.hpp"

namespace Ray
{
    class Texture
    {
    public:
        enum Filter : uint8_t
        {
            NEAREST,
            BILINEAR,
            TRILINEAR,
        };
        enum Wrap : uint8_t
        {
            REPEAT,
            CLAMP,
            MIRROR,
            MIRROR_ONCE,
        };
        ///TODO: Support more format
        enum Format : uint8_t
        {
            //Color
            R8,
            R8I,
            R32I,
            R32F,

            RG8,
            RG8I,
            RG32I,
            RG32F,

            RGB8,
            RGB8I,
            RGB32I,
            RGB32F,

            RGBA8,
            RGBA8I,
            RGBA16,
            RGBA16F,
            RGBA32I,
            RGBA32F,

            //Depth/Stencil
            DEPTH,
            DEPTH_STENCIL,

            //Defaults
            RED_INTEGER = R32I,

            COLOR2 = RG8,
            COLOR2F = RG32F,
            COLOR3 = RGB8,
            COLOR3F = RGB32F,
            COLOR4 = RGBA8,
            COLOR4F = RGBA32F,
        };

    public:
        Texture() = default;
        virtual ~Texture() = default;

        virtual void Bind(uint32_t = 0) const = 0;

        virtual void Clear(int32_t = 0, uint8_t = 0) = 0;
        virtual void SetData(void *, uint32_t, uint8_t = 0) = 0;

        virtual intptr_t GetRendererID() const = 0;
    };

    struct Texture2DSpecification
    {
        uint32_t Width, Height;

        Texture::Format Format;

        Texture::Wrap WrappingU = Texture::Wrap::REPEAT;
        Texture::Wrap WrappingV = Texture::Wrap::REPEAT;

        Texture::Filter MinFilter = Texture::Filter::NEAREST;
        Texture::Filter MagFilter = Texture::Filter::NEAREST;

        uint8_t Mipmaps = 0;
    };

    class Texture2D : public Texture
    {
    public:
        virtual const Texture2DSpecification &GetSpecifications() const = 0;

    public:
        static Ref<Texture2D> Create(const Texture2DSpecification &);
        static Ref<Texture2D> Create(const std::string &, uint32_t = 0);
    };
}