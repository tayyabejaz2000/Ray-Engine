#pragma once
#include "Core.h"

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

