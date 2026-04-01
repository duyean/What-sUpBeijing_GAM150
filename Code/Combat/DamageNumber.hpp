/*!
@file DamageNumber.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the interface for a DamageNumber entity.
*//*______________________________________________________________________*/

#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "Globals/Globals.hpp"

class DamageNumbers : public SoloBehavior
{
	//Pointer to entity system
	EntityManager* enSystem;

	//To show whether to start updating the text
	bool activate;
	
public:
	/*!***********************************************************************
	* \brief
	* Static member to get a Color from an ELEMENT
	* \return
	* A color corresponding to the element
	*************************************************************************/
	static Color GetElementColor(Game::WUXING_ELEMENT);
	
	//The color of the text
	Color textColor;

	//The size of the text
	float size;

	//The contents of the text
	std::string text;

	//The remaining lifetime of the text
	float lifetime;

	//Default constructor
	DamageNumbers();

	//Activates the damage number, setting activate to true
	inline void Activate() { activate = true; }

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};