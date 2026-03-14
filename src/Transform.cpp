#include "Transform.h"
#include "raymath.h"

G::Transform::Transform()
{
    position = {};
    rotation = QuaternionIdentity();
    scale = {1};
}

Vector3 G::Transform::GetForward() const
{
    return Vector3RotateByQuaternion({0, 0, 1}, rotation);
}

Vector3 G::Transform::GetRight() const
{
    return Vector3RotateByQuaternion({1, 0, 0}, rotation);
}