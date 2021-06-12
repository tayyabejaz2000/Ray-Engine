#pragma once

#include "Core/Core.hpp"

namespace Ray
{
    enum class RAYAPI MouseButton : uint8_t
    {
        BUTTON_1,
        BUTTON_2,
        BUTTON_3,
        BUTTON_4,
        BUTTON_5,
        BUTTON_6,
        BUTTON_7,
        BUTTON_8,
        BUTTON_LEFT = BUTTON_1,
        BUTTON_RIGHT = BUTTON_2,
        BUTTON_MIDDLE = BUTTON_3,
    };
}