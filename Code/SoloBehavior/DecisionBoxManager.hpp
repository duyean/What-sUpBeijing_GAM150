#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/Button.hpp"

class DecisionBoxManager : public SoloBehavior
{
public:
	void ToggleDecisionBox(bool toggle);
	Button* leftButton = nullptr, *rightButton = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};

