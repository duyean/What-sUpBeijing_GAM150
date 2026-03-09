#pragma once
#include "../Engine_WZBJ_Pak.hpp"

class BattleManager;

class PartyUI : public SoloBehavior
{
	const std::vector<AEVec2> iconPositions = { {50, -AEGfxGetWindowHeight() * 0.7f * 0.5f}, {300, -AEGfxGetWindowHeight() * 0.7f * 0.5f}, {550, -AEGfxGetWindowHeight() * 0.7f} };
	BattleManager* battleManager = nullptr;

public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};