#include "BattleManager.hpp"
#include <algorithm>
#include <iostream>
#include "../CombatUIManager.hpp"
#include "../../Scenes/SceneHandler/GameStateManager.hpp"

void BattleManager::awake()
{
	enSystem = &EntityManager::getInstance();
	ts = enSystem->findByComponentGLOBAL<TransitionScreen>()->getComponent<TransitionScreen>();
}

void BattleManager::init()
{

}

BattleManager::BattleManager() : delay(0), wait(false),
currentActiveUnit(0), enemyCount(0), inBattle(false), outcome(BATTLE_OUTCOME::NONE), lastTargetedUnit(nullptr), currentTurn(0)
{

}

bool BattleManager::PointInMesh(const s32& mouseX, const s32& mouseY, const Transform2D* transform)
{
	float halfWidth = transform->getLocalScale().x * 0.5f;
	float halfHeight = transform->getLocalScale().y * 0.5f;
	float centerX = transform->getLocalPosition().x;
	float centerY = transform->getLocalPosition().y;

	return std::abs(mouseX - centerX) <= halfWidth &&
		std::abs(mouseY - centerY) <= halfHeight;

}

Character* BattleManager::GetActiveUnit()
{
	return battleUnits[currentActiveUnit];
}

int BattleManager::GetCurrentTurn() const
{
	return currentTurn;
}

bool BattleManager::InBattle() const
{
	return inBattle;
}

void BattleManager::ProcessTargeting()
{
	for (Character* unit : battleUnits)
	{
		if (unit->GetFaction() != Game::FACTION::ENEMY)
		{
			continue;
		}
		s32 mouseX, mouseY;
		AEInputGetCursorPosition(&mouseX, &mouseY);

		//Convert to world space
		mouseX = mouseX - (AEGfxGetWindowWidth() * 0.5f);
		mouseY = (AEGfxGetWindowHeight() * 0.5f) - mouseY;
		//End of conversion

		if (PointInMesh(mouseX, mouseY, unit->entity->transform))
		{
			//Render crosshair here
			if (AEInputCheckTriggered(AEVK_LBUTTON))
			{
				lastTargetedUnit = unit;
				printf("Target Confirmed: %s\n", lastTargetedUnit->GetName().c_str());
			}
			break;
		}
	}
}

void BattleManager::ResetBattle()
{
	inBattle = false;

	//Delete the background
	Destroy(EntityManager::getInstance().FindByNameGLOBAL("BattleBackgroundIMG"));
	
	//Destroy all player sprites
	for (Character* unit : battleUnits)
	{
		Destroy(unit->entity);
	}

	//Clear Event Listeners
	CombatEventHandler::Instance().ClearAll();

	CombatUIManager::Instance().Reset();
	battleUnits.clear();
	lastTargetedUnit = nullptr;
	currentActiveUnit = 0;
	enemyCount = 0;
	wait = false;

}

void BattleManager::LoadBattleUnit(Character* unit)
{
	if (!unit)
	{
		printf("Warning: Attempted to add a null character to battle!\n");
		return;
	}
	unit->Init();
	battleUnits.push_back(unit);
}

void BattleManager::StartBattle()
{
	//Sort the list based on initiative in descending order
	outcome = NONE;
	std::sort(battleUnits.begin(), battleUnits.end(), [](const Character* a, const Character* b) {return a->GetInitiative() > b->GetInitiative();});
	for (Character* unit : battleUnits)
	{
		unit->SetOnDeath([this](Character* dead) {ProcessDeadUnit(dead);});
		if (unit->GetFaction() == Game::FACTION::ENEMY)
		{
			enemyCount++;
			if (!lastTargetedUnit)
			{
				lastTargetedUnit = unit;
			}
		}
	}
	currentActiveUnit = 0;
	inBattle = true;
	CombatUIManager::Instance().CreateMessageText({0.f, 225}, "Battle Start");
}

