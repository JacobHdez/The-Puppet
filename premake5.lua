-- OpenGL - Puppet
workspace "The_Puppet"
	architecture "x86"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Ze_Puppet"
	location "Ze_Puppet"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src/OpenGL-Core",
		"%{prj.name}/src/vendor",
		"Dependencies/GLFW/include",
		"Dependencies/GLEW/include"
	}

	libdirs
	{
		"Dependencies/GLEW/lib/Release/Win32",
		"Dependencies/GLFW/lib-vc2019"
	}

	links
	{
		"glew32s.lib",
		"glfw3.lib",
		"opengl32.lib",
		"User32.lib",
		"Gdi32.lib",
		"Shell32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GLEW_STATIC",
			"WIN32"
		}

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"