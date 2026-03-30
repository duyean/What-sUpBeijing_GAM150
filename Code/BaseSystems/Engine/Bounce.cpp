#include "Bounce.hpp"
#include "../EaseFunctions/AEVEC2OVERLOAD.hpp"

void Bounce::awake()
{
}

void Bounce::init()
{
    cleanScale = entity->transform->getScale();
    cleanPos = entity->transform->getPosition();
}

void Bounce::update()
{
    // Always sync cleanPos from actual position minus current bounce offset
    AEVec2 currentPos = entity->transform->getPosition();
    cleanPos = { currentPos.x, currentPos.y - currentBounceOffset };

    time += (f32)AEFrameRateControllerGetFrameTime() * spd;
    if (time > maxTime) time -= maxTime;

    f32 wave = -(fabsf(AESinDeg(time * 360.0f))) - 0.01f;
    f32 scaleDiff = AEClamp(wave * sqs, -0.9f, 0.0f);

    if (fabsf(scaleDiff) < 0.001f)
    {
        entity->transform->setScale(cleanScale);
        entity->transform->setPosition(cleanPos);
        // Do NOT re-read cleanScale / cleanPos here
    }

    AEVec2 tempScale
    {
        cleanScale.x * (1.0f - scaleDiff),
        cleanScale.y * (1.0f + scaleDiff)
    };
    entity->transform->setScale(tempScale);

    currentBounceOffset = (cleanScale.y * scaleDiff) * 0.5f;
    AEVec2 tempPosition
    {
        cleanPos.x,
        cleanPos.y + currentBounceOffset
    };
    entity->transform->setPosition(tempPosition);
}

void Bounce::fixedUpdate()
{
}

void Bounce::destroy()
{
}