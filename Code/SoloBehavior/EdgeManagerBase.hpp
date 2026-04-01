/******************************************************************************/
/*!
\file   EdgeManager.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Edge Manager Base
*/
/******************************************************************************/

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
	//pointer to the SceneEdge base exit
	SceneEdge* base_exit = nullptr;
	//pointer to the Transition Screen
	TransitionScreen* ts = nullptr;
	//pointer to the Entity Player Object
	Entity* player = nullptr;

	//boolean for the switch to the base camp
	bool switch_BC = false;
/*!***********************************************************************
\brief This function checks each edge from the map and updates the edges
*************************************************************************/
	void UpdateEdges();
public:

	EntityManager* enSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
	//default ctr
	EdgeManagerBase() : base_exit{ nullptr } {}
	//dstr
	~EdgeManagerBase() {}

};


#endif