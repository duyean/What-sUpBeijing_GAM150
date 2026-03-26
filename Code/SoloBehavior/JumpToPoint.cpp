// JumpToPoint.cpp
#include "JumpToPoint.hpp"

// ease in: slow start, fast end (accelerate into hit)
static float EaseIn(float t)
{
    return t * t;
}

// ease out: fast start, slow end (decelerate on return)
static float EaseOut(float t)
{
    return 1.0f - (1.0f - t) * (1.0f - t);
}

// quadratic bezier for arc height
static AEVec2 Bezier(AEVec2 start, AEVec2 end, float arcHeight, float t)
{
    // control point is midpoint lifted by arcHeight
    AEVec2 control
    {
        (start.x + end.x) * 0.5f,
        (start.y + end.y) * 0.5f + arcHeight
    };

    float oneMinusT = 1.0f - t;
    return
    {
        oneMinusT * oneMinusT * start.x + 2.0f * oneMinusT * t * control.x + t * t * end.x,
        oneMinusT * oneMinusT * start.y + 2.0f * oneMinusT * t * control.y + t * t * end.y
    };
}

void JumpToPoint::awake() {}
void JumpToPoint::init()
{
    startPos = entity->transform->getPosition();
}

void JumpToPoint::Trigger(AEVec2 _targetPos, float _arcHeight, float _duration)
{
    startPos = entity->transform->getPosition();
    targetPos = _targetPos;
    arcHeight = _arcHeight;
    duration = _duration;
    timer = 0.f;
    jumping = true;
    returning = false;
}

void JumpToPoint::update()
{
    if (!jumping && !returning) return;

    timer += (f32)AEFrameRateControllerGetFrameTime();
    float t = AEClamp(timer / duration, 0.0f, 1.0f);

    if (jumping)
    {
        // ease in to target, slow start fast end
        float easedT = EaseIn(t);
        AEVec2 pos = Bezier(startPos, targetPos, arcHeight, easedT);
        entity->transform->setPosition(pos);

        if (t >= 1.0f)
        {
            // reached target, start return
            jumping = false;
            returning = true;
            timer = 0.f;
        }
    }
    else if (returning)
    {
        // ease out back to start, fast start slow end
        float easedT = EaseOut(t);
        AEVec2 pos = Bezier(targetPos, startPos, arcHeight, easedT);
        entity->transform->setPosition(pos);

        if (t >= 1.0f)
        {
            // back to original, done
            returning = false;
            entity->transform->setPosition(startPos);
        }
    }
}

void JumpToPoint::fixedUpdate() {}
void JumpToPoint::destroy() {}