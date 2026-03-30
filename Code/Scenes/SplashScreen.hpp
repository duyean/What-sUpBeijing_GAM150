/******************************************************************************/
/*!
\file   SplashScreen.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Splash Screen
*/
/******************************************************************************/
#pragma once
#include "../BaseSystems_WZBJ_Pak.hpp"
#include "../SceneHandler_WZBJ_Pak.hpp"

#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"
#include "../SoloBehavior/SplashLogo.hpp"

class SplashScreen : public GameState
{
private:
	//CP_Image logo;
	EntityManager* enSystem = nullptr;
	MeshGen* meshSystem = nullptr;
public:
	SplashScreen();
	~SplashScreen();

/*!***********************************************************************
\brief This function loads all Splash Screen objects.
*************************************************************************/
	void Load() override;
/*!***********************************************************************
\brief This function unloads all Splash Screen objects.
*************************************************************************/
	void Unload() override;
};

