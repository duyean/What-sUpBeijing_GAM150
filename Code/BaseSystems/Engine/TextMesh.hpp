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


class TextMesh : public SoloBehavior
{
private:
		
public:

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	Transform2D* parent = nullptr;
	Color color;
	AEVec2 pos;
	TextAlignment allign;
	double size;
	const char* text;
	const char* font;

	TextMesh();
	TextMesh(AEVec2 _pos, double _size, const char* _text, TextAlignment _allign = TextAlignment::LEFT);
	TextMesh(AEVec2 _pos, double _size, const char* _text, Color _color, TextAlignment _allign = TextAlignment::LEFT);
	~TextMesh(){}

};

#endif