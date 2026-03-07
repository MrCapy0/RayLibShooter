#pragma once

#include "IActor.h"

namespace G
{
    class Player : public IActor
    {
    public:
        void Setup() override;
        void Update(float delta) override;
        ~Player() override;
    };
}