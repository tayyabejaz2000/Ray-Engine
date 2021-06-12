#pragma once

#include "Core.hpp"

namespace Ray
{
    enum class RAYAPI Resolution : uint64_t
    {
        RESOLUTION_SD = (480ul << sizeof(uint32_t) * 8) | 640ul,
        RESOLUTION_HD = (720ul << sizeof(uint32_t) * 8) | 1280ul,
        RESOLUTION_HD_PLUS = (900ul << sizeof(uint32_t) * 8) | 1600ul,
        RESOLUTION_FHD = (1080ul << sizeof(uint32_t) * 8) | 1920ul,
        RESOLUTION_QHD = (1440ul << sizeof(uint32_t) * 8) | 2560ul,
        RESOLUTION_QHD_PLUS = (1800ul << sizeof(uint32_t) * 8) | 3200ul,
        RESOLUTION_4K = (2160ul << sizeof(uint32_t) * 8) | 3840ul,
    };
    struct RAYAPI WindowSpecifications
    {
        std::string title = "Ray Engine"s;
        union
        {
            struct
            {
                Resolution resolution;
            };
            struct
            {
                uint32_t width, height;
            };
        };
        bool vsync = true;
        uint16_t samples = 1;
    };
}