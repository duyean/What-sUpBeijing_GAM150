#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "Globals/Globals.hpp"

class DamageNumbers : public SoloBehavior
{
	EntityManager* enSystem;
	
public:
	static Color GetElementColor(Game::WUXING_ELEMENT);
	Color textColor;
	float size;
	std::string text;
	float lifetime;

	DamageNumbers();
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};