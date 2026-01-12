/*!
@file SplashScreen.cpp
@author Toby Chua (t.chua)
@course CSD1401
@section A
@Final Project
@date 16 September 2025
@brief
This file contains the definitions for the collection of functions in SplashScreen.h
*//*______________________________________________________________________*/
#include "SplashScreen.hpp"

//SplashScreen::SplashScreen():
//	//logo(NULL)
//{
//	curSplashTimer = maxSplashTimer;
//}

SplashScreen::~SplashScreen()
{
}

/*!
@brief Initialize splash screen variables

Overwrites virtual GameState::Init().
This function loads splash screen image

@param void
@return void
*//*______________________________________________________________*/
void SplashScreen::Init()
{
	//logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
}

/*!
@brief Updates splash screen frame

Overwrites virtual GameState::Update(). 
This function updates variables in splash screen per frame to
makes image fade in and out before loading main menu.

@param float
@return void
*//*______________________________________________________________*/
void SplashScreen::Update(float _dt)
{
	/*if (curSplashTimer < 0 || CP_Input_KeyDown(KEY_SPACE)) {
		GameStateManager::GetInstance()->NextScene(GameStateManager::MAIN_MENU);
		return;
	}*/

	curSplashTimer -= _dt;

	
	/*if (curSplashTimer > maxSplashTimer/2) {
		splashOpacity = CP_Math_LerpInt(0, 255, (maxSplashTimer - curSplashTimer) / (maxSplashTimer / 2));
	}
	else {
		splashOpacity = CP_Math_LerpInt(255, 0, (maxSplashTimer / 2 - curSplashTimer) / (maxSplashTimer / 2));
	}*/
}

/*!
@brief Render splash screen

Overwrites virtual GameState::Render().
This function renders splash screen image

@param void
@return void
*//*______________________________________________________________*/
void SplashScreen::Render()
{
	/*CP_Image_Draw(logo, 
		(float)(CP_System_GetWindowWidth() / 2.f), 
		(float)(CP_System_GetWindowHeight() / 2.f), 
		(float)CP_Image_GetWidth(logo), 
		(float)CP_Image_GetHeight(logo),
		splashOpacity);*/
}

/*!
@brief Clears splash screen variables

Overwrites virtual GameState::Exit().
This function frees splash screen image used.

@param void
@return void
*//*______________________________________________________________*/
void SplashScreen::Exit()
{
	/*CP_Image_Free(logo);*/
}
