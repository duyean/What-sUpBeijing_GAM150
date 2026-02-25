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

enum T_State
{
	T_IN,
	T_OUT,
	DONE
};

class EntityManager;

class TransitionScreen: public SoloBehavior
{
private:
	float transitionSpeed;
	bool t_buffer;
	T_State state;

public:

	EntityManager* enSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
	void SetState(T_State _state) { state = _state; t_buffer = true; }
	T_State GetState() const { return state; }

	TransitionScreen() = default;

	TransitionScreen(T_State _state) {
		transitionSpeed = 1000.f;
		t_buffer = false;
		state = _state;
	}

	~TransitionScreen(){}

};


#endif