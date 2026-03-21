#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/DecisionBoxManager.hpp"
#include "../Code/Combat/Blessing/Blessing.hpp"
#include "../Code/SoloBehavior/ShopBlessing.hpp"

#include <vector>

class Shop : public SoloBehavior
{
public:
	void AddDisplayEntity(Entity* ent);
	void ChooseSelection(int id);
	void SetBuyButton(Entity* ent);
	void PurchaseSelection();
	void AddShopBlessings(ShopBlessing* b, int id);
	void CloseShopUI();
	void SetPlayer(Entity* p);

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
	int currSelection{ -1 };
	Entity* buyButton;
	Entity* player;
	ShopBlessing* shopBlessings[4];
	
	void onHit(BoxCollider2D* other);
	void onStay(BoxCollider2D* other);
	void onExit(BoxCollider2D* other);
};

