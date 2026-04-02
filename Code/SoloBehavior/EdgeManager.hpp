/******************************************************************************/
/*!
\file   EdgeManager.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Edge Manager
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
#include "../Code/Map/NavigationData.hpp"
#include "../Code/SoloBehavior/SceneEdge.hpp"

using namespace std;

class EntityManager;


class EdgeManager : public SoloBehavior
{
private:
	//reference to the Navigation Data
	NavigationData& map;

	//Pointers to the different Edge Entities
	Entity* N_path;
	Entity* E_path;
	Entity* S_path;
	Entity* W_path;

	//Pointers to the different Scene Edge Classes
	SceneEdge* SE_N = nullptr;
	SceneEdge* SE_E = nullptr;
	SceneEdge* SE_S = nullptr;
	SceneEdge* SE_W = nullptr;

	//pointer to player Entity object
	Entity* player = nullptr;
	//pointer to shop Entity object
	Entity* shop = nullptr;
	//pointer to Transition Screen
	TransitionScreen* ts = nullptr;
	//pointer to the noitfication object
	Entity* notif = nullptr;

	//boolean to check if player has traveled between node
	bool hasTraveled = false;
	//boolean to switch to base camp
	bool switch_BC = false;
/*!***********************************************************************
\brief This function checks each edge from the map and updates the edges
*************************************************************************/
	void UpdateEdges();
/*!***********************************************************************
\brief This function checks each neighbour node type
*************************************************************************/
	void CheckNeighborNode(const MapNode& node);
public:

	EntityManager* enSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
/*!***********************************************************************
\brief Single arguement constructor for EdgeManager. Takes in reference
	   to NavigationData 
\param Navigation&
*************************************************************************/
	EdgeManager(NavigationData& _map) : N_path{ nullptr }, E_path{ nullptr }, S_path{ nullptr }, W_path{ nullptr }, map{ _map } {}
	//dstr
	~EdgeManager() {}

};


#endif