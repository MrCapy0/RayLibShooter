workspace "RaylibProject"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "Game"

project "Game"
    location "build"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("build/bin/%{cfg.buildcfg}")
    objdir ("build/obj/%{cfg.buildcfg}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "libs/raylib/include"
    }

    libdirs
    {
        "libs/raylib/lib"
    }

    filter "system:linux"
        links
        {
            "raylib",
            "m",
            "pthread",
            "dl",
            "rt",
            "X11"
        }

        linkoptions
        {
            "-Wl,-rpath,$$ORIGIN"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

    filter {}