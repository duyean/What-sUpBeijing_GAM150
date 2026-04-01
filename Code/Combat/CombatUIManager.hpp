/*!
@file CombatUIManager.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the implementation of a CombatUIManager
*//*______________________________________________________________________*/

#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Combat/Globals/Globals.hpp"
#include <queue>

/*!***********************************************************************
* \class CombatUIManager
* \brief
* The class to handle all Combat UI elements
*************************************************************************/
class CombatUIManager : public SoloBehavior
{
private:

	//Queue to store the pending text elements to prevent overlapping
	std::queue<std::unique_ptr<Entity>> damageNumbers, messages;

	//Doubles to handle delay timers
	double dnDelay = 0, messDelay = 0;

	//Singleton instance
	static CombatUIManager* instance;
public:
	//Singleton Accessor
	static CombatUIManager& Instance();

	/*!***********************************************************************
	* \brief
	* Create a damage number at the specified position
	* \param position
	* The position to show the damage number
	* \param info
	* The damage info to help load the damage number
	*************************************************************************/
	void CreateDamageNumber(AEVec2 position, Game::DamageInfo info);

	/*!***********************************************************************
	* \brief
	* Creates a message text at the specified position
	* \param position
	* The position to render the text
	* \param text
	* The text to show
	* \param color
	* The color of the text. Default is white
	* \param size
	* The scale of the text. Default is 1.0f
	*************************************************************************/
	void CreateMessageText(AEVec2 position, std::string text, Color color = Color(255, 255, 255, 1), float size = 1);

	/*!***********************************************************************
	* \brief
	* Clears the queues and reset all data
	*************************************************************************/
	void Reset();

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};