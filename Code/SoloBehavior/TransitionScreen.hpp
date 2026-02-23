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

class TransitionScreen: public SoloBehavior
{
private:
	float curSplashTimer;
	float maxSplashTimer;
	float splashOpacity;
public:

	EntityManager* enSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	TransitionScreen() {
		curSplashTimer = 0.f;
		maxSplashTimer = 6.f;
		splashOpacity = 0.f;
	}

	~TransitionScreen(){}

};


#endif