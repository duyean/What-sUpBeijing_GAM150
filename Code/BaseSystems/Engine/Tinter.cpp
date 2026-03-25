// Tinter.cpp
#include "Tinter.hpp"

void Tinter::awake() {}

void Tinter::init()
{
    originalColor = entity->mesh->color;
}

void Tinter::Trigger()
{
    timer = duration;
    tinting = true;
}

void Tinter::update()
{
    if (!tinting) return;

    timer -= (f32)AEFrameRateControllerGetFrameTime();

    if (timer <= 0.f)
    {
        timer = 0.f;
        tinting = false;
        entity->mesh->color = originalColor;
        return;
    }

    float t = timer / duration;
    Color tintedColor
    {
        static_cast<uint8_t>(255 * t + originalColor.R * (1.0f - t)),
        static_cast<uint8_t>(originalColor.G * (1.0f - t)),
        static_cast<uint8_t>(originalColor.B * (1.0f - t)),
        originalColor.A
    };
    entity->mesh->color = tintedColor;
}

void Tinter::fixedUpdate() {}
void Tinter::destroy() {}