#pragma once

#include "Core.hpp"

namespace Ray
{
    class RayObject
    {
    public:
        virtual std::string ToString() { return "Ray Object"; }
        virtual bool Equals(const RayObject &) { return false; }

    public:
        template <class T, std::enable_if_t<std::is_base_of_v<RayObject, T>, bool> = true>
        inline constexpr T Cast() { return *(dynamic_cast<T *>(this)); }
    };
}