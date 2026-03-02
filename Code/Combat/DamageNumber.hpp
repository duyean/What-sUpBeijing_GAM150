#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "Globals/Globals.hpp"

class DamageNumbers : public SoloBehavior
{
	EntityManager* enSystem;
	bool activate;
	
public:
	static Color GetElementColor(Game::WUXING_ELEMENT);
	Color textColor;
	float size;
	std::string text;
	float lifetime;

	DamageNumbers();
	inline void Activate() { activate = true; }
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};