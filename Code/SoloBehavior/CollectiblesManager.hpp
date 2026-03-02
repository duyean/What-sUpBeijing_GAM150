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

using namespace std;

class EntityManager;

class CollectiblesManager : public SoloBehavior
{
private:
	
public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	CollectiblesManager(){}
	~CollectiblesManager() {}
};


#endif