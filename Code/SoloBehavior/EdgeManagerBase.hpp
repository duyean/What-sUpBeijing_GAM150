#pragma once
#ifndef EdgeManager
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
#include "../Code/SoloBehavior/SceneEdge.hpp"

using namespace std;

class EntityManager;


class EdgeManagerBase : public SoloBehavior
{
private:

	SceneEdge* base_exit = nullptr;
	TransitionScreen* ts = nullptr;

	bool switch_BC = false;

	void UpdateEdges();
public:

	EntityManager* enSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	EdgeManagerBase() : base_exit{ nullptr } {}
	~EdgeManagerBase() {}

};


#endif