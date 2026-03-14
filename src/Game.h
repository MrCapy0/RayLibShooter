#pragma once

#include <memory>
#include <vector>
#include "IActor.h"
#include "raylib.h"
#include "raymath.h"

namespace G
{
    class Game
    {
    private:
        static std::vector<IActor *> actors;

    public:
        const static int WINDOW_WIDTH = 1200;
        const static int WINDOW_HEIGHT = 900;
        static void SetCamera(Vector3 position, Vector3 direction);
        static void DrawCube(Vector3 position, Vector3 euler, Vector3 size, Color color);
        static bool IsFocused();

        template <typename T>
        static std::unique_ptr<T> AddActor()
        {
            std::unique_ptr<T> ptr = std::make_unique<T>();
            IActor *actor = static_cast<IActor *>(ptr.get());
            actor->OnSetup();
            actors.push_back(actor);

            return ptr;
        }

        static void Update(const float delta);
    };
}