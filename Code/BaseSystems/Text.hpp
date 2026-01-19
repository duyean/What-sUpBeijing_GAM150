#pragma once
#include "AEEngine.h"
#include "../BaseSystems/Mesh/ColorClass.hpp"
#include"../BaseSystems/Prefabs/SingletonPattern.hpp"

class Text : public SingletonPattern<Text>
{
	friend SingletonPattern<Text>;
public:
	enum Fonts {
		CINZEL,
		NUM_FONTS
	};

private:
	s8 fonts[NUM_FONTS];

public:
	void Draw(Fonts font, const char* text, AEVec2 pos, float scale, Color4 color);
	Text();
	~Text();

	/*!
	@brief Loads all text assets
	@param void
	@return void
	*//*______________________________________________________________*/
	void Init();
	/*!
	@brief Frees all text assets
	@param void
	@return void
	*//*______________________________________________________________*/
	void Exit();
};