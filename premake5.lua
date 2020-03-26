workspace "SK-Gaming-Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir =  "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- include directories relative to root folder 
	IncludeDir = {}
	IncludeDir["GLFW"] = "SK-Gaming-Engine/vendor/GLFW/include"
	include "SK-Gaming-Engine/vendor/GLFW"

	project "SK-Gaming-Engine"
	location "SK-Gaming-Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "SK-Gaming-Engine/src/pch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"

	defines
	{
		"SKGE_PLATFORM_WINDOWS",
		"SKGE_BUILD_DLL"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
	}

	filter "configurations:Debug"
		defines "SKGE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SKGE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SKGE_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"SK-Gaming-Engine/vendor/spdlog/include",
		"SK-Gaming-Engine/src"
	}

	links
	{
		"SK-Gaming-Engine"
	}

	filter "system:windows"
	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"

	defines
	{
		"SKGE_PLATFORM_WINDOWS",
	}

	filter "configurations:Debug"
		defines "SKGE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SKGE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SKGE_DIST"
		optimize "On"