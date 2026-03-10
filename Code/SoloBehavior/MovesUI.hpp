#pragma once
#include "../Engine_WZBJ_Pak.hpp"

class BattleManager;

class MovesUI : public SoloBehavior
{
private:
	BattleManager* battleManager = nullptr;
	const AEVec2 movesUIPanelPos = {-AEGfxGetWindowWidth() * 0.90f * 0.5f, -AEGfxGetWindowHeight() * 0.6f * 0.5f};
public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};