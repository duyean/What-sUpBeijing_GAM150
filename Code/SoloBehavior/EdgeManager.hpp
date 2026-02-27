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
#include "../Code/Map/NavigationData.hpp"
#include "../Code/SoloBehavior/SceneEdge.hpp"

using namespace std;

class EntityManager;


class EdgeManager : public SoloBehavior
{
private:
	NavigationData& map;
	Entity* N_path;
	Entity* E_path;
	Entity* S_path;
	Entity* W_path;

	SceneEdge* SE_N = nullptr;
	SceneEdge* SE_E = nullptr;
	SceneEdge* SE_S = nullptr;
	SceneEdge* SE_W = nullptr;

	Entity* player = nullptr;
public:

	EntityManager* enSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	EdgeManager(NavigationData& _map) : N_path{ nullptr }, E_path{ nullptr }, S_path{ nullptr }, W_path{ nullptr }, map{ _map } {}
	~EdgeManager() {}

};


#endif