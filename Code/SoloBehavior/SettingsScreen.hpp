/******************************************************************************/
/*!
\file   SettingsScreen.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for the Settings Screen
*/
/******************************************************************************/

#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"

class SettingsScreen : public SoloBehavior
{
private:	
	// Pointer to the entity manager
	EntityManager* enSystem = nullptr;
	// Vector of entities in the settings screen
	std::vector<Entity*> prevDisplay;

	// Sliders for BGM and SFX
	Slider* bgm_sl = nullptr;
	Slider* sfx_sl = nullptr;

	// Whether the settings screen should be displaying
	bool isDisplaying = false;
public:
	/*!***********************************************************************
	\brief This function shows or hides the settings screen
	*************************************************************************/
	void ShowSettings(bool canShow);
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	/*!***********************************************************************
	\brief This function returns if the settings screen is currently displaying
	\return If the settings are currently displayed
	*************************************************************************/
	bool IsDisplaying() const { return isDisplaying; }
	/*!***********************************************************************
	\brief Adds entities to the prevDisplay vector
	\param Entity*
	*************************************************************************/
	void AddPrevDisplayEntity(Entity* en);
	/*!***********************************************************************
	\brief Default constructor
	*************************************************************************/
	SettingsScreen() : isDisplaying(false){}
	/*!***********************************************************************
	\brief Default destructor
	*************************************************************************/
	~SettingsScreen() {};
};