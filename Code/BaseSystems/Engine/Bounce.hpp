#pragma once
#ifndef _Transform_
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


using namespace std;


class Bounce : public SoloBehavior
{

	AEGfxVertexList* targetMesh = nullptr;
	float time = 0.f;
	float maxTIme = 1.f;

public:

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	Bounce()
	{

	}

	~Bounce()
	{

	}

};


#endif