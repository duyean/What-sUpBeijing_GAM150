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
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
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

	TextBox();
	TextBox(const char* _text, float _size, TextBoxVAllign _allign_v = TextBoxVAllign::TOP, TextBoxHAllign _allign_h = TextBoxHAllign::LEFT);
	~TextBox(){}
};

#endif