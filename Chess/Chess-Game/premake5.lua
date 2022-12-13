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
		"../OpenGL-Core/Dependencies/spdlog/include",
		"../OpenGL-Core/src",
		"../OpenGL-Core/Dependencies",
		"../OpenGL-Core/%{IncludeDir.glm}",
		"../OpenGL-Core/%{IncludeDir.GLEW}"
	}

	links
	{
		"OpenGL-Core"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			
		}

	filter "configurations:Debug"
	--	defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
	--	defines "RELEASE"
		runtime "Release"
        optimize "on"
