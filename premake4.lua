-- A solution contains projects, and defines the available configurations
solution "Exil"
	location("build/" .. _ACTION)
	targetdir "bin"
	configurations { "Debug", "Release" }

	-- A project defines one build target
	project "ExilDemo"
		kind "ConsoleApp"
		language "C++"
		files {
			"include/*.h",
			"source/*.cpp",
			"main.cpp",
			"ReadMe.txt"
		}
		includedirs { "include" }
		objdir "intermediate"
	
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }
		objdir "intermediate/Debug"
		targetname "ExilDemo_d"

	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" }
		objdir "intermediate/Release"
