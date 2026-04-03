/*!
@file MovesUI.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the implementation of the moves UI
*//*______________________________________________________________________*/
#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/Combat/Move.hpp"
#include "../UI_WZBJ_Pak.hpp"

// Forward declare the BattleManager class
class BattleManager;

/*!***********************************************************************
* \class MovesUI
* \brief
* The class to handle all move UI elements
*************************************************************************/
class MovesUI : public SoloBehavior
{
private:
	//The BattleManager 
	BattleManager* battleManager = nullptr;
	//The four move buttons
	Button* moveButton1 = nullptr;
	Button* moveButton2 = nullptr;
	Button* moveButton3 = nullptr;
	Button* moveButton4 = nullptr;

	//Text boxes for the move names
	TextBox* tb1 = nullptr;
	TextBox* tb2 = nullptr;
	TextBox* tb3 = nullptr;
	TextBox* tb4 = nullptr;

	//Tooltip that displays when hovering over the move
	Entity* tooltip = nullptr;
	//Whether the tooltip should be displayed
	bool canDisplay = false;

	//Current character in play
	Character* currentCh = nullptr;
	//The current move slot
	MOVE_SLOT currMoveSlot = MOVE_SLOT::NONE;

	/*!***********************************************************************
	* \brief
	* Uses the current move
	* \param ms
	* Which move slot the move is at
	* \param ch
	* What character is using the move
	*************************************************************************/
	void UseCurrMove(MOVE_SLOT ms, Character* ch);
	/*!***********************************************************************
	* \brief
	* Displays the tooltip of the move
	* \param ms
	* Which move slot to display
	*************************************************************************/
	void DisplayToolTip(MOVE_SLOT ms);
	/*!***********************************************************************
	* \brief
	* Hides the move tooltip
	*************************************************************************/
	void HideToolTip();
public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};