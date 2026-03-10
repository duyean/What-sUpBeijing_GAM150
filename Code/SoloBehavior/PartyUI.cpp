#include "PartyUI.hpp"
#include "../Combat/BattleManager/BattleManager.hpp"

void PartyUI::awake()
{

}

void PartyUI::init()
{
	battleManager = EntityManager::getInstance().findByComponentGLOBAL<BattleManager>()->getComponent<BattleManager>();
}

void PartyUI::update()
{
	if (battleManager->InBattle())
	{
		auto party = battleManager->GetPlayerParty();
		for (int i = 0; i < party.size(); ++i)
		{
			MeshGen::getInstance().DrawBoxTexture(iconPositions[i].x, iconPositions[i].y, 100, 100, Color(255, 255, 255, 255), 0, party[i]->characterIconTexture.c_str());
			//MeshGen::getInstance().DrawBox(iconPositions[i], { 100, 100 }, Color(255, 255, 255, 255), 0);
		}
	}
}

void PartyUI::fixedUpdate()
{

}

void PartyUI::destroy()
{

}