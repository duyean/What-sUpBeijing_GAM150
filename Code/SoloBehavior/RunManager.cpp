#include "RunManager.hpp"

void RunManager::StartRun()
{
	//Set default values
}

void RunManager::ResetRun()
{
	runBlessings.clear();
}

void RunManager::AddBlessing(std::unique_ptr<Blessing> bless)
{
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