/*!
@file Tinter.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the Tinter component which applies a temporary colour
tint effect to the owning entity's Mesh for a configurable duration
*//*______________________________________________________________________*/
#pragma once
#ifndef _Tinter_
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


class Tinter : public SoloBehavior
{

    float duration = 1.f;
    float timer = 0.f;
    Color originalColor{};
    bool tinting = false;
public:
	/*!***********************************************************************
	* \brief
	* Called once when the component is first created, before init
	*************************************************************************/
    void awake() override;

	/*!***********************************************************************
	* \brief
	* Called once before the first update, used for initialisation
	*************************************************************************/
    void init() override;

	/*!***********************************************************************
	* \brief
	* Called every frame, advances the tint timer and restores the original
	* colour once the duration has elapsed
	*************************************************************************/
    void update() override;

	/*!***********************************************************************
	* \brief
	* Called at a fixed timestep, used for physics-based updates
	*************************************************************************/
    void fixedUpdate() override;

	/*!***********************************************************************
	* \brief
	* Called when the component is destroyed, used for cleanup
	*************************************************************************/
    void destroy() override;

	/*!***********************************************************************
	* \brief
	* Triggers the tint effect, resetting the timer and applying the tint colour
	*************************************************************************/
    void Trigger();

	/*!***********************************************************************
	* \brief
	* Constructs a Tinter component with the given effect duration
	* \param[in] _duration
	* The duration of the tint effect in seconds
	*************************************************************************/
    Tinter(float _duration) : duration(_duration) {}
    ~Tinter() {}

};


#endif

