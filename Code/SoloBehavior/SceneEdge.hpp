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
#include "../Scenes/SceneHandler/GameStateManager.hpp"
#include "../BaseSystems/Engine/BoxCollider2D.hpp"
#include "../Code/SoloBehavior/TransitionScreen.hpp"

using namespace std;

class EntityManager;

enum EdgeType
{
	BASE,
	NUM_PATHS,
};

class SceneEdge: public SoloBehavior
{
private:
	EdgeType type;
	BoxCollider2D* col;
	TransitionScreen* t_screen;
	bool changeBuffer;

	void onHit(BoxCollider2D* other);
	void onStay(BoxCollider2D* other);
	void onExit(BoxCollider2D* other);
public:

	EntityManager* enSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	SceneEdge(EdgeType _type) : type{ _type }, col{ nullptr }, t_screen{nullptr}, changeBuffer {false} {}
	~SceneEdge(){}

};


#endif