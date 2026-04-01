/*!
@file TextMesh.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the TextMesh component which handles line-wrapped text
rendering in world space, with support for alignment and colour
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

enum class TextLineAllignment
{
	TOP,
	CENTER,
	BOTTOM
};

class TextMesh : public SoloBehavior
{
private:
	std::vector < std::string > lines;

	/*!***********************************************************************
	* \brief
	* Parses the raw text string and splits it into individual lines
	* for rendering
	* \param[in] _text
	* The raw text string to parse
	*************************************************************************/
	void ReadText(const char* _text);
	bool textChanged = false;
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
	* Called every frame, re-renders text lines if the content has changed
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

	Color color;
	AEVec2 pos;
	TextAlignment t_allign;
	TextLineAllignment tl_allign;

	float padding;
	float size;
	int layer;
	const char* text;
	const char* font;
	
	/*!***********************************************************************
	* \brief
	* Default constructor, initialises a TextMesh with default settings
	*************************************************************************/
	TextMesh();

	/*!***********************************************************************
	* \brief
	* Constructs a TextMesh at the given position with the specified size,
	* text content, and alignment
	* \param[in] _pos
	* The world position to render the text at
	* \param[in] _size
	* The scale of the rendered text
	* \param[in] _text
	* The string content to display
	* \param[in] _allign
	* The horizontal text alignment (default: LEFT)
	*************************************************************************/
	TextMesh(AEVec2 _pos, float _size, const char* _text, TextAlignment _allign = TextAlignment::LEFT);

	/*!***********************************************************************
	* \brief
	* Constructs a TextMesh at the given position with explicit colour,
	* size, text content, and alignment
	* \param[in] _pos
	* The world position to render the text at
	* \param[in] _size
	* The scale of the rendered text
	* \param[in] _text
	* The string content to display
	* \param[in] _color
	* The colour to render the text with
	* \param[in] _allign
	* The horizontal text alignment (default: LEFT)
	*************************************************************************/
	TextMesh(AEVec2 _pos, float _size, const char* _text, Color _color, TextAlignment _allign = TextAlignment::LEFT);
	~TextMesh(){}

};

#endif
