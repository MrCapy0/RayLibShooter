#include "Transform.h"
#include "raymath.h"

G::Transform::Transform()
{
    position = {};
    rotation = QuaternionIdentity();
    scale = {1};
}