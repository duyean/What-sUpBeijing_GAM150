#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/Combat/Move.hpp"
#include "../UI_WZBJ_Pak.hpp"

class BattleManager;

class MovesUI : public SoloBehavior
{
private:
	BattleManager* battleManager = nullptr;
	Button* moveButton1 = nullptr;
	Button* moveButton2 = nullptr;
	Button* moveButton3 = nullptr;
	Button* moveButton4 = nullptr;
	const AEVec2 movesUIPanelPos = {-AEGfxGetWindowWidth() * 0.90f * 0.5f, -AEGfxGetWindowHeight() * 0.6f * 0.5f};

	void UseCurrMove(MOVE_SLOT ms, Character* ch);
public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};