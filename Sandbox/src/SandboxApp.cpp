#include "Core/EntryPoint.hpp"
#include "Core/Application.hpp"

#include "SandboxLayer.hpp"

namespace Ray
{
    class SandboxApp : public Application
    {
    public:
        SandboxApp() : Application("Ray Engine")
        {
            Application::GetApplication().PushLayer(CreateRef<SandboxLayer>());
        }
        ~SandboxApp()
        {
        }
    };

    Object<Application> CreateApplication()
    {
        return CreateObject<SandboxApp>();
    }
}