/******************************************************************************/
/*!
\file   BaseCamp.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Base Camp Scene
*/
/******************************************************************************/
#pragma once
#include "../BaseSystems_WZBJ_Pak.hpp"
#include "../SceneHandler_WZBJ_Pak.hpp"

#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"
#include "../SoloBehavior/Player.hpp"
#include "../Map/MapClass.hpp"
#include "../SoloBehavior/TransitionScreen.hpp"
#include "../SoloBehavior/SceneEdge.hpp"
#include "../Code/Combat/Blessing/Blessing.hpp"

class BaseCamp : public GameState
{
private:
	EntityManager* enSystem = nullptr;
	MeshGen* meshSystem = nullptr;
	//Map* map = nullptr;
public:
	BaseCamp();
	~BaseCamp();

/*!***********************************************************************
\brief This function loads all the Base Camp scene objects.
*************************************************************************/
	void Load() override;
/*!***********************************************************************
\brief This function unloads all Base Camp scene objects.
*************************************************************************/
	void Unload() override;
};

