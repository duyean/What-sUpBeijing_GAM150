/*!************************************************************************
* \file BattleManager.hpp
* \author Wayne Lion Wei Jynn
* \par DP email: lion.w\@digipen.edu
* \par Course: CSD1451-b
* \brief
*  This file contains the declarations of functions for the 
   DecisionBoxManager
**************************************************************************/

#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/Button.hpp"

/*!***********************************************************************
* \class DecisionBoxManager
* \brief
*  The SoloBehavior object for BattleManager
*************************************************************************/
class DecisionBoxManager : public SoloBehavior
{
public:
	/*!***********************************************************************
	* \brief
	*  Toggles the Decision Box showing
	* \param[in] toggle
	*  current active status of the Decision Box
	*************************************************************************/
	void ToggleDecisionBox(bool toggle);
	Button* leftButton = nullptr, *rightButton = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};

