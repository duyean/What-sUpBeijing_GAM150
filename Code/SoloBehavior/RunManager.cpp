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
	party.reserve(2);
	party.push_back("Guy");
	party.push_back("Char2");
}

void RunManager::StartRun()
{
	//Set default values
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

const std::vector<std::unique_ptr<Blessing>>& RunManager::GetBlessings() const
{
	return runBlessings;
}

RunManager& RunManager::Instance()
{
	static RunManager instance;
	return instance;
}