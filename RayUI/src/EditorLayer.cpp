#include "EditorLayer.hpp"

namespace Ray
{
    EditorLayer::EditorLayer() : Layer()
    {

    }
    EditorLayer::~EditorLayer()
    {

    }

    void EditorLayer::OnUpdate(float delta_time)
    {
    }

    void EditorLayer::OnEvent(KeyEvent& e)
    {
        std::cout << e.scancode << '\n';
    }
}