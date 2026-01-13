/*!
@file SplashScreen.hpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 13/1/26
@brief
This file contains the declarations of functions for splash screen
*//*______________________________________________________________________*/
#pragma once
#include "Mesh.hpp"
#include "Sprite.hpp"
#include "GameState.hpp"
#include "GameStateManager.hpp"

class SplashScreen : public GameState
{
private:
	//CP_Image logo;
	Sprite logo;
	float curSplashTimer;
	float maxSplashTimer = 6.f;
	int splashOpacity = 0;

public:
	SplashScreen();
	~SplashScreen();

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

