/******************************************************************************/
/*!
\file   MainMenu.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Main Menu
*/
/******************************************************************************/

#pragma once
#include "../BaseSystems_WZBJ_Pak.hpp"
#include "../SceneHandler_WZBJ_Pak.hpp"

#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/TransitionScreen.hpp"
#include "../Code/SoloBehavior/SettingsScreen.hpp"

class MainMenu : public GameState
{
private:
	//pointer to entity system
	EntityManager* enSystem = nullptr;
	//pointer to Mesh Gen system
	MeshGen* meshSystem = nullptr;
	//pointer to Transition Screen Entity object
	TransitionScreen* ts_comp = nullptr;

/*!***********************************************************************
\brief Function to switch to the game scene.
*************************************************************************/
	void SwitchToGame();
/*!***********************************************************************
\brief This function resets the game to a new state. Clearing all saves.
*************************************************************************/
	void PlayNewSave();
/*!***********************************************************************
\brief Function to quit the game.
*************************************************************************/
	void QuitGame();
public:
	MainMenu();
	~MainMenu();

/*!***********************************************************************
\brief This function loads all Main Menu objects.
*************************************************************************/
	void Load() override;
/*!***********************************************************************
\brief This function unloads all Main Menu objects.
*************************************************************************/
	void Unload() override;
};

