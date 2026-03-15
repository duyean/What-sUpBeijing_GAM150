#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/DecisionBoxManager.hpp"
#include "../Code/Combat/Blessing/Blessing.hpp"

#include <vector>

class Shop : public SoloBehavior
{
public:
	void AddDisplayEntity(Entity* ent);
	void ChooseSelection(int id);

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	Shop();
	~Shop();
private:
	std::vector<Entity*> display{};
	std::map<int, bool> selection{};
	
	void onHit(BoxCollider2D* other);
	void onStay(BoxCollider2D* other);
	void onExit(BoxCollider2D* other);
};

