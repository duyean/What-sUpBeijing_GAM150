// CameraVFX.cpp
#include "CameraVFX.hpp"

void CameraVFX::awake() {}
void CameraVFX::init()
{
    AEGfxGetCamPosition(&originalX, &originalY);
}

void CameraVFX::TriggerShake()
{
    timer = duration;
    shaking = true;
    AEGfxGetCamPosition(&originalX, &originalY);
}

void CameraVFX::update()
{
    if (!shaking) return;

    timer -= (f32)AEFrameRateControllerGetFrameTime();

    if (timer <= 0.f)
    {
        timer = 0.f;
        shaking = false;
        AEGfxSetCamPosition(originalX, originalY);
        return;
    }

    // intensity fades out over duration
    float t = timer / duration;
    float currentIntensity = intensity * t;

    // random offset each frame
    float offsetX = (AERandFloat() * 2.0f - 1.0f) * currentIntensity;
    float offsetY = (AERandFloat() * 2.0f - 1.0f) * currentIntensity;

    AEGfxSetCamPosition(originalX + offsetX, originalY + offsetY);
}

void CameraVFX::fixedUpdate() {}
void CameraVFX::destroy() {}