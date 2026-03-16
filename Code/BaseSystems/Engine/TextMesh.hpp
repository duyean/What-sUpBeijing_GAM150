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
	TextMesh(AEVec2 _pos, float _size, const char* _text, TextAlignment _allign = TextAlignment::LEFT);
	TextMesh(AEVec2 _pos, float _size, const char* _text, Color _color, TextAlignment _allign = TextAlignment::LEFT);
	~TextMesh(){}

};

#endif