#pragma once
#include "../UI_WZBJ_Pak.hpp"
class BattleManager;

class BattleStatUI : public SoloBehavior
{
	public:
	BattleStatUI();
	void ToggleRender();
	void SetBattleManager(BattleManager*);

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	private:
	bool render;
	BattleManager* battleManager;
	
};