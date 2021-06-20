#include "SandboxLayer.hpp"

namespace Ray
{
    SandboxLayer::SandboxLayer() : Layer()
    {
    }
    SandboxLayer::~SandboxLayer()
    {
    }

    void SandboxLayer::OnUpdate(float delta_time)
    {
    }

    void SandboxLayer::OnEvent(KeyEvent &e)
    {
        std::cout << e.scancode << '\n';
    }
}