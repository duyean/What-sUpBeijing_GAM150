/*!
@file Text.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the Text class which stores all data needed to render
a string of text through the MeshGen rendering system
*//*______________________________________________________________________*/
#pragma once
#pragma once
#ifndef _Text_

#include "AEEngine.h"
#include "ECS.hpp"
#include "Colors.hpp"
#include "OOP.hpp"
#include "Transform2D.hpp"
#include "Renderable.hpp"
#include <string>
enum struct TextAlignment
{
	LEFT,
	CENTER,
	RIGHT
};

class Text : public IRenderable
{
public:

	float Xpos;
	float Ypos;
	float scale;
	Color color;
	std::string text;
	std::string fileName;
	TextAlignment align = TextAlignment::LEFT;

	/*!***********************************************************************
	* \brief
	* Constructs a Text object with all rendering parameters
	* \param[in] x
	* The world X position of the text
	* \param[in] y
	* The world Y position of the text
	* \param[in] s
	* The scale of the rendered text
	* \param[in] c
	* The colour to render the text with
	* \param[in] t
	* The string content to display
	* \param[in] f
	* The key name of the cached font to use
	* \param[in] a
	* The text alignment (LEFT, CENTER, RIGHT)
	* \param[in] d
	* The draw order depth layer
	*************************************************************************/
	Text(float x, float y, float s, Color c, std::string t, std::string f, TextAlignment a, int d) : Xpos(x), Ypos(y), scale(s), color(c), text(t), fileName(f), align(a) { this->drawOrder = d; }
	~Text(){}

};

#endif
