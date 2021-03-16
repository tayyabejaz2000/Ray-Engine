#pragma once
#include "Application.h"
#include <iostream>
#ifdef RAY_WINDOWS_PLATFORM

extern Ray::Application* Ray::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Ray::CreateApplication();
	app->Run();
	delete app;
}

#endif