#include "Player.h"
#include "Game.h"

#include <iostream>

const float MOVE_SPEED = 10;

void G::Player::Setup()
{
    Transform t = G::Transform();
    SetTransform(t);
}

void G::Player::Update(float delta)
{
    Transform transform = GetTransform();
    Vector3 position = transform.position;

    Vector3 move = {};
    move.x = IsKeyDown(KEY_A) - IsKeyDown(KEY_D);
    move.z = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
    move = Vector3Normalize(move);
    move.x *= delta * MOVE_SPEED;
    move.z *= delta * MOVE_SPEED;

    position = Vector3Add(position, move);
    transform.position = position;
    SetTransform(transform);

    Vector3 cameraPosition = position;
    cameraPosition.y += 2;

    G::Game::SetCamera(cameraPosition, {0, 0, 1});
    Game::DrawCube({2, 0.5f, 0}, {0, 45, 0}, {2, 1, 1}, RED);

    std::cout << delta << std::endl;
}

G::Player::~Player()
{
}