#pragma once

#include "Transform.h"

namespace G
{
    class IActor
    {
    private:
        Transform transform;

    public:
        virtual void Setup() = 0;
        virtual void Update(float delta) = 0;
        void SetTransform(const Transform transform);
        G::Transform GetTransform() const;
        virtual ~IActor() = default;
    };
}
