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

#include <iostream>
#include <fstream>

RunManager::RunManager()
{
	party.reserve(3);
	party.push_back("Guy");
	party.push_back("Char2");
	party.push_back("Char3");

	StartRun();
}

RunManager::~RunManager()
{
	SaveRun();
}

void RunManager::StartRun()
{
	if (!LoadRun())
	{
		//Set default values
		enemyDifficulty = 1;

		//Can change this if the player owns an artifact
		currency = 50;

		SetMapType(MapType::CityStreets);
	}
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

void RunManager::SaveRun() const
{
	JSONSerializer serializer;
	std::ofstream ofs("Assets/SaveFile.json");
	if (!ofs.is_open())
	{
		std::cout << "Cannot open Assets/SaveFile.json" << std::endl;
		return;
	}

	rapidjson::OStreamWrapper os(ofs);
	rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(os);
	
	writer.StartObject();
		writer.Key("enemyDifficulty");
		writer.Int(enemyDifficulty);
		writer.Key("currency");
		writer.Int(currency);
		writer.Key("currMapType");
		writer.Int(static_cast<int>(currMapType));
		writer.Key("prevMapType");
		writer.Int(static_cast<int>(prevMapType));
	writer.EndObject();
}

bool RunManager::LoadRun()
{
	JSONSerializer serializer;
	rapidjson::Document doc = serializer.ReadDocument("Assets/SaveFile.json");
	if (doc.IsNull())
	{
		std::cout << "Unable to load RunManager as Document is nullptr" << std::endl;
		return false;
	}
	enemyDifficulty = doc["enemyDifficulty"].GetInt();
	currency = doc["currency"].GetInt();
	currMapType = static_cast<MapType>(doc["currMapType"].GetInt());
	prevMapType = static_cast<MapType>(doc["prevMapType"].GetInt());
	return true;
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