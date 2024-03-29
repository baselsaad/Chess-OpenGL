project "GLEW"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    
    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin/Intermediate/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/GL/*.h",
        "src/*.c"
    }

    includedirs
    {
        "include"
    }
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
