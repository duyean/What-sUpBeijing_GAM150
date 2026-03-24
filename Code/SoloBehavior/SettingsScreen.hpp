#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"

class SettingsScreen : public SoloBehavior
{
private:	
	EntityManager* enSystem = nullptr;
	std::vector<Entity*> prevDisplay;

	Slider* bgm_sl = nullptr;
	Slider* sfx_sl = nullptr;

	bool isDisplaying;
public:
	void ShowSettings(bool canShow);
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	bool IsDisplaying() const { return isDisplaying; }

	SettingsScreen(std::vector<Entity*> const& _prevDisplay) : prevDisplay(_prevDisplay) {}
	~SettingsScreen() {};
};