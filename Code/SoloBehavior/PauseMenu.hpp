/******************************************************************************/
/*!
\file   PauseMenu.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for the Pause Menu
*/
/******************************************************************************/

#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/TransitionScreen.hpp"
#include "../Code/SoloBehavior/SettingsScreen.hpp"

class PauseMenu : public SoloBehavior
{
private:
	/*!***********************************************************************
	\brief This function resumes the game after pausing
	*************************************************************************/
	void ResumeGame();
	/*!***********************************************************************
	\brief This function quits the game
	*************************************************************************/
	void QuitGame();
	/*!***********************************************************************
	\brief This function brings the game to the main menu
	*************************************************************************/
	void QuitToMainMenu();
	// The Entities to display in the PauseMenu
	std::vector<Entity*> prevDisplay;

	// The transition screen
	TransitionScreen* ts_comp = nullptr;
	// Pointer to the entity manager
	EntityManager* enSystem = nullptr;
	// Pointer to the settings screen
	SettingsScreen* settings = nullptr;
	// Whether the PauseMenu should be displayed
	bool canDisplay = true;
public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
	/*!***********************************************************************
	\brief Adds entities to the prevDisplay vector
	\param Entity*
	*************************************************************************/
	void AddPrevDisplayEntity(Entity* en);

	/*!***********************************************************************
	\brief Default constructor
	*************************************************************************/
	PauseMenu() {}
	/*!***********************************************************************
	\brief Default destructor
	*************************************************************************/
	~PauseMenu() {}
};