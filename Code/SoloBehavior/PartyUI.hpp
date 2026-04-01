/*!
@file PartyUI.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 11/3/26
@brief
This file contains the interface for a party UI display
*//*______________________________________________________________________*/

#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include <array>

//Forward declaration of BattleManager
class BattleManager;

/*!***********************************************************************
* \class PartyUI
* \brief
* The class that defines the components of the party UI display
*************************************************************************/
class PartyUI : public SoloBehavior
{
	//Store the positions of the icon in the UI
	const std::vector<AEVec2> iconPositions = { {60, -AEGfxGetWindowHeight() * 0.7f * 0.5f}, {300, -AEGfxGetWindowHeight() * 0.7f * 0.5f}, {550, -AEGfxGetWindowHeight() * 0.7f * 0.5f} };
	
	//Reference to the battle manager
	BattleManager* battleManager = nullptr;
	
	//Vector to store the icons of the player character's icons
	std::vector<Entity*> icons;

	//Vector to store the health bar entities of each player character
	std::vector<Entity*> healthBars;

	//Array to store 3 vectors of entities that represent modifier icons
	std::array<std::vector<Entity*>, 3> modifierIcons = {};

	//Pointer to the modifier tooltip entity
	Entity* modifierTooltip = nullptr;

	//A string to store text for the tooltip buffer
	std::string toolTipBuffer;

public:
	/*!***********************************************************************
	* \brief
	* Add an icon to the vector of Entities
	* \param[in] en
	* A pointer to the Entity
	*************************************************************************/
	void AddIcon(Entity* en);

	/*!***********************************************************************
	* \brief
	* Add an modifier to the vector in the array specified by index
	* \param[in] index
	* The index to determine which vector to add into
	* \param[in] en
	* The entity pointer to the modifier icon
	*************************************************************************/
	void AddModifierIcon(int index, Entity* en);

	/*!***********************************************************************
	* \brief
	* Add a health bar icon to the vector of Entities
	* \param[in] en
	* A pointer to the health bar entity
	*************************************************************************/
	void AddHealthBarEntity(Entity* en);

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	/*!***********************************************************************
	* \brief
	* Checks whether the mouse cursor is hovering over the transform
	* \param[in] mouseX
	* The mouse X coordinate
	* \param[in] mouseY
	* The mouse Y coordinate
	* \param[in] transform
	* A pointer to the transform to check for
	* \return
	* True if the mouse is over one of the modifier icons
	*************************************************************************/
	bool IsMouseOverIcon(const s32& mouseX, const s32& mouseY, const Transform2D* transform);
};