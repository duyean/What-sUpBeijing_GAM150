/*!
@file BattleStatUI.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the interface for a 
Debug Combat Screen entity for our game.
*//*______________________________________________________________________*/

#pragma once
#include "../UI_WZBJ_Pak.hpp"

//Forward declaration
class BattleManager;

/*!***********************************************************************
* \class BattleStatUI
* \brief
* The class that defines the combat battle debug screen UI
*************************************************************************/
class BattleStatUI : public SoloBehavior
{
	public:
	//Default constructor
	BattleStatUI();

	/*!***********************************************************************
	* \brief
	* Toggles whether to render the debug screen
	*************************************************************************/
	void ToggleRender();

	/*!***********************************************************************
	* \brief
	* Assigns the battle manager to the class
	* \param BattleManager
	* A pointer to the battle manager
	*************************************************************************/
	void SetBattleManager(BattleManager*);

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	private:
	//Boolean to indicate whether the UI is rendering
	bool render;
	//Pointer to the battle manager
	BattleManager* battleManager = nullptr;
	
};