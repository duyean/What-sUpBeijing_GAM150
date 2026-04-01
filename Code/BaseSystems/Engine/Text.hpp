/******************************************************************************/
/*!
\file   Text.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Text class
*/
/******************************************************************************/
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
\brief Constructor for Text Class
\param x
x pos
\param y
y pos
\param s
text size
\param c
Color of the text
\param t 
The text to print
\param f
The filename of the font
\param a
Type of allignment to apply to the text
\param d
Draw order for the text
*************************************************************************/
	Text(float x, float y, float s, Color c, std::string t, std::string f, TextAlignment a, int d) : Xpos(x), Ypos(y), scale(s), color(c), text(t), fileName(f), align(a) { this->drawOrder = d; }
	~Text(){}

};

#endif