void BattleManager::update()
{
	//No updates when there is no battle
	if (!inBattle)
	{
		return;
	}
	
	//To allow delay between unit actions
	if (delay > 0.0f)
	{
		delay -= 1 / 60.0f;
		return;
	}

	if (outcome != BATTLE_OUTCOME::NONE)
	{
		if (delay < 0)
		{
			ResetBattle();

			BATTLE_TYPE bt = RunManager::Instance().GetBattleType();
			if (bt != BATTLE_TYPE::BOSS)
			{
				//Change scene back to exploration
				ts->TransitionToScene(GameStateManager::LEVEL_SCENE);
			}
			else
			{
				//Change scene back to base camp
				ts->TransitionToScene(GameStateManager::BASE_CAMP);
			}

		}
		return;
	}

	Character* activeUnit = battleUnits[currentActiveUnit];
	if (!wait)
	{
		currentTurn++;
		activeUnit->StartTurn();
		delay = 1.5f;
		wait = true;
	}

	if (activeUnit->GetFaction() == Game::PLAYER) //Player's turn
	{
		ProcessTargeting();
		if (lastTargetedUnit)
		{
			//Placeholder to render targeting UI
			MeshGen::getInstance().DrawCircle(lastTargetedUnit->entity->transform->getPosition(), {100, 100}, Color(255, 0, 0, 0.3f));
		}
		if (!activeUnit->TurnFinished() && wait)
		{
			//Register Inputs
			if (AEInputCheckTriggered(AEVK_Z))
			{
				activeUnit->UseMove(MOVE_SLOT_1, lastTargetedUnit);
			}
			else if (AEInputCheckTriggered(AEVK_X))
			{
				activeUnit->UseMove(MOVE_SLOT_2, lastTargetedUnit);
			}
			else if (AEInputCheckTriggered(AEVK_C))
			{
				activeUnit->UseMove(MOVE_SLOT_3, lastTargetedUnit);
			}
			else if (AEInputCheckTriggered(AEVK_V))
			{
				activeUnit->UseMove(MOVE_SLOT_4, lastTargetedUnit);
			}
		}
	}
	else
	{
		if (activeUnit->GetFaction() == Game::FACTION::ENEMY)
		{
			std::vector<Character*> playerTargets;
			std::copy_if(battleUnits.begin(), battleUnits.end(),
				std::back_inserter(playerTargets), [](Character* ch)
				{ return ch->GetFaction() == Game::FACTION::PLAYER; }
			);
			activeUnit->SetTargets(playerTargets);
			activeUnit->AIAttack();
		}
	}

	if (activeUnit->TurnFinished() && wait)
	{
		currentActiveUnit++;
		if (currentActiveUnit >= battleUnits.size())
		{
			currentActiveUnit = 0;
		}
		wait = false;
		delay = 1.5f;
	}
}

void BattleManager::fixedUpdate()
{

}

void BattleManager::ProcessDeadUnit(Character* dead)
{
	if (dead->GetFaction() == Game::FACTION::ENEMY)
	{
		auto it = std::find(battleUnits.begin(), battleUnits.end(), dead);
		if (it != battleUnits.end())
		{
			battleUnits.erase(it);
			enemyCount--;
			if (lastTargetedUnit == dead)
			{
				if (enemyCount > 0)
				{
					auto newTarget = std::find_if(battleUnits.begin(), battleUnits.end(), [](Character* ch) {return ch->GetFaction() == Game::FACTION::ENEMY;});
					lastTargetedUnit = *newTarget;
				}
			}
			Destroy(dead->entity);
		}

		if (enemyCount <= 0)
		{
			outcome = VICTORY;
			AEVec2 pos = { 0.f, 225 };
			CombatUIManager::Instance().CreateMessageText(pos, "Battle Over!");
			delay = 1.5f;
		}
	}
}

std::vector<Character*> BattleManager::GetPlayerParty()
{
	std::vector<Character*> toReturn = {};
	std::copy_if(battleUnits.begin(), battleUnits.end(), std::back_inserter(toReturn), [](Character* ch) {return ch && ch->GetFaction() == Game::PLAYER; });
	return toReturn;
}

void BattleManager::destroy()
{
	battleUnits.clear();
}