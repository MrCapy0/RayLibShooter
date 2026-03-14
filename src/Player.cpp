#include "Player.h"
#include "Game.h"

#include <iostream>

const float LOOK_SPEED = 0.001f;
const float MOVE_SPEED = 10;

void G::Player::OnSetup()
{
    Transform t = G::Transform();
    cameraSmoothRotation = QuaternionIdentity();
    SetTransform(t);

    Vector2 screenSize = {GetScreenWidth(), GetScreenHeight()};
    Vector2 screenCenter = screenSize / (Vector2){2, 2};
}

void G::Player::OnUpdate(float delta)
{
    Vector2 mouseDelta = GetMouseDelta();
    if (Game::IsFocused() && Vector2Length(mouseDelta) > 0.01f)
    {
        Vector2 screenSize = {GetScreenWidth(), GetScreenHeight()};
        Vector2 screenCenter = screenSize / (Vector2){2, 2};
        SetMousePosition(screenCenter.x, screenCenter.y);
    }
    else
    {
        mouseDelta = {0};
    }

    Transform transform = GetTransform();
    Vector3 position = transform.position;

    Vector3 moveForward = GetTransform().GetForward();
    Vector3 moveRight = GetTransform().GetRight();

    moveForward = Vector3ClampValue(moveForward, 0, IsKeyDown(KEY_W) - IsKeyDown(KEY_S));
    moveRight = Vector3ClampValue(moveRight, 0, IsKeyDown(KEY_A) - IsKeyDown(KEY_D));

    Vector3 move = Vector3Add(moveForward, moveRight);
    move = Vector3Normalize(move);
    move.x *= delta * MOVE_SPEED;
    move.z *= delta * MOVE_SPEED;

    Vector2 mouseDir = mouseDelta;
    cameraEulerX += mouseDir.y * LOOK_SPEED;
    cameraEulerY -= mouseDir.x * LOOK_SPEED;

    cameraEulerX = Clamp(cameraEulerX, DEG2RAD * -20, DEG2RAD * 20);
    if (cameraEulerY > 360 * DEG2RAD)
    {
        cameraEulerY -= 360 * DEG2RAD;
    }
    if (cameraEulerY < 0)
    {
        cameraEulerY += 360 * DEG2RAD;
    }

    position = Vector3Add(position, move);
    transform.position = position;
    transform.rotation = QuaternionFromEuler(0, cameraEulerY, 0);
    SetTransform(transform);

    Game::DrawCube({2, 0.5f, 0}, {0, 45, 0}, {2, 1, 1}, RED);

    Quaternion rawRot = QuaternionFromEuler(cameraEulerX, cameraEulerY, 0);
    Vector3 rawForward = Vector3RotateByQuaternion({0, 0, 1}, rawRot);
    Vector3 smoothForward = Vector3RotateByQuaternion({0, 0, 1}, cameraSmoothRotation);
    float angle = Vector3Angle(rawForward, smoothForward);
    float smooth = std::max(angle * delta * 10, delta * 10);
    cameraSmoothRotation = QuaternionSlerp(cameraSmoothRotation, rawRot, Clamp(smooth, 0, 1));
}

void G::Player::OnPostRender()
{
    G::Game::SetCamera(GetCameraPosition(), GetCameraForward());
}

Vector3 G::Player::GetCameraForward() const
{
    Quaternion rotation = QuaternionFromEuler(cameraEulerX, cameraEulerY, 0);
    return Vector3RotateByQuaternion({0, 0, 1}, cameraSmoothRotation);
}

Vector3 G::Player::GetCameraPosition() const
{
    Vector3 position = GetTransform().position;
    position.y += 2;
    return position;
}

G::Player::~Player()
{
}