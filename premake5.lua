workspace "Raylib Game"
    configurations {"Debug" }

    location "build"

project "Game"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "build/obj/%{cfg.buildcfg}"

    files {
        "**.h",
        "**.c",
        "**.cpp",
        "**.hpp",
    }

    includedirs {
        "libs/raylib/include"
    }

    links{
        "raylib",
        "m",         -- math library (for linux)
        "pthread",   -- threads (for linux)
        "dl",        -- dynamic loading (for linux)
        "X11",       -- X11 (for linux)
        "xcb",       -- XCB (for linux, X11 alternative)
        "Xau",       -- X11 authorization (for linux)
        "Xdmcp"      -- X11 display manager control (for linux)
    }

    libdirs {
        "libs/raylib/lib"
    }

    filter "system:linux"
        links {
            "GL",
            "rt"
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"