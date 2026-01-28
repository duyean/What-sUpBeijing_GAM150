#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Combat/Globals/Globals.hpp"


class CombatUIManager : public SoloBehavior
{
public:
	static CombatUIManager* instance;
	void CreateDamageNumber(AEVec2 position, Game::DamageInfo info);

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};