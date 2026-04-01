/*!
@file Bounce.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the Bounce component which applies a procedural bounce
animation to the owning entity's scale and position over time
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
	/*!***********************************************************************
	* \brief
	* Called once when the component is first created, before init.
	* Records the entity's clean scale and position for reset purposes
	*************************************************************************/
    void awake() override;

	/*!***********************************************************************
	* \brief
	* Called once before the first update, used for initialisation
	*************************************************************************/
    void init() override;

	/*!***********************************************************************
	* \brief
	* Called every frame, advances the bounce timer and applies squash and
	* stretch offsets to the entity's transform
	*************************************************************************/
    void update() override;

	/*!***********************************************************************
	* \brief
	* Called at a fixed timestep, used for physics-based updates
	*************************************************************************/
    void fixedUpdate() override;

	/*!***********************************************************************
	* \brief
	* Called when the component is destroyed, restores the entity's original
	* scale and position before cleanup
	*************************************************************************/
    void destroy() override;

	/*!***********************************************************************
	* \brief
	* Constructs a Bounce component with the given animation parameters
	* \param[in] _timer
	* The initial elapsed time of the bounce animation
	* \param[in] _maxTime
	* The total duration of one bounce cycle in seconds
	* \param[in] _spd
	* The speed multiplier of the bounce oscillation
	* \param[in] _sqs
	* The squash and stretch intensity factor
	*************************************************************************/
    Bounce(float _timer, float _maxTime, float _spd, float _sqs)
        : time(_timer), maxTime(_maxTime), spd(_spd), sqs(_sqs) {
    }
    ~Bounce() {}

};


#endif

