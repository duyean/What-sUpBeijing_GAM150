#include "MovesUI.hpp"
#include "../Combat/BattleManager/BattleManager.hpp"

void MovesUI::awake()
{

}

void MovesUI::init()
{
	battleManager = EntityManager::getInstance().findByComponentGLOBAL<BattleManager>()->getComponent<BattleManager>();
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
		AEVec2 scale = { 800, 300 };
		//Background UI
		MeshGen::getInstance().DrawBox(movesUIPanelPos.x, movesUIPanelPos.y, scale.x, scale.y, Color(122, 122, 122, 128), 0);

		//You can draw your buttons here
		//Remember DrawFont uses normalized coordinates

		//@t.qianyi
		//To get a move data
		//Move::moveDatabase[battleManager->GetActiveUnit()->GetMoveList().at(MOVE_SLOT_1)].description;
		//Replace MOVE_SLOT_1 with MOVE_SLOT_2/3/4 for other moves, check if the move exist first
		//Replace .description with .name and other fields for the OnHover tooltip
	}
}

void MovesUI::fixedUpdate()
{

}

void MovesUI::destroy()
{

}