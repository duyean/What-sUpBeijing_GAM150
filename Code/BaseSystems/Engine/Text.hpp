#pragma once
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

	Text(float x, float y, float s, Color c, std::string t, std::string f, TextAlignment a, int d) : Xpos(x), Ypos(y), scale(s), color(c), text(t), fileName(f), align(a) { this->drawOrder = d; }
	~Text(){}

};