#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/TransitionScreen.hpp"
#include "../Code/SoloBehavior/SettingsScreen.hpp"

class PauseMenu : public SoloBehavior
{
private:
	void ResumeGame();
	void QuitGame();
	void QuitToMainMenu();
	std::vector<Entity*> prevDisplay;

	TransitionScreen* ts_comp = nullptr;
	EntityManager* enSystem = nullptr;
	SettingsScreen* settings = nullptr;
	bool canDisplay = true;
public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
	void AddPrevDisplayEntity(Entity* en);

	PauseMenu() {}
	~PauseMenu() {}
};