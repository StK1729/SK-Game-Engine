workspace "SK-Game-Engine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir =  "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- include directories relative to root folder 
	IncludeDir = {}
	IncludeDir["GLFW"] = "SK-Game-Engine/vendor/GLFW/include"
	IncludeDir["Glad"] = "SK-Game-Engine/vendor/Glad/include"
	IncludeDir["ImGui"] = "SK-Game-Engine/vendor/imgui"

	group "Dependencies"
		include "SK-Game-Engine/vendor/GLFW"
		include "SK-Game-Engine/vendor/Glad"
		include "SK-Game-Engine/vendor/imgui"

	group ""

	project "SK-Game-Engine"
	location "SK-Game-Engine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "SK-Game-Engine/src/pch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"ImGui"
	}

	filter "system:windows"
	cppdialect "C++17"
	systemversion "latest"

	defines
	{
		"SKGE_PLATFORM_WINDOWS",
		"SKGE_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
	}

	filter "configurations:Debug"
		defines "SKGE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SKGE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SKGE_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"SK-Game-Engine/vendor/spdlog/include",
		"SK-Game-Engine/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"SK-Game-Engine"
	}

	filter "system:windows"
	cppdialect "C++17"
	systemversion "latest"

	defines
	{
		"SKGE_PLATFORM_WINDOWS",
	}

	filter "configurations:Debug"
		defines "SKGE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SKGE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SKGE_DIST"
		runtime "Release"
		optimize "On"