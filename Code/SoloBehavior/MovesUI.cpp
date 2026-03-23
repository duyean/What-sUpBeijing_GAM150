#include "MovesUI.hpp"
#include "../Combat/BattleManager/BattleManager.hpp"
#include "../BaseSystems/Engine/EventSystem.hpp"

void MovesUI::UseCurrMove(MOVE_SLOT ms, Character* ch)
{
	if (!ch->IsEndingTurn())
	{
		bool isAOE = Move::moveDatabase[ch->GetMoveList().at(ms)].targetGroup == Game::MOVE_TARGET_GROUP::AOE_OPPOSITE;
		if (isAOE)
		{
			ch->UseMove(ms, battleManager->GetAllEnemies());
		}
		else
		{
			ch->UseMove(ms, battleManager->GetlastTargetedUnit());
		}
	}
}

void MovesUI::DisplayToolTip(MOVE_SLOT ms)
{
	canDisplay = true;
	currMoveSlot = ms;
}

void MovesUI::HideToolTip()
{
	canDisplay = false;
}

void MovesUI::awake()
{
	
}

void MovesUI::init()
{
	battleManager = EntityManager::getInstance().findByComponentGLOBAL<BattleManager>()->getComponent<BattleManager>();
	moveButton1 = EntityManager::getInstance().FindByNameGLOBAL("MOVEBUTTON1")->getComponent<Button>();
	moveButton2 = EntityManager::getInstance().FindByNameGLOBAL("MOVEBUTTON2")->getComponent<Button>();
	moveButton3 = EntityManager::getInstance().FindByNameGLOBAL("MOVEBUTTON3")->getComponent<Button>();
	moveButton4 = EntityManager::getInstance().FindByNameGLOBAL("MOVEBUTTON4")->getComponent<Button>();

	tb1 = moveButton1->entity->getComponent<TextBox>();
	tb2 = moveButton2->entity->getComponent<TextBox>();
	tb3 = moveButton3->entity->getComponent<TextBox>();
	tb4 = moveButton4->entity->getComponent<TextBox>();

	tooltip = EntityManager::getInstance().FindByNameGLOBAL("ToolTipUI");
	tooltip->isActive = false;

	currentCh = battleManager->GetActiveUnit();

	if (battleManager->GetActiveUnit()->GetFaction() == Game::PLAYER)
	{
		moveButton1->SetOnClick([this]() {UseCurrMove(MOVE_SLOT_1, battleManager->GetActiveUnit()); });
		moveButton2->SetOnClick([this]() {UseCurrMove(MOVE_SLOT_2, battleManager->GetActiveUnit()); });
		moveButton3->SetOnClick([this]() {UseCurrMove(MOVE_SLOT_3, battleManager->GetActiveUnit()); });
		moveButton4->SetOnClick([this]() {UseCurrMove(MOVE_SLOT_4, battleManager->GetActiveUnit()); });

		moveButton1->SetOnHover([this]() { DisplayToolTip(MOVE_SLOT_1); });
		moveButton2->SetOnHover([this]() { DisplayToolTip(MOVE_SLOT_2); });
		moveButton3->SetOnHover([this]() { DisplayToolTip(MOVE_SLOT_3); });
		moveButton4->SetOnHover([this]() { DisplayToolTip(MOVE_SLOT_4); });

		moveButton1->SetOnHoverExit([this]() { HideToolTip(); });
		moveButton2->SetOnHoverExit([this]() { HideToolTip(); });
		moveButton3->SetOnHoverExit([this]() { HideToolTip(); });
		moveButton4->SetOnHoverExit([this]() { HideToolTip(); });
	}
}

void MovesUI::update()
{
	if (!battleManager->InBattle())
	{
		return;
	}
	bool endingTurn = battleManager->GetActiveUnit()->IsEndingTurn();
	
	moveButton1->entity->isActive = !endingTurn;
	moveButton2->entity->isActive = !endingTurn;
	moveButton3->entity->isActive = !endingTurn;
	moveButton4->entity->isActive = !endingTurn;

	if (canDisplay && !endingTurn)
	{
		tooltip->getComponent<TextBox>()->text =
			(Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(currMoveSlot)].brief).c_str();
		tooltip->isActive = true;
	}
	else
	{
		tooltip->isActive = false;
		canDisplay = false;
	}

	if (battleManager->GetActiveUnit()->GetFaction() == Game::PLAYER)
	{
		tb1->text = (Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_1)].name).c_str();
		tb2->text = (Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_2)].name).c_str();
		tb3->text = (Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_3)].name).c_str();
		tb4->text = (Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_4)].name).c_str();
	}
	AEVec2 ttbox_scale = tb1->entity->transform->getScale();
	AEVec2 mouseCoord = { EventSystem::getInstance().eventData.x , EventSystem::getInstance().eventData.y };
	tooltip->transform->setPosition({ mouseCoord.x + (ttbox_scale.x / 2), mouseCoord.y + (ttbox_scale.y) });
}

void MovesUI::fixedUpdate()
{

}

void MovesUI::destroy()
{

}