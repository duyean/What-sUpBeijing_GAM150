/******************************************************************************/
/*!
\file   Button.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Buttons
*/
/******************************************************************************/

#pragma once
#ifndef _BoxCollider2D_
#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "UIElement.hpp"



class Button : public UIElement, public IPointerTriggered
{
private:
	Mesh* buttonMesh;
	void OnPointerTriggered(const PointerEventData& event) override;
	void OnHover() override;
	void OnHoverExit() override;

	Color normal_color;
	Color highlighted_color;
	Color pressed_color;
	Color disabled_color;
public:
	using Callback = std::function<void()>;

	/*!***********************************************************************
	* \brief
	*  This function sets the Function Callback for this button when clicked
	* \param[in] cb
	*  The function to run when this button is clicked
	* \return
	*  void
	*************************************************************************/
	void SetOnClick(Callback cb)
	{
		//onClick = std::move(cb);
		onClick = cb;
	}

	/*!***********************************************************************
	* \brief
	*  This function sets the Function Callback for this button when hovered over
	* \param[in] cb
	*  The function to run when this button is hovered over
	* \return
	*  void
	*************************************************************************/
	void SetOnHover(Callback cb)
	{
		onHover = cb;
	}
	
	/*!***********************************************************************
	* \brief
	*  This function sets the Function Callback for this button when out of hover
	* \param[in] cb
	*  The function to run when this button is clicked when exiting hover
	* \return
	*  void
	*************************************************************************/
	void SetOnHoverExit(Callback cb)
	{
		onHoverExit = cb;
	}

	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's awake() function
	* \return
	*  void
	*************************************************************************/
	void awake() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's init() function
	* \return
	*  void
	*************************************************************************/
	void init() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's update() function
	* \return
	*  void
	*************************************************************************/
	void update() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's fixedUpdate() function
	* \return
	*  void
	*************************************************************************/
	void fixedUpdate() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's destroy() function
	* \return
	*  void
	*************************************************************************/
	void destroy() override;

	/*!***********************************************************************
	* \brief
	*  This function sets the base color of the button
	* \param[in] color
	*  The color of the button
	* \return
	*  void
	*************************************************************************/
	void SetNormalColor(Color color);
	/*!***********************************************************************
	* \brief
	*  This function sets the color of the button when highlighted
	* \param[in] color
	*  The color of the button when highlighted
	* \return
	*  void
	*************************************************************************/
	void SetHighlightedColor(Color color);
	/*!***********************************************************************
	* \brief
	*  This function sets the color of the button when pressed
	* \param[in] color
	*  The color of the button when pressed
	* \return
	*  void
	*************************************************************************/
	void SetPressedColor(Color color);
	/*!***********************************************************************
	* \brief
	*  This function sets the color of the button when disabled
	* \param[in] color
	*  The color of the button when disabled
	* \return
	*  void
	*************************************************************************/
	void SetDisabledColor(Color color);

	/*!***********************************************************************
	* \brief
	*  Default constructor
	*************************************************************************/
	Button() {
		enabled = true;
		buttonMesh = nullptr;
		normal_color = {255,255,255,1 };
		highlighted_color = { 255,255,255,1 };
		pressed_color = { 200,200,200,1 };
		disabled_color = { 200,200,200, 0.5 };
	}
	/*!***********************************************************************
	* \brief
	*  Default destructor
	*************************************************************************/
	~Button(){}

private:
	Callback onClick;
	Callback onHover;
	Callback onHoverExit;
};


#endif