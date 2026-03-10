#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/DecisionBoxManager.hpp"

#include <vector>

class Shop : public SoloBehavior
{
public:
	void AddDisplayEntity(Entity* ent);

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	Shop();
	~Shop();
private:
	std::vector<Entity*> display{};

	void onHit(BoxCollider2D* other);
	void onStay(BoxCollider2D* other);
	void onExit(BoxCollider2D* other);
};

