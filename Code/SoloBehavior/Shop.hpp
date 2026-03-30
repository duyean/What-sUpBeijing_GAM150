/*!************************************************************************
* \file Shop.hpp
* \author Tai Yang Tat Bryson
* \par DP email: t.yangtatbryson\@digipen.edu
* \par Course: CSD1451-b
* \brief
*   This file implements the Shop system as a SoloBehavior object
**************************************************************************/

#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/DecisionBoxManager.hpp"
#include "../Code/Combat/Blessing/Blessing.hpp"
#include "../Code/SoloBehavior/ShopBlessing.hpp"

#include <vector>

/*!***********************************************************************
* \class Shop
* \brief
*  The SoloBehavior object for Shop
*************************************************************************/
class Shop : public SoloBehavior
{
public:
	/*!***********************************************************************
	* \brief
	*  Adds an Entity into a vector with all display components for the Shop
	* \param[in] ent
	*  The entity to add into the vector
	* \return
	*  void
	*************************************************************************/
	void AddDisplayEntity(Entity* ent);
	/*!***********************************************************************
	* \brief
	*  Selects a shop item
	* \param[in] id
	*  The id of the shop item to choose
	* \return
	*  void
	*************************************************************************/
	void ChooseSelection(int id);
	/*!***********************************************************************
	* \brief
	*  Setter for the buy button Entity UI
	* \param[in] ent
	*  The buy button
	* \return
	*  void
	*************************************************************************/
	void SetBuyButton(Entity* ent);
	/*!***********************************************************************
	* \brief
	*  Logic to buy an item in the shop
	* \return
	*  void
	*************************************************************************/
	void PurchaseSelection();
	/*!***********************************************************************
	* \brief
	*  Adds a ShopBlessing component into a list of all blessings in the shop
	* \param[in] b
	*  The blessing to add
	* \param[in] id
	*  Which id to set the blessing to
	* \return
	*  void
	*************************************************************************/
	void AddShopBlessings(ShopBlessing* b, int id);
	/*!***********************************************************************
	* \brief
	*  Sets all Shop UI to inactive
	* \return
	*  void
	*************************************************************************/
	void CloseShopUI();
	/*!***********************************************************************
	* \brief
	*  Set Player Entity
	* \param[in] p
	*  The player Entity
	* \return
	*  void
	*************************************************************************/
	void SetPlayer(Entity* p);
	/*!***********************************************************************
	* \brief
	*  Set the Currency Entity
	* \param[in] c
	*  The currency Entity
	* \return
	*  void
	*************************************************************************/
	void SetCurrency(Entity* c);
	/*!***********************************************************************
	* \brief
	*  Set the Cost Entity
	* \param[in] c
	*  The cost Entity
	* \return
	*  void
	*************************************************************************/
	void SetCost(Entity* c);

	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's awake() function
	* \return
	*  void
	*************************************************************************/
	void awake() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's init() function
	* \return
	*  void
	*************************************************************************/
	void init() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's update() function
	* \return
	*  void
	*************************************************************************/
	void update() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's fixedUpdate() function
	* \return
	*  void
	*************************************************************************/
	void fixedUpdate() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's destroy() function
	* \return
	*  void
	*************************************************************************/
	void destroy() override;

	/*!***********************************************************************
	* \brief
	*  Default constructor
	*************************************************************************/
	Shop() {}
	/*!***********************************************************************
	* \brief
	*  Default destructor
	*************************************************************************/
	~Shop();
private:
	// Boolean to show the shop UI
	bool canShow = false;
	// Vector of all shop UI Entities
	std::vector<Entity*> display{};
	// Map of all shop items
	std::map<int, bool> selection{};
	// The current shop item selected
	int currSelection{ -1 };
	// The buy button entity
	Entity* buyButton = nullptr;
	// The player entity
	Entity* player = nullptr;
	// The ShopBlessings in the shop
	ShopBlessing* shopBlessings[4]{};
	// The currency entity
	Entity* currency = nullptr;
	// How much currency you have as a string
	std::string curStr{};
	// The cost entity
	Entity* cost = nullptr;
	// How much an item costs as a string
	std::string costStr{};

	// Timer for the currency flash
	float currencyFlashTimer{};
	// Timer max for the currency flash
	float currencyFlashTimerMax{};
	
	/*!***********************************************************************
	* \brief
	*  Logic for BoxCollider2D onHit
	* \param[in] other
	*  The other collider
	* \return
	*  void
	*************************************************************************/
	void onHit(BoxCollider2D* other);
	/*!***********************************************************************
	* \brief
	*  Logic for BoxCollider2D onStay
	* \param[in] other
	*  The other collider
	* \return
	*  void
	*************************************************************************/
	void onStay(BoxCollider2D* other);
	/*!***********************************************************************
	* \brief
	*  Logic for BoxCollider2D onExit
	* \param[in] other
	*  The other collider
	* \return
	*  void
	*************************************************************************/
	void onExit(BoxCollider2D* other);
};

