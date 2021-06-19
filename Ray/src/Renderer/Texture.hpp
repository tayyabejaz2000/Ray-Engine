#pragma once

#include "Core/Core.hpp"

namespace Ray
{
    class Texture
    {
    public:
        Texture() = default;
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t = 0) const = 0;

        virtual void SetData(void *, uint32_t) = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(uint32_t, uint32_t);
        static Ref<Texture2D> Create(const std::string &);
    };
}