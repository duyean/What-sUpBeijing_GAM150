/*!
@file SplashScreen.cpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 13/1/26
@brief
This file contains the definitions for the collection of functions in SplashScreen.h
*//*______________________________________________________________________*/
#include "SplashScreen.hpp"
#include "Math.hpp"

SplashScreen::SplashScreen()
{
	curSplashTimer = maxSplashTimer;
}

SplashScreen::~SplashScreen()
{
}

AEGfxVertexList* Rectangle()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	return AEGfxMeshEnd();

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
	logo.SetMesh(Rectangle());
	logo.SetTexture(AEGfxTextureLoad("Assets/Images/DigiPen_Singapore_WEB_RED.png"));
	logo.SetScale(1525, 445);
	logo.SetPosition(0, 0);
	logo.SetColor(Color4(1, 1, 1, 1));
	logo.opacity = 0;
	logo.SetRenderMode(AE_GFX_RM_TEXTURE);
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
	if (curSplashTimer < 0 || AEInputCheckCurr(VK_SPACE)){
		GameStateManager::GetInstance()->NextScene(GameStateManager::MAIN_MENU);
		return;
	}

	curSplashTimer -= _dt;

	
	if (curSplashTimer > maxSplashTimer/2) {
		logo.opacity = Lerp(0.f, 1.f, (maxSplashTimer - curSplashTimer) / (maxSplashTimer / 2));
	}
	else {
		logo.opacity = Lerp(1.f, 0.f, (maxSplashTimer / 2 - curSplashTimer) / (maxSplashTimer / 2));
	}
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
	logo.Draw();
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
	logo.FreeTexture();
}
