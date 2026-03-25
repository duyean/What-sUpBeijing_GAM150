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

	bool isDisplaying = false;
public:
	void ShowSettings(bool canShow);
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	bool IsDisplaying() const { return isDisplaying; }
	void AddPrevDisplayEntity(Entity* en);
	SettingsScreen() : isDisplaying(false){}
	~SettingsScreen() {};
};