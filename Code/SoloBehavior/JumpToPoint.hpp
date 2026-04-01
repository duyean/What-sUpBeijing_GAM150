/*!
@file JumpToPoint.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the animation jumping code
*//*______________________________________________________________________*/

#pragma once
#ifndef _JumpToPoint_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "../BaseSystems/Engine/OOP.hpp"
#include "../BaseSystems/Engine/Colors.hpp"
#include "../BaseSystems/Engine/Entity.hpp"

class JumpToPoint : public SoloBehavior
{
    AEVec2 startPos{};
    AEVec2 targetPos{};
    float arcHeight = 100.f;
    float duration = 1.f;
    float timer = 0.f;
    bool jumping = false;
    bool returning = false;
public:
    void awake() override;
    void init() override;
    void update() override;
    void fixedUpdate() override;
    void destroy() override;

/*!***********************************************************************
* \brief
* Trigger animation
*************************************************************************/
    void Trigger(AEVec2 _targetPos, float _arcHeight, float _duration);
    JumpToPoint() {}
    ~JumpToPoint() {}
};
#endif