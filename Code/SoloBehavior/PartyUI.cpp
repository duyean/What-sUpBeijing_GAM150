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
			float scale = 100;
			if (party[i] == battleManager->GetActiveUnit())
			{
				scale = 150;
			}
			MeshGen::getInstance().DrawBoxTexture(iconPositions[i].x, iconPositions[i].y, scale, scale, Color(255, 255, 255, 255), 0, party[i]->characterIconTexture.c_str());
		}
	}
}

void PartyUI::fixedUpdate()
{

}

void PartyUI::destroy()
{

}