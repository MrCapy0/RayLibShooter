#include "raylib.h"

int main()
{
    InitWindow(800, 450, "raylib + premake");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello Raylib!", 300, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
}