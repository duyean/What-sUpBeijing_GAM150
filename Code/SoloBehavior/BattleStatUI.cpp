#include "BattleStatUI.hpp"
#include "../Combat/BattleManager/BattleManager.hpp"
#include <sstream>
#include <iomanip>

BattleStatUI::BattleStatUI() : render(false)
{
}

void BattleStatUI::ToggleRender()
{
	render = !render;
}

void BattleStatUI::SetBattleManager(BattleManager* bm)
{
	battleManager = bm;
}

void BattleStatUI::awake()
{
	
}

void BattleStatUI::init()
{
	AEVec2 pos{}, scale{};

	auto characterName = std::make_unique<Entity>("CharacterText");
}

void BattleStatUI::update()
{
	auto unit = battleManager->GetActiveUnit();
	if (unit && unit->GetFaction() == Game::FACTION::PLAYER && AEInputCheckTriggered(AEVK_TAB))
	{
		ToggleRender();
	}
	entity->mesh->isActive = render;
	if (render)
	{
		if (battleManager->GetActiveUnit()->GetFaction() != Game::FACTION::PLAYER)
		{
			return;
		}
	
		if (!unit) return;

		std::stringstream text;
		//Render Name
		MeshGen::getInstance().DrawFont(-0.8f, 0.8f, 1.0, Color(255, 255, 255, 1.0f), unit->GetName().c_str(), "liberi", TextAlignment::LEFT, 1501);

		text << "HP: " << std::ceil(unit->GetHealthPercentage() * unit->GetStat(Game::HP)) << "/" << std::ceil(unit->GetStat(Game::HP));
		MeshGen::getInstance().DrawFont(-0.8f, 0.6f, 1.0, Color(255, 255, 255, 1.0f), text.str().c_str(), "liberi", TextAlignment::LEFT, 1501);
		text.str("");
		text.clear();
		text << "ATK: " << std::round(unit->GetStat(Game::ATTRIBUTE_TYPE::ATK));
		MeshGen::getInstance().DrawFont(-0.8f, 0.5f, 1.0, Color(255, 255, 255, 1.0f), text.str().c_str(), "liberi", TextAlignment::LEFT, 1501);
		text.str("");
		text.clear();
		text << "DEF: " << std::round(unit->GetStat(Game::ATTRIBUTE_TYPE::DEF));
		MeshGen::getInstance().DrawFont(-0.8f, 0.4f, 1.0, Color(255, 255, 255, 1.0f), text.str().c_str(), "liberi", TextAlignment::LEFT, 1501);
		text.str("");
		text.clear();
		text << "CRIT Rate: " << std::fixed << std::setprecision(1) << std::round(unit->GetStat(Game::ATTRIBUTE_TYPE::CRIT_RATE) * 100) << "%";
		MeshGen::getInstance().DrawFont(-0.8f, 0.3f, 0.8f, Color(255, 255, 255, 1.0f), text.str().c_str(), "liberi", TextAlignment::LEFT, 1501);
		text.str("");
		text.clear();
		text << "CRIT DMG: " << std::fixed << std::setprecision(1) << std::round(unit->GetStat(Game::ATTRIBUTE_TYPE::CRIT_DAMAGE) * 100) << "%";
		MeshGen::getInstance().DrawFont(-0.8f, 0.2f, 0.8f, Color(255, 255, 255, 1.0f), text.str().c_str(), "liberi", TextAlignment::LEFT, 1501);
		text.str("");
		text.clear();
		text << "DMG Bonus: " << std::fixed << std::setprecision(1) << std::round(unit->GetStat(Game::ATTRIBUTE_TYPE::DMG_BONUS) * 100) << "%";
		MeshGen::getInstance().DrawFont(-0.8f, 0.1f, 0.8f, Color(255, 255, 255, 1.0f), text.str().c_str(), "liberi", TextAlignment::LEFT, 1501);
		text.str("");
		text.clear();
		text << "DMG Reduction: " << std::fixed << std::setprecision(1) << std::round(unit->GetStat(Game::ATTRIBUTE_TYPE::DMG_REDUCTION) * 100) << "%";
		MeshGen::getInstance().DrawFont(-0.8f, 0.0f, 0.8f, Color(255, 255, 255, 1.0f), text.str().c_str(), "liberi", TextAlignment::LEFT, 1501);
	}
}

void BattleStatUI::fixedUpdate()
{

}

void BattleStatUI::destroy()
{
	battleManager = nullptr;
}