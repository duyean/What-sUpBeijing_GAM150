/******************************************************************************/
/*!
\file   TextMesh.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Text Mesh
*/
/******************************************************************************/

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
\brief This function reads the current text and applies any newline to it 
\param _text
text to be read
*************************************************************************/
	void ReadText(const char* _text);
	bool textChanged = false;
public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
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
	

	TextMesh();
/*!***********************************************************************
\brief Constructor for TextMesh Class
\param _pos
pos of the text mesh
\param _size
size of the text mesh
\param _text
text of the text mesh
\param _allign
Allignment of the text
*************************************************************************/
	TextMesh(AEVec2 _pos, float _size, const char* _text, TextAlignment _allign = TextAlignment::LEFT);
/*!***********************************************************************
\brief Constructor overload for TextMesh Class
\param _pos
pos of the text mesh
\param _size
size of the text mesh
\param _text
text of the text mesh
\param _color
color of the text mesh
\param _allign
Allignment of the text
*************************************************************************/
	TextMesh(AEVec2 _pos, float _size, const char* _text, Color _color, TextAlignment _allign = TextAlignment::LEFT);
	~TextMesh(){}

};

#endif