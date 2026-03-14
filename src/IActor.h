#pragma once

#include "Transform.h"

namespace G
{
    class IActor
    {
    private:
        Transform transform;

    public:
        virtual void OnSetup() = 0;
        virtual void OnUpdate(float delta) = 0;
        virtual void OnPostRender() = 0;
        virtual void SetTransform(const Transform transform);
        G::Transform GetTransform() const;
        virtual ~IActor() = default;
    };
}
