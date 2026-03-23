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
#include "../UI_WZBJ_Pak.hpp"

RunManager::RunManager()
{
	party.reserve(3);
	party.push_back("Guy");
	party.push_back("Char2");
	party.push_back("Char3");

	SetMapType(MapType::CityStreets);
}

void RunManager::StartRun()
{
	//Set default values
	enemyDifficulty = 1;

	//Can change this if the player owns an artifact
	currency = 50;

	currMapType = OuterPalace;
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

void RunManager::ResetSave()
{
	if (std::remove("Assets/Map/PlayMap.json") != 0)
		std::cout << "PlayMap.json was unable to be removed.\n";
	if (std::remove("Assets/Map/ViewMap.json") != 0)
		std::cout << "ViewMap.json was unable to be removed.\n";
	if (std::remove("Assets/Map/NavData.json") != 0)
		std::cout << "NavData.json was unable to be removed.\n";

	runBlessings.clear();
	currency = 50;
}

void RunManager::AddBlessing(std::unique_ptr<Blessing> bless)
{
	AEVec2 pos = { 0, 0 };
	AEVec2 scale = { AEGfxGetWindowWidth() * 0.8f, AEGfxGetWindowHeight() * 0.8f };

	auto displayBox = std::make_unique<Entity>("DisplayBox");
	displayBox->addComponent<Transform2D>(pos, scale, 0.f);
	displayBox->addComponent<Mesh>("Box", Color(50, 50, 50, 0.9f), 1002, MeshType::BOX_B);
	const char* blessName = bless->blessingName.c_str();
	const char* blessDesc = bless->blessingDesc.c_str();
	displayBox->addComponent<DisplayBox>("New Blessing Obtained", blessName, blessDesc, "-- Click To Continue --");

	//Add a new blessing, the original blessing from the database is cloned
	runBlessings.push_back(std::move(bless));
	EntityManager::getInstance().rootEntity->transform->AddChild(displayBox->transform);
	EntityManager::getInstance().entities.push_back(std::move(displayBox));
}

void RunManager::SetBattleType(BATTLE_TYPE type)
{
	bt = type;
}

BATTLE_TYPE RunManager::GetBattleType() const
{
	return bt;
}

void RunManager::SetMapType(MapType type)
{
	currMapType = type;
	prevMapType = type;
}

void RunManager::IncrementMapType()
{
	if (currMapType < MapType::NUM_MAPTYPES)
	{
		prevMapType = currMapType;
		currMapType = MapType(currMapType + 1);
	}	
}

void RunManager::SetPrevMapType(MapType type)
{
	prevMapType = type;
}

MapType RunManager::GetMapType() const
{
	return currMapType;
}

MapType RunManager::GetPrevMapType() const
{
	return prevMapType;
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