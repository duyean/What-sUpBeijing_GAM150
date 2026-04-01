/*!
@file Bounce.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the generation of shapes and textures
*//*______________________________________________________________________*/

#pragma once
#ifndef _Bounce_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include "AEEngine.h"
#include "OOP.hpp"
#include "Colors.hpp"
#include "Entity.hpp"


class Bounce : public SoloBehavior
{

    float time = 0.f;
    float maxTime = 1.f;
    float spd = 1.f;
    float sqs = 0.05f;
    float lastScaleDiff = 0.f;
    float lastPosOffset = 0.f;
    AEVec2 cleanScale{ 1.0f, 1.0f };
    AEVec2 cleanPos{ 1.0f, 1.0f };
    f32 currentBounceOffset = 0.0f;


public:
    void awake() override;
    void init() override;
    void update() override;
    void fixedUpdate() override;
    void destroy() override;
    Bounce(float _timer, float _maxTime, float _spd, float _sqs)
        : time(_timer), maxTime(_maxTime), spd(_spd), sqs(_sqs) {
    }
    ~Bounce() {}

};


#endif