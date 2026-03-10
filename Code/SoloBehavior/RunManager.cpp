/*!
@file RunManager.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the implementation for a Run Manager for our game.
*//*______________________________________________________________________*/
#include "RunManager.hpp"

RunManager::RunManager()
{
	party.reserve(3);
	party.push_back("Guy");
	party.push_back("Char2");
	party.push_back("Char3");
}

void RunManager::StartRun()
{
	//Set default values
	enemyDifficulty = 1;

	//Can change this if the player owns an artifact
	currency = 50;
}

const std::vector<std::string>& RunManager::GetParty() const
{
	return party;
}

void RunManager::ResetRun()
{
	//Clear the blessings for the current run
	runBlessings.clear();
}

void RunManager::AddBlessing(std::unique_ptr<Blessing> bless)
{
	//Add a new blessing, the original blessing from the database is cloned
	runBlessings.push_back(std::move(bless));
}

void RunManager::SetBattleType(BATTLE_TYPE type)
{
	bt = type;
}

BATTLE_TYPE RunManager::GetBattleType() const
{
	return bt;
}

const std::vector<std::unique_ptr<Blessing>>& RunManager::GetBlessings() const
{
	return runBlessings;
}


RunManager& RunManager::Instance()
{
	static RunManager instance;
	return instance;
}