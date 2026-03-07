#pragma once

struct Vector3;
struct Color;

class Game
{
public:
    static void SetCamera(Vector3 position, Vector3 direction);
    static void DrawCube(Vector3 position, Vector3 euler, Vector3 size, Color color);
};