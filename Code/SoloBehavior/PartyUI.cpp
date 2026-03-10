#include "PartyUI.hpp"
#include "../Combat/BattleManager/BattleManager.hpp"

void PartyUI::AddIcon(Entity* en)
{
	icons.push_back(en);
}

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
			AEVec2 scale = { 100, 100 };
			if (party[i] == battleManager->GetActiveUnit())
			{
				scale = { 150, 150 };
			}
			if (icons[i]->transform)
			{
				icons[i]->transform->setScale(scale);
				//Debug to render the status icons
				//AEVec2 debugPos = { icons[i]->transform->getPosition() };
				//debugPos.y -= (icons[i]->transform->getScale().y * 0.5f + 50);
				//MeshGen::getInstance().DrawBox(debugPos, { 20, 20 }, Color(255, 255, 255, 1.f), 0.f);
			}
		}
	}
}

void PartyUI::fixedUpdate()
{

}

void PartyUI::destroy()
{
	icons.clear();
}