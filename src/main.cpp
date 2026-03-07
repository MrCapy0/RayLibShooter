#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "IActor.h"
#include "Game.h"
#include "Level.h"

Camera3D camera;

G::Level level;
Model cubeModel;

std::vector<G::IActor *> G::Game::actors;

void G::Game::SetCamera(Vector3 position, Vector3 direction)
{
    camera.position = position;
    camera.target = Vector3Add(position, direction);
}

void G::Game::DrawCube(Vector3 position, Vector3 euler, Vector3 size, Color color)
{
    euler.x *= DEG2RAD;
    euler.y *= DEG2RAD;
    euler.z *= DEG2RAD;

    Matrix translation = MatrixTranslate(position.x, position.y, position.z);
    Matrix rotation = MatrixRotateXYZ(euler);
    Matrix scale = MatrixScale(size.x, size.y, size.z);
    Matrix transform = translation;
    cubeModel.transform = scale * transform * rotation;

    DrawModel(cubeModel, {0}, 1, color);
}

void G::Game::Update(const float delta)
{
    for (IActor *actor : actors)
    {
        actor->Update(delta);
    }
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Window");
    SetTargetFPS(60);

    camera = {0};
    camera.position = (Vector3){20.0f, 8, 20.0f}; // Camera position
    camera.target = (Vector3){0.0f, 0, 0.0f};     // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};      // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                          // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;       // Camera mode type

    cubeModel = LoadModel("assets/Cube.glb");

    level = G::Level();
    level.Setup();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        BeginMode3D(camera);
        ClearBackground(RAYWHITE);

        float delta = GetFrameTime();
        level.Update(delta);
        G::Game::Update(delta);

        DrawGrid(50, 1);
        EndMode3D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}