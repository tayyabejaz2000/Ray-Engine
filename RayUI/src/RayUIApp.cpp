#include "Core/EntryPoint.hpp"
#include "Core/Application.hpp"

#include "EditorLayer.hpp"

namespace Ray
{
    class RayUIApp : public Application
    {
    public:
        RayUIApp() : Application("Ray Engine")
        {
            Application::GetApplication().PushLayer(CreateRef<EditorLayer>());
        }
        ~RayUIApp()
        {
        }
    };

    Object<Application> CreateApplication()
    {
        return CreateObject<RayUIApp>();
    }
}