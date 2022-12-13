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
IncludeDir["GLFW"] = "Dependencies/GLFW/include"
IncludeDir["GLEW"] = "Dependencies/GLEW/include"
IncludeDir["glm"] =  "Dependencies/glm"
IncludeDir["stb_image"] = "Dependencies/stb_image"

-- Projects
group "Dependencies"
	include "OpenGL-Core/Dependencies/GLFW"
	include "OpenGL-Core/Dependencies/GLEW"
group ""

include "OpenGL-Core"
include "Chess-Game"