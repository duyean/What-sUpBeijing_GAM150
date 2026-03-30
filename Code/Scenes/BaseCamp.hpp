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
/*!***********************************************************************
\brief Displays the selected blessing
\param[in] nameStr 
The name of the blessing selected
\param[in] typeDesc
Description of the blessing
\param[in] longDescStr
Long description of the blessing
\param[in] shopId
Id of the selected blessing item
*************************************************************************/
	void DisplayBlessing(std::string const& nameStr, std::string const& typeDesc, std::string const& longDescStr, int shopId);
/*!***********************************************************************
\brief Purchases the current shop item
*************************************************************************/
	void Purchase();
/*!***********************************************************************
\brief Closes the shop screen
*************************************************************************/
	void CloseShop();
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

