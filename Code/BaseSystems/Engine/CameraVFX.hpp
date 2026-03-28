// CameraShake.hpp
#pragma once
#ifndef _CameraVFX_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h>
#include <mutex>
#include <map>
#include <memory>
#include "AEEngine.h"
#include "OOP.hpp"


class CameraVFX : public SoloBehavior
{
    float duration = 0.f;
    float timer = 0.f;
    float intensity = 0.f;
    float originalX = 0.f;
    float originalY = 0.f;
    bool shaking = false;
public:
    void awake() override;
    void init() override;
    void update() override;
    void fixedUpdate() override;
    void destroy() override;
    void TriggerShake();
    void SetShakeDuration(float newDuration) { duration = newDuration; }
    CameraVFX(float _duration, float _intensity)
        : duration(_duration), intensity(_intensity) {
    }
    ~CameraVFX() {}
};
#endif