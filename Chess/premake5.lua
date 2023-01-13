-- Chess
workspace "Chess"
	architecture "x64"
	startproject "Chess-Game"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to OpenGL-Core
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["GLEW"] = "vendor/GLEW/include"
IncludeDir["glm"] =  "vendor/glm"
IncludeDir["stb_image"] = "vendor/stb_image"
IncludeDir["spdlog"] = "vendor/spdlog/include"

group "Dependencies"
	include "OpenGL-Core/vendor/GLFW"
	include "OpenGL-Core/vendor/GLEW"
group ""

include "OpenGL-Core"
include "Chess-Game"

newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        print("Removing binaries")
        os.rmdir("./bin")
		os.rmdir("./OpenGL/vendor/bin")
        print("Removing intermediate binaries")
        os.rmdir("./bin/Intermediate")
		os.rmdir("./OpenGL/vendor/bin/Intermediate")
        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}