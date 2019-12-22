workspace "path-tracer"
    architecture "x64"
    language "C++"
	cppdialect "C++17"

    configurations { "Debug", "Release" }

    targetdir "build/%{cfg.buildcfg}"
	objdir "build/intermediates/%{cfg.buildcfg}/%{prj.name}"
	includedirs { ".", "dependencies/glm" }
	libdirs { }

	filter "configurations:Debug"
		symbols "On"
		optimize "Off"

	filter "configurations:Release"
		symbols "On"
		optimize "Speed"

	filter {}

-- Applications
group "Applications"
    project "PathTracerCLI"
        kind "ConsoleApp"
		location "PathTracerCLI"
		files { "%{prj.name}/**.h", "%{prj.name}/**.hpp", "%{prj.name}/**.cpp" }
		links { "PathTracer" }

-- Libraries
group "Libraries"
    project "PathTracer"
        kind "StaticLib"
		location "PathTracer"
		files { "%{prj.name}/**.h", "%{prj.name}/**.hpp", "%{prj.name}/**.cpp" }
		defines { }
		links { }
