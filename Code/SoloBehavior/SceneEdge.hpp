/******************************************************************************/
/*!
\file   SceneEdge.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Scene Edge 
*/
/******************************************************************************/

#pragma once
#ifndef SceneEdge
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

using namespace std;

class EntityManager;

class SceneEdge: public SoloBehavior
{
private:
	//pointer to the box collider 
	BoxCollider2D* col;
	//pointer to the transtion screen
	TransitionScreen* t_screen;
	//boolean to change once only
	bool changeBuffer;

	void onHit(BoxCollider2D* other);
	void onStay(BoxCollider2D* other);
	void onExit(BoxCollider2D* other);

public:
	//pointer to Entity Manager
	EntityManager* enSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	//boolean for if can trigger
	bool triggerBuffer = false;
	//default ctr
	SceneEdge() : col{nullptr}, t_screen{nullptr}, changeBuffer{false} {}
	//dstr
	~SceneEdge(){}

};


#endif