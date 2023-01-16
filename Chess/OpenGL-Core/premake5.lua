project "OpenGL-Core"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin/Intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",

		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",

		"vendor/glm/**.hpp",
		"vendor/glm/**.inl",
		
		"vendor/spdlog/include/spdlog/spdlog.h",
		"vendor/spdlog/include/spdlog/fmt/ostr.h",
		"vendor/spdlog/include/spdlog/sinks/stdout_color_sinks.h"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"src",
		"vendor/",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"GLFW",
		"GLEW",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLEW_STATIC"
		}

	filter "configurations:Debug"
		disablewarnings { "4244" }
	    defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		disablewarnings { "4244" }
	    defines "RELEASE"
		runtime "Release"
		optimize "on"