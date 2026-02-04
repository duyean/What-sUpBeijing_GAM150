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
#include "../BaseSystems_WZBJ_Pak.hpp"
#include "../SceneHandler_WZBJ_Pak.hpp"

#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"
#include "../SoloBehavior/Player.hpp"

class GameScene : public GameState
{
private:
	EntityManager* enSystem = nullptr;
	MeshGen* meshSystem = nullptr;
public:
	GameScene();
	~GameScene();

	/*!
	@brief Initialize Splash Screen variables
	@param void
	@return void
	*//*______________________________________________________________*/
	void Load() override;
	/*!
	* 
	/*!
	@brief Clears splash screen variables
	@param void
	@return void
	*//*______________________________________________________________*/
	void Unload() override;
};

