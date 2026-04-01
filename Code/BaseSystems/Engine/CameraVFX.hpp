/*!
@file CameraVFX.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the CameraVFX component which handles camera shake visual effects
*//*______________________________________________________________________*/
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
	* Called every frame, handles the camera shake offset logic
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
	* Triggers the camera shake effect using the configured duration and intensity
	*************************************************************************/
    void TriggerShake();

	/*!***********************************************************************
	* \brief
	* Sets the duration of the camera shake effect
	* \param[in] newDuration
	* The new duration value in seconds
	*************************************************************************/
    void SetShakeDuration(float newDuration) { duration = newDuration; }

	/*!***********************************************************************
	* \brief
	* Constructs a CameraVFX component with the given shake parameters
	* \param[in] _duration
	* The duration of the shake in seconds
	* \param[in] _intensity
	* The intensity (magnitude) of the shake offset
	*************************************************************************/
    CameraVFX(float _duration, float _intensity)
        : duration(_duration), intensity(_intensity) {
    }
    ~CameraVFX() {}
};
#endif

