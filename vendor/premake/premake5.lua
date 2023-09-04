project "Premake"
	kind "Utility"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{wks.location}/**premake5.lua"
	}
	
	postbuildmessage "Regenerating project files with Premake5!"
	filter "system:windows"
		postbuildcommands {
			"tools\\Windows\\premake5.exe %{_ACTION} --file=\"%{wks.location}\\premake5.lua\""
		}
	filter "system:linux"
		postbuildcommands {
			"./tools/Linux/premake5 %{_ACTION} --file=\"%{wks.location}/premake5.lua\""
		}