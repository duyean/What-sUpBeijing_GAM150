/******************************************************************************/
/*!
\file   LevelScene.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Level Scene
*/
/******************************************************************************/
#pragma once
#include "../BaseSystems_WZBJ_Pak.hpp"
#include "../SceneHandler_WZBJ_Pak.hpp"
#include "../Maps_WZBJ_Pak.hpp"

#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"

class LevelScene : public GameState
{
private:
	//Pointer to the Entity System
	EntityManager* enSystem = nullptr;
	//Pointer to the Mesh Gen System
	MeshGen* meshSystem = nullptr;
	//Navigation Data
	NavigationData map { };
public:
	LevelScene();
	~LevelScene();

/*!***********************************************************************
\brief This function loads all the Level Scene objects
*************************************************************************/
	void Load() override;
/*!***********************************************************************
\brief This function unloads all Level Scene objects.
*************************************************************************/
	void Unload() override;
};

