#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"

class CreditsScreen : public SoloBehavior
{
private:	
	EntityManager* enSystem = nullptr;
	std::vector<Entity*> prevDisplay;

	bool isDisplaying = false;
public:
	void ShowCredits(bool canShow);
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	bool IsDisplaying() const { return isDisplaying; }
	void AddPrevDisplayEntity(Entity* en);
	CreditsScreen() : isDisplaying(false){}
	~CreditsScreen() {};
};