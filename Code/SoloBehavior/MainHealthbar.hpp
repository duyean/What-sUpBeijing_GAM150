/*!
@file MainHealthbar.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 10/3/26
@brief
This file contains the interface for the top left battle UI display
*//*______________________________________________________________________*/

#pragma once
#include "AEEngine.h"
#include "../BaseSystems/Engine/OOP.hpp"
#include "../BaseSystems/Engine/EntityManager.hpp"
#include "../Code/Combat/BattleManager/BattleManager.hpp"

/*!***********************************************************************
* \class MainHealthbar
* \brief
* The class that defines the top left battle UI display
*************************************************************************/
class MainHealthbar : public SoloBehavior
{
private:
	//Stores the fixed positions of entity elements
	const AEVec2 currentTurnTextPos = {-0.915f, 0.9f};

	//Stores the fixed positions of entity elements
	const AEVec2 activeUnitHPPos = { -0.8f * AEGfxGetWindowWidth() / 2, 0.9f * AEGfxGetWindowHeight() / 2};
public:
	//Pointer to entity system
	EntityManager* enSystem = nullptr;

	//Pointer to the entity manager
	BattleManager* battleManager = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	//Default constructor
	MainHealthbar() = default;

	//Default destructor
	~MainHealthbar() = default;
};

