project "Chess-Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin/Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"res/shaders/*",
		"res/textures/*"
	}

	includedirs
	{
		"../OpenGL-Core/src",
		"../OpenGL-Core/vendor",
		"../OpenGL-Core/vendor/spdlog/include",
		"../OpenGL-Core/%{IncludeDir.glm}",
		"../OpenGL-Core/%{IncludeDir.GLEW}",
		"../OpenGL-Core/%{IncludeDir.GLFW}"
	}

	links
	{
		"OpenGL-Core"
	}

	filter "system:windows"
		systemversion "latest"

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
