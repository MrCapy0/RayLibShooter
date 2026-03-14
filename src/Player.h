#pragma once

#include "IActor.h"

namespace G
{
    class Player : public IActor
    {
    private:
        double cameraEulerY;
        double cameraEulerX;

        Quaternion cameraSmoothRotation;

    public:
        void OnSetup() override;
        void OnUpdate(float delta) override;
        void OnPostRender() override;
        Vector3 GetCameraPosition() const;
        Vector3 GetCameraForward() const;
        ~Player() override;
    };
}