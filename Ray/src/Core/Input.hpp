#include "Core/Core.hpp"

namespace Ray
{
    struct MouseVec2;
    enum class MouseButton : uint8_t;
    class Input
    {
    public:
        static MouseVec2 GetMousePosition();
        static bool IsMouseButtonPressed(MouseButton);
    };
}