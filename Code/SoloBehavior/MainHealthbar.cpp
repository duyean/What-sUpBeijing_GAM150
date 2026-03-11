#include "MainHealthbar.hpp"

void MainHealthbar::awake()
{
	enSystem = &EntityManager::getInstance();
}

void MainHealthbar::init()
{
	battleManager = enSystem->findByComponentGLOBAL<BattleManager>()->getComponent<BattleManager>();
}

void MainHealthbar::update()
{
	if (!battleManager->InBattle())
	{
		return;
	}


	MeshGen::getInstance().DrawFont(currentTurnTextPos.x, currentTurnTextPos.y, 0.8f, Color(255, 255, 255, 255), "Turn", "liberi", TextAlignment::CENTER, 700);
	MeshGen::getInstance().DrawFont(currentTurnTextPos.x, currentTurnTextPos.y - 0.1f, 0.8f, Color(255, 255, 255, 255), to_string(battleManager->GetCurrentTurn()).c_str(), "liberi", TextAlignment::CENTER, 700);
	if (battleManager->GetActiveUnit() && battleManager->GetActiveUnit()->GetFaction() == Game::PLAYER)
	{
		Color color;
		float hpperc = battleManager->GetActiveUnit()->GetHealthPercentage();
		if (hpperc >= 0.4f)
		{
			color = Color(0, 255, 0, 1);
		}
		else
		{
			color = Color(255, 0, 0, 1);
		}
		AEVec2 scale = { 300, 12 };
		AEVec2 trueScale = { scale.x * hpperc, scale.y };
		entity->transform->setScale(trueScale);
		entity->getComponent<Mesh>()->color = color;
		MeshGen::getInstance().DrawFont(-0.825f, 0.7f, 0.5f, Color(255, 255, 255, 255), battleManager->GetActiveUnit()->GetName().c_str(), "liberi", TextAlignment::CENTER, 700);
	}
}

void MainHealthbar::fixedUpdate()
{
}

void MainHealthbar::destroy()
{
}
