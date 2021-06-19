workspace "Ray"
	architecture "x64"
	startproject "RayUI"

	configurations {
		"Debug",
		"Release"
	}


	flags {
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Ray/vendor/GLFW/include"
IncludeDir["glad"] = "%{wks.location}/Ray/vendor/glad/include"
IncludeDir["glm"] = "%{wks.location}/Ray/vendor/glm"
IncludeDir["spdlog"] = "%{wks.location}/Ray/vendor/spdlog/include"
IncludeDir["stb_image"] = "%{wks.location}/Ray/vendor/stb_image"


group "Dependencies"
	include "vendor/premake"
	include "Ray/vendor/GLFW"
	include "Ray/vendor/glad"
group ""

include "Ray"
include "RayUI"
