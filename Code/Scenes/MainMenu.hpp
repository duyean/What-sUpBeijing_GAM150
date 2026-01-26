/*!
@file MainMenu.hpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 13/1/26
@brief
This file contains the declarations of functions for the main menu
*//*______________________________________________________________________*/
#pragma once
#include "../BaseSystems_WZBJ_Pak.hpp"
#include "../SceneHandler_WZBJ_Pak.hpp"


class MainMenu : public GameState
{
private:


public:
	MainMenu();
	~MainMenu();

	/*!
	@brief Initialize Splash Screen variables
	@param void
	@return void
	*//*______________________________________________________________*/
	void Init() override;
	/*!
	@brief Updates splash screen frame
	@param float
	@return void
	*//*______________________________________________________________*/
	void Update(float _dt) override;
	/*!
	@brief Render splash screen
	@param void
	@return void
	*//*______________________________________________________________*/
	void Render() override;
	/*!
	@brief Clears splash screen variables
	@param void
	@return void
	*//*______________________________________________________________*/
	void Exit() override;
};