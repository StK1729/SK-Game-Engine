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
	IncludeDir["glm"] = "SK-Game-Engine/vendor/glm"

	group "Dependencies"
		include "SK-Game-Engine/vendor/GLFW"
		include "SK-Game-Engine/vendor/Glad"
		include "SK-Game-Engine/vendor/imgui"

	group ""

	project "SK-Game-Engine"
	location "SK-Game-Engine"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "SK-Game-Engine/src/pch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
		-- "%{prj.name}/vendor/glm/glm/**.hpp",
		-- "%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
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
		-- "SKGE_BUILD_DLL", not dll anymore
		"GLFW_INCLUDE_NONE",
	}

	-- postbuildcommands
	-- {
	-- 	("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
	-- }

	filter "configurations:Debug"
		defines "SKGE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SKGE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SKGE_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

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
		"%{IncludeDir.glm}",
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
		symbols "on"

	filter "configurations:Release"
		defines "SKGE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SKGE_DIST"
		runtime "Release"
		optimize "on"