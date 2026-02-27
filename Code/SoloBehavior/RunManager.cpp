#include "RunManager.hpp"

void RunManager::StartRun()
{
	//Set default values
}

void RunManager::ResetRun()
{
	runBlessings.clear();
}

RunManager& RunManager::Instance()
{
	static RunManager instance;
	return instance;
}