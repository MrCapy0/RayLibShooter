#include "Level.h"
#include "Game.h"
#include "raylib.h"
#include "raymath.h"

#include <iostream>

struct Player
{
    Vector3 position;
    Vector3 euler;
};

Player player;

const float MOVE_SPEED = 10;

Vector3 GetPlayerCameraForward()
{
    float x = player.euler.x;
    float y = player.euler.y;
    float z = player.euler.z;
    return Vector3RotateByQuaternion({0, 0, 1}, QuaternionFromEuler(x, y, z));
}

Level::Level()
{
    player = {};
    player.position = {0, 2, 0};
    player.euler = {0, 0, 0};
}

void Level::Setup()
{
}

void Level::Update(float delta)
{
    Game::SetCamera(player.position, GetPlayerCameraForward());

    Vector3 move = {};
    move.x = IsKeyDown(KEY_A) - IsKeyDown(KEY_D);
    move.z = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
    move = Vector3Normalize(move);
    move.x *= delta * MOVE_SPEED;
    move.z *= delta * MOVE_SPEED;

    player.position = Vector3Add(player.position, move);

    Game::DrawCube({2, 0.5f, 0}, {0, 45, 0}, {2, 1, 1}, RED);

    // std::cout << cubeModel.meshCount << std::endl;
}
