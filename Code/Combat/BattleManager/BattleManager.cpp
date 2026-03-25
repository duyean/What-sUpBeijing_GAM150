#include "BattleManager.hpp"
#include <algorithm>
#include <iostream>
#include "../CombatUIManager.hpp"
#include "../../Scenes/SceneHandler/GameStateManager.hpp"
#include "../Code/Audio_WZBJ_Pak.hpp"

void BattleManager::awake()
{
	enSystem = &EntityManager::getInstance();
}

void BattleManager::init()
{

}

BattleManager::BattleManager() : delay(0), wait(false),
currentActiveUnit(0), enemyCount(0), playerCount(0), inBattle(false), 
outcome(BATTLE_OUTCOME::NONE), lastTargetedUnit(nullptr), currentTurn(0), activeUnit(nullptr)
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
	return activeUnit;
}

Character* BattleManager::GetlastTargetedUnit()
{
	return lastTargetedUnit;
}

std::vector<Character*> BattleManager::GetAllEnemies()
{
	std::vector<Character*> enemies;
	std::copy_if(battleUnits.begin(), battleUnits.end(), std::back_inserter(enemies), [](Character* ch) {return ch->GetFaction() == Game::ENEMY && !ch->IsDead(); });
	return enemies;
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
		mouseX = mouseX - static_cast<s32>(AEGfxGetWindowWidth() * 0.5f);
		mouseY = static_cast<s32>(AEGfxGetWindowHeight() * 0.5f) - mouseY;
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
	playerUnits.clear();
	lastTargetedUnit = nullptr;
	currentActiveUnit = 0;
	enemyCount = 0;
	wait = false;

	std::uniform_int_distribution<int> d(1, 3);
	RunManager::Instance().ModifyEnemyDifficulty(d(Game::gen));
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
	if (unit->GetFaction() == Game::FACTION::PLAYER)
	{
		playerUnits.push_back(unit);
	}
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
		else
		{
			playerCount++;
		}
	}
	currentActiveUnit = 0;
	inBattle = true;
	CombatUIManager::Instance().CreateMessageText({ 0.f, 225 }, "Battle Start");
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
			ts = enSystem->findByComponentGLOBAL<TransitionScreen>()->getComponent<TransitionScreen>();
			BATTLE_TYPE bt = RunManager::Instance().GetBattleType();
			AEVec2 pos = { 0.f, 225 };

			if (outcome == BATTLE_OUTCOME::DEFEAT)
			{
				CombatUIManager::Instance().CreateMessageText(pos, "Game Over!");
			}
			else if (outcome == BATTLE_OUTCOME::VICTORY)
			{
				CombatUIManager::Instance().CreateMessageText(pos, "Battle Over!");
				AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_BATTLE_WIN);
			}

			if (bt == BATTLE_TYPE::MINI_BOSS)
			{
				//unlock character goes here
			}
			if (bt != BATTLE_TYPE::BOSS)
			{
				//Change scene back to exploration
				ts->TransitionToScene(GameStateManager::LEVEL_SCENE);
			}
			else
			{
				//Change scene back to base camp
				// Need check if win game or not
				RunManager::Instance().IncrementMapType();
				ts->TransitionToScene(GameStateManager::BASE_CAMP);
			}

		}
		return;
	}

	activeUnit = battleUnits[currentActiveUnit];
	if (!wait)
	{
		currentTurn++;
		delay = activeUnit->GetFaction() == Game::PLAYER ? 0.25f : 0.75f;
		activeUnit->StartTurn();
		wait = true;
	}

	if (activeUnit->GetFaction() == Game::PLAYER) //Player's turn
	{
		ProcessTargeting();
		if (!activeUnit->IsEndingTurn() && wait && !activeUnit->IsDead())
		{

			if (lastTargetedUnit)
			{
				//Placeholder to render targeting UI
				MeshGen::getInstance().DrawCircle(lastTargetedUnit->entity->transform->getPosition(), { 100, 100 }, Color(255, 0, 0, 0.3f));
			}
			MOVE_SLOT usingMove = MOVE_SLOT::NONE;
			//Register Inputs
			if (AEInputCheckTriggered(AEVK_Z))
			{
				usingMove = MOVE_SLOT::MOVE_SLOT_1;
			}
			else if (AEInputCheckTriggered(AEVK_X))
			{
				usingMove = MOVE_SLOT::MOVE_SLOT_2;
			}
			else if (AEInputCheckTriggered(AEVK_C))
			{
				usingMove = MOVE_SLOT::MOVE_SLOT_3;
			}
			else if (AEInputCheckTriggered(AEVK_V))
			{
				usingMove = MOVE_SLOT::MOVE_SLOT_4;
			}

			if (usingMove != MOVE_SLOT::NONE)
			{
				auto moveGroup = Move::moveDatabase[activeUnit->GetMoveList().at(usingMove)].targetGroup;
				switch (moveGroup)
				{
				case (Game::AOE_OPPOSITE):
				{
					activeUnit->UseMove(usingMove, GetAllEnemies());
					break;
				}
				case (Game::AOE_ALLY):
				{
					activeUnit->UseMove(usingMove, GetPlayerParty());
					break;
				}
				default:
				{
					activeUnit->UseMove(usingMove, lastTargetedUnit);
					break;
				}
				}
			}
		}
	}
	else
	{
		if (activeUnit->GetFaction() == Game::FACTION::ENEMY && !activeUnit->IsEndingTurn())
		{
			std::vector<Character*> playerTargets;
			std::copy_if(battleUnits.begin(), battleUnits.end(),
				std::back_inserter(playerTargets), [](Character* ch)
				{ return ch->GetFaction() == Game::FACTION::PLAYER && !ch->IsDead(); }
			);
			activeUnit->SetTargets(playerTargets);
			activeUnit->AIAttack();
		}
	}

	if (activeUnit->TurnFinished() && wait)
	{
		do
		{
			currentActiveUnit++;
			if (currentActiveUnit >= battleUnits.size())
			{
				currentActiveUnit = 0;
			}
			wait = false;

		} while (battleUnits[currentActiveUnit]->IsDead());
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
			delay = 1.5f;

			//DEBUG to add a random blessing after every battle victory
			std::uniform_int_distribution<size_t> dist(0, !blessingDatabase.size() ? 0 : blessingDatabase.size() - 1);
			auto it2 = blessingDatabase.begin();
			std::advance(it2, dist(Game::gen));
			auto randomBlessing = it2->second->Clone();
			RunManager::Instance().AddBlessing(std::move(randomBlessing));
		}
	}
	else if (dead->GetFaction() == Game::FACTION::PLAYER)
	{
		//auto it = std::find(battleUnits.begin(), battleUnits.end(), dead);
		//if (it != battleUnits.end())
		//{
		//	battleUnits.erase(it);
		//}
		//Cannot destroy player entity as Party UI is still referencing it

		--playerCount;
		if (playerCount <= 0)
		{
			outcome = DEFEAT;
			delay = 1.5f;
		}
	}
}

std::vector<Character*> BattleManager::GetPlayerParty() const
{
	return playerUnits;
}

void BattleManager::destroy()
{
	battleUnits.clear();
}