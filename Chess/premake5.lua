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

include "OpenGL-Core"
include "Chess-Game"