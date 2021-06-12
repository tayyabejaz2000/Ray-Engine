project "RayUI"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.hpp",
		"src/**.cpp"
	}

	includedirs {
		"%{wks.location}/Ray/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
	}

	links {
		"Ray",
        "GL",
		"pthread",
        "GLFW",
        "glad",
        "X11",
		"dl",
    }

	filter "configurations:Debug"
		defines "RAY_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RAY_RELEASE"
		runtime "Release"
		optimize "on"