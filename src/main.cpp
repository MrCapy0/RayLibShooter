#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "IActor.h"
#include "Game.h"
#include "Level.h"

Camera3D camera;

G::Level level;
Model cubeModel;
bool focused = 0;
float focusedTimer = 0;

std::vector<G::IActor *> G::Game::actors;

void UpdateIsFocused(float delta)
{
    focused = true;
    if (!IsWindowFocused())
    {
        focused = false;
    }

    if (focused)
    {
        Vector2 mousePosition = GetMousePosition();
        if (mousePosition.x < 1 || mousePosition.y < 1)
        {
            focused = false;
        }

        if (mousePosition.x > G::Game::WINDOW_WIDTH - 1 || mousePosition.y > G::Game::WINDOW_HEIGHT - 1)
        {
            focused = false;
        }
    }

    if (focused)
    {
        focusedTimer += delta;
        if (focusedTimer < 0.1)
        {
            focused = false;
        }
    }
    else
    {
        focusedTimer = 0;
    }
}

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
    DrawModelWires(cubeModel, {0}, 1.004f, (Color){color.r * 0.5f, color.g * 0.5f, color.b * 0.5f, color.a});
}

void G::Game::Update(const float delta)
{
    for (IActor *actor : actors)
    {
        actor->OnUpdate(delta);
    }

    for (IActor *actor : actors)
    {
        actor->OnPostRender();
    }
}

bool G::Game::IsFocused()
{
    return focused;
}

int main()
{
    InitWindow(G::Game::WINDOW_WIDTH, G::Game::WINDOW_HEIGHT, "Window");
    SetTargetFPS(60);
    DisableCursor();

    camera = {0};
    camera.position = (Vector3){20.0f, 8, 20.0f};
    camera.target = (Vector3){0.0f, 0, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    cubeModel = LoadModel("assets/Cube.glb");

    level = G::Level();
    level.Setup();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        BeginMode3D(camera);
        ClearBackground(RAYWHITE);

        float delta = GetFrameTime();
        UpdateIsFocused(delta);

        level.Update(delta);
        G::Game::Update(delta);

        DrawGrid(50, 1);
        EndMode3D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}