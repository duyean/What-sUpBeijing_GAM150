#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/DecisionBoxManager.hpp"

class PartyManagerObject : public SoloBehavior
{
public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	PartyManagerObject();
	PartyManagerObject(DecisionBoxManager* box);
	~PartyManagerObject();
private:
	DecisionBoxManager* decisionBox{ nullptr };

	void onHit(BoxCollider2D* other);
	void onStay(BoxCollider2D* other);
	void onExit(BoxCollider2D* other);
};

