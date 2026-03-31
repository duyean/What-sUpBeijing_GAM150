#include "MainHealthbar.hpp"
#include <sstream>

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
		std::ostringstream os;
		os << "Lv " << RunManager::Instance().GetPartyLevel() << " " << battleManager->GetActiveUnit()->GetName();
		MeshGen::getInstance().DrawFont(-0.825f, 0.725f, 0.5f, Color(255, 255, 255, 255),os.str().c_str(), "liberi", TextAlignment::LEFT, 700);

	}
	std::ostringstream oss;
	oss << "Action Points: " << battleManager->actionPoint << "/" << battleManager->maxActionPoints;
	MeshGen::getInstance().DrawFont(-0.825f, 0.91f, 0.6f, Color(255, 255, 255, 1), oss.str().c_str(), "liberi", TextAlignment::LEFT, 700);
}

void MainHealthbar::fixedUpdate()
{
}

void MainHealthbar::destroy()
{
}
