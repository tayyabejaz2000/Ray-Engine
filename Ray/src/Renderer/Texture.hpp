#pragma once

#include "Core/Core.hpp"

namespace Ray
{
    struct Texture2DSpecification
    {
        uint32_t Width, Height;

        Texture::Format Format;

        Texture::Wrap WrappingR = Texture::Wrap::REPEAT;
        Texture::Wrap WrappingS = Texture::Wrap::REPEAT;
        Texture::Wrap WrappingT = Texture::Wrap::REPEAT;

        Texture::Filter MinFilter = Texture::Filter::LINEAR;
        Texture::Filter MagFilter = Texture::Filter::LINEAR;
    };

    class Texture
    {
    public:
        Texture() = default;
        virtual ~Texture() = default;

        virtual const Texture2DSpecification &GetSpecifications() const = 0;

        virtual void Bind(uint32_t = 0) const = 0;

        virtual void Clear(uint32_t = 0) = 0;
        virtual void SetData(void *, uint32_t) = 0;

    public:
        enum Filter : uint8_t
        {
            NEAREST,
            LINEAR,

            //Mipmaps (Only Minifying Filter)
            NEAREST_MIPMAP_NEAREST,
            LINEAR_MIPMAP_NEAREST,
            NEAREST_MIPMAP_LINEAR,
            LINEAR_MIPMAP_LINEAR,
        };
        enum Wrap : uint8_t
        {
            REPEAT,
            MIRRORED_REPEAT,

            CLAMP_TO_EDGE,
            MIRROR_CLAMP_TO_EDGE,

            CLAMP_TO_BORDER,
        };
        ///TODO: Support more format
        enum Format : uint8_t
        {
            //Color
            R8,
            R8I,
            R32F,

            RG8,
            RG8I,
            RG32F,

            RGB8,
            RGB32F,

            RGBA8,
            RGBA16,
            RGBA16F,
            RGB32I,
            RGBA32F,

            //Depth/Stencil
            STENCIL8,
            DEPTH24STENCIL8,
            DEPTH32,

            //Defaults
            DEPTH = DEPTH24STENCIL8,

            RED_INTEGER = R8,

            COLOR3 = RGB8,
            COLOR3F = RGB32F,
            COLOR4 = RGBA8,
            COLOR4F = RGBA32F,
        };
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const Texture2DSpecification &);
        static Ref<Texture2D> Create(const std::string &);
    };
}