#pragma once
#ifndef _HealthBar1_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "../BaseSystems/Engine/OOP.hpp"
#include "../BaseSystems/Engine/Colors.hpp"


using namespace std;

class EntityManager;

class SplashLogo: public SoloBehavior
{
private:
	float curSplashTimer;
	float maxSplashTimer = 6.f;
	int splashOpacity = 0;

public:

	EntityManager* enSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	SplashLogo() {
		enSystem = nullptr;
	}

	~SplashLogo(){}

};


#endif