#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/TransitionScreen.hpp"

class PauseMenu : public SoloBehavior
{
private:
	void ResumeGame();
	void QuitGame();
	void QuitToMainMenu();

	TransitionScreen* ts_comp = nullptr;
	EntityManager* enSystem = nullptr;
public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	PauseMenu() {}
	~PauseMenu() {}
};