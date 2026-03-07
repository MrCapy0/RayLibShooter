#pragma once
#include "raylib.h"

namespace G
{
    struct Transform
    {
    public:
        Vector3 position;
        Quaternion rotation;
        Vector3 scale;
        Transform();
    };
}