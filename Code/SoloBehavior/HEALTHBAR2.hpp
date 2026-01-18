#pragma once
#ifndef _HealthBar2_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "OOP.hpp"
#include "Colors.hpp"


using namespace std;

class EntityManager;

class Healthbar2 : public SoloBehavior
{
public:

	float hideAtValue = 100.f;
	EntityManager* enSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	Healthbar2()
	{
		enSystem = nullptr;
	}

	Healthbar2(float a)
	{
		hideAtValue = a;
	}

	~Healthbar2()
	{

	}

};


#endif