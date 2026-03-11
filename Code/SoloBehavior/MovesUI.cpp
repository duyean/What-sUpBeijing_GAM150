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
		//Render UI
		//AEVec2 scale = { 800, 300 };
		//Background UI
		//MeshGen::getInstance().DrawBox(movesUIPanelPos.x, movesUIPanelPos.y, scale.x, scale.y, Color(122, 122, 122, 128), 0);

		//You can draw your buttons here
		//Remember DrawFont uses normalized coordinates

		//@t.qianyi
		//To get a move data
		//Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_1)].description;
		//Replace MOVE_SLOT_1 with MOVE_SLOT_2/3/4 for other moves, check if the move exist first
		//Replace .description with .name and other fields for the OnHover tooltip

		AEVec2 normalised = { this->entity->transform->getPosition().x / 800.f, this->entity->transform->getPosition().y / 450.f };
		MeshGen::getInstance().DrawFont(normalised.x - 0.87f, normalised.y - 0.46f, 0.5, Color{ 255,255,255,1 }, (Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_1)].name).c_str(), "liberi", TextAlignment::LEFT, 700);
		MeshGen::getInstance().DrawFont(normalised.x - 0.87f, normalised.y - 0.60f, 0.5, Color{ 255,255,255,1 }, (Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_2)].name).c_str(), "liberi", TextAlignment::LEFT, 700);
		MeshGen::getInstance().DrawFont(normalised.x - 0.87f, normalised.y - 0.73f, 0.5, Color{ 255,255,255,1 }, (Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_3)].name).c_str(), "liberi", TextAlignment::LEFT, 700);
		MeshGen::getInstance().DrawFont(normalised.x - 0.87f, normalised.y - 0.86f, 0.5, Color{ 255,255,255,1 }, (Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_4)].name).c_str(), "liberi", TextAlignment::LEFT, 700);
	}
}

void MovesUI::fixedUpdate()
{

}

void MovesUI::destroy()
{

}