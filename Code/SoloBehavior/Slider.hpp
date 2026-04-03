/******************************************************************************/
/*!
\file   Slider.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Slider class
*/
/******************************************************************************/

#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"

class Slider : public SoloBehavior
{
private:

	Entity* slider = nullptr;

	//slider values
	float max_value;
	float& value;
	float changeFactor;

	EntityManager* enSystem = nullptr;
	MeshGen* meSystem = nullptr;

	/*!***********************************************************************
	\brief This function increases the slider's value
	\param val
	value of how much to increase by
	\param max_val
	maximum value 
	*************************************************************************/
	void Increase(float& val, float const& max_val);
	/*!***********************************************************************
	\brief This function decreases the slider's value
	\param val
	value of how much to decrease by
	*************************************************************************/
	void Decrease(float& val);

	std::vector<Entity*>sliderComp;
public:
	
	TextBox* text = nullptr;
	Color slider_color = Color{ 100, 100, 100, 1.f };
	Color background_color = Color{ 200, 200, 200, 1.f };

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	/*!***********************************************************************
	\brief This function makes the slider active or inactive
	\param active
	active status of the slider
	*************************************************************************/
	void SliderSetActive(bool active);

	/*!***********************************************************************
	\brief Default constructor of the Slider
	\param val
	initial value
	\param max_val
	maximum slider value
	\param _changeFactor
	how much to change the value by
	*************************************************************************/
	Slider(float& val, float const& max_val, float _changeFactor) :
		value(val), max_value(max_val), changeFactor(_changeFactor) { }
	~Slider() {}
	
};