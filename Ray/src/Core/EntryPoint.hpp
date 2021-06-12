#pragma once
#include "Core.hpp"
#include "Application.hpp"

extern Ray::Object<Ray::Application> Ray::CreateApplication();

int main(int argc, char **argv, char **envp)
{
    auto applicationInstance = Ray::CreateApplication();

    applicationInstance->Run();

    return 0;
}