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

	MeshGen::getInstance().DrawFont(currentTurnTextPos.x, currentTurnTextPos.y, 0.8f, Color(255, 255, 255, 255), "Turn", "liberi");
	MeshGen::getInstance().DrawFont(currentTurnTextPos.x - 0.05f, currentTurnTextPos.y - 0.1f, 0.8f, Color(255, 255, 255, 255), to_string(battleManager->GetCurrentTurn()).c_str(), "liberi");
	if (battleManager->GetActiveUnit()->GetFaction() == Game::PLAYER)
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
		AEVec2 scale = { 300, 10 };
		AEVec2 trueScale = { scale.x * hpperc, scale.y };
		MeshGen::getInstance().DrawBoxLeft(activeUnitHPPos, scale, Color(155, 0, 0, 1), 0);
		MeshGen::getInstance().DrawBoxLeft(activeUnitHPPos, trueScale, color, 0);
		MeshGen::getInstance().DrawFont(-0.7, 0.78f, 0.5f, Color(255, 255, 255, 255), battleManager->GetActiveUnit()->GetName().c_str(), "liberi");
	}
}

void MainHealthbar::fixedUpdate()
{
}

void MainHealthbar::destroy()
{
}
