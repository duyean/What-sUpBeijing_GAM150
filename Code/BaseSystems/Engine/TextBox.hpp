/*!
@file TextBox.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the TextBox component which renders text within a
bounded box area with configurable vertical and horizontal alignment,
padding, and text size
*//*______________________________________________________________________*/
#pragma once
#ifndef _Text_
#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "ECS.hpp"
#include "Colors.hpp"
#include "OOP.hpp"
#include "Transform2D.hpp"
#include "MeshGen.hpp"
#include "TextMesh.hpp"

enum struct TextBoxVAllign
{
	TOP,
	CENTER,
	BOTTOM
};

enum struct TextBoxHAllign
{
	LEFT,
	CENTER,
	RIGHT
};


class TextBox : public SoloBehavior
{
private:
	TextMesh* textMesh = nullptr;
public:
	/*!***********************************************************************
	* \brief
	* Called once when the component is first created, before init
	*************************************************************************/
	void awake() override;

	/*!***********************************************************************
	* \brief
	* Called once before the first update, used for initialisation
	*************************************************************************/
	void init() override;

	/*!***********************************************************************
	* \brief
	* Called every frame, updates and positions the text mesh
	*************************************************************************/
	void update() override;

	/*!***********************************************************************
	* \brief
	* Called at a fixed timestep, used for physics-based updates
	*************************************************************************/
	void fixedUpdate() override;

	/*!***********************************************************************
	* \brief
	* Called when the component is destroyed, used for cleanup
	*************************************************************************/
	void destroy() override;

	TextBoxVAllign v_allign;
	TextBoxHAllign h_allign;
	TextAlignment text_allign;
	const char* text;

	float text_size;
	float line_padding;
	float padding_h;
	float padding_v;
	int text_layer;

	Color text_color;

	/*!***********************************************************************
	* \brief
	* Default constructor, initialises a TextBox with default settings
	*************************************************************************/
	TextBox();

	/*!***********************************************************************
	* \brief
	* Constructs a TextBox with the given text content, size, and alignment
	* \param[in] _text
	* The string content to display
	* \param[in] _size
	* The scale of the rendered text
	* \param[in] _allign_v
	* The vertical alignment within the box (default: TOP)
	* \param[in] _allign_h
	* The horizontal alignment within the box (default: LEFT)
	*************************************************************************/
	TextBox(const char* _text, float _size, TextBoxVAllign _allign_v = TextBoxVAllign::TOP, TextBoxHAllign _allign_h = TextBoxHAllign::LEFT);
	~TextBox(){}
};

#endif
