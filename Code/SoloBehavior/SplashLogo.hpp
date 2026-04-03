/******************************************************************************/
/*!
\file   SplashLogo.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for SplashLogo class
*/
/******************************************************************************/

#pragma once
#ifndef _HealthBar1_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "../BaseSystems/Engine/OOP.hpp"
#include "../BaseSystems/Engine/Colors.hpp"
#include "../BaseSystems/EaseFunctions/Math.hpp"
#include "../BaseSystems/Engine/EntityManager.hpp"
#include "../SceneHandler_WZBJ_Pak.hpp"

using namespace std;

class EntityManager;

class SplashLogo: public SoloBehavior
{
private:
	//private splash logo variables
	float curSplashTimer;
	float maxSplashTimer;
	float splashOpacity;
	bool transition;
public:

	EntityManager* enSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	//default constr
	SplashLogo() {
		curSplashTimer = 0.f;
		maxSplashTimer = 6.f;
		splashOpacity = 0.f;
		transition = true;
	}
	//destr
	~SplashLogo(){}

};


#endif