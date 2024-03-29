project "Ray"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    if (kind == "SharedLib") then
		staticruntime "off"
	end

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	filter "system:windows"
        pchheader "src\\raypch.hpp"
        pchsource "src\\raypch.cpp"
	filter "system:linux"
        pchheader "src/raypch.hpp"
        pchsource "src/raypch.cpp"

    files {
        "src/**.hpp",
        "src/**.cpp",
        "vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl",
    }

    defines {
        "GLFW_INCLUDE_NONE",
    }

    if (kind == "SharedLib") then
		table.insert(defines, "RAY_BUILD_SHARED")
	end

    includedirs {
        "src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links {
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
