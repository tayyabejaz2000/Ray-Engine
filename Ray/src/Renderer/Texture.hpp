#pragma once

#include "Core/Core.hpp"

namespace Ray
{
    enum class TextureWrap : uint8_t
    {
        REPEAT,
        MIRRORED_REPEAT,

        CLAMP_TO_EDGE,
        MIRROR_CLAMP_TO_EDGE,

        CLAMP_TO_BORDER,
    };

    ///TODO: Support more format
    enum class TextureFormat : uint8_t
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

    struct Texture2DSpecification
    {
        uint32_t Width, Height;
        TextureFormat Format;
        TextureWrap WrappingR = TextureWrap::REPEAT;
        TextureWrap WrappingS = TextureWrap::REPEAT;
        TextureWrap WrappingT = TextureWrap::REPEAT;
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
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const Texture2DSpecification &);
        static Ref<Texture2D> Create(const std::string &);
    };
}