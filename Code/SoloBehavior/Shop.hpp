#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/DecisionBoxManager.hpp"

class Shop : public SoloBehavior
{
public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	Shop();
	Shop(DecisionBoxManager* box);
	~Shop();
private:
	DecisionBoxManager* decisionBox{ nullptr };

	void onHit(BoxCollider2D* other);
	void onStay(BoxCollider2D* other);
	void onExit(BoxCollider2D* other);
};

