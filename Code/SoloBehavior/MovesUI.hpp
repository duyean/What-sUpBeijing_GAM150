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

	TextBox* tb1 = nullptr;
	TextBox* tb2 = nullptr;
	TextBox* tb3 = nullptr;
	TextBox* tb4 = nullptr;

	Entity* tooltip = nullptr;
	bool canDisplay = false;

	Character* currentCh = nullptr;
	MOVE_SLOT currMoveSlot;

	void UseCurrMove(MOVE_SLOT ms, Character* ch);
	void DisplayToolTip(MOVE_SLOT ms);
	void HideToolTip();
public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};