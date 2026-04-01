/*!
@file HEALTHBAR1.hpp
@author Wayne Lion (lion.w), Edmund Tan
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the interface for the Enemy Health Bar components
*//*______________________________________________________________________*/

#pragma once
#include <iostream>
#include <cstdint>
#include <vector>
#include "AEEngine.h"
#include "../BaseSystems/Engine/OOP.hpp"
#include "../BaseSystems/Engine/Colors.hpp"

using namespace std;

//Forward declaration
class EntityManager;

/*!***********************************************************************
* \class Healthbar1
* \brief
* TThe class to display enemy health bars in battle
*************************************************************************/
class Healthbar1: public SoloBehavior
{
private:
	//The color of the health bar
	Color color;
public:

	//The health bar entity
	Entity* en = nullptr;

	//The background health bar entity
	Entity* hpBarBG = nullptr;

	//Pointer to entity system
	EntityManager* enSystem = nullptr;

	//A vector to store the status icon entities
	std::vector<Entity*> statusIcons = {};

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	//Default Constructor
	Healthbar1() {
		enSystem = nullptr;
	}

	//Default Destructor
	~Healthbar1() = default;

};