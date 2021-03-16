#pragma once
#include "Core.hpp"

namespace Ray
{
	class RAYAPI Application
	{
	public:
		Application();
		virtual ~Application();
		int Run();
	};

	Application* CreateApplication();
}

