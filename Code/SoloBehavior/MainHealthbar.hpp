#pragma once
#include "AEEngine.h"
#include "../BaseSystems/Engine/OOP.hpp"
#include "../BaseSystems/Engine/EntityManager.hpp"
#include "../Code/Combat/BattleManager/BattleManager.hpp"

class MainHealthbar : public SoloBehavior
{
private:
	const AEVec2 currentTurnTextPos = {-0.9f, 0.875f};
	const AEVec2 activeUnitHPPos = { -0.8f * AEGfxGetWindowWidth() / 2, 0.9f * AEGfxGetWindowHeight() / 2};
public:
	EntityManager* enSystem = nullptr;
	BattleManager* battleManager = nullptr;
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	MainHealthbar() = default;
	~MainHealthbar() = default;
};

