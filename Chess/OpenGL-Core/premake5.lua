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
		"vendor/spdlog/inlcude/spdlog/spdlog.h",
		"vendor/spdlog/inlcude/spdlog/fmt/ostr.h",
		"vendor/spdlog/inlcude/spdlog/sinks/stdout_color_sinks.h"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"vendor/GLFW/lib/glfw3_mt",
		"vendor/GLEW/lib/glew32s",
		"opengl32"
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