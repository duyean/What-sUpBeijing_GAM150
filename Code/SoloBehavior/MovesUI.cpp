#include "MovesUI.hpp"
#include "../Combat/BattleManager/BattleManager.hpp"

void MovesUI::UseCurrMove(MOVE_SLOT ms, Character* ch)
{
	if (!ch->IsEndingTurn())
	{
		ch->UseMove(ms, battleManager->GetlastTargetedUnit());
	}
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

	if (battleManager->GetActiveUnit()->GetFaction() == Game::PLAYER)
	{
		moveButton1->SetOnClick([this]() {UseCurrMove(MOVE_SLOT_1, battleManager->GetActiveUnit()); });
		moveButton2->SetOnClick([this]() {UseCurrMove(MOVE_SLOT_2, battleManager->GetActiveUnit()); });
		moveButton3->SetOnClick([this]() {UseCurrMove(MOVE_SLOT_3, battleManager->GetActiveUnit()); });
		moveButton4->SetOnClick([this]() {UseCurrMove(MOVE_SLOT_4, battleManager->GetActiveUnit()); });
	}
}

void MovesUI::update()
{
	if (!battleManager->InBattle())
	{
		return;
	}

	if (battleManager->GetActiveUnit()->GetFaction() == Game::PLAYER)
	{
		tb1->text = (Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_1)].name).c_str();
		tb2->text = (Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_2)].name).c_str();
		tb3->text = (Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_3)].name).c_str();
		tb4->text = (Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_4)].name).c_str();

	}
}

void MovesUI::fixedUpdate()
{

}

void MovesUI::destroy()
{

}