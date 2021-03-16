#pragma once

#ifdef RAY_WINDOWS_PLATFORM
	#ifdef RAY_BUILD_DLL
		#define RAYAPI __declspec(dllexport)
	#else
		#define RAYAPI __declspec(dllimport)
	#endif
#else
	#error Only Windows Platform Supported
#endif