#include "Move.hpp"
#include <unordered_map>
#include <iostream>

std::unordered_map<MOVE_ID, Move> Move::moveDatabase;

void Move::InitMoveDatabase(JSONSerializer& serializer, std::string fileName)
{
	rapidjson::Document doc = serializer.ReadDocument(fileName);
	if (doc.IsNull())
	{
		std::cout << "Unable to load move database as Document is nullptr" << std::endl;
		return;
	}

	const rapidjson::Value& moves = doc["moves"];
	for (rapidjson::Value::ConstValueIterator p = moves.Begin(); p != moves.End(); ++p)
	{
		moveDatabase.emplace(static_cast<MOVE_ID>((*p)["id"].GetInt()),
			Move((*p)["name"].GetString(),
				(*p)["coefficient"].GetFloat(),
				(*p)["dot"].GetFloat(),
				(*p)["brief"].GetString(),
				(*p)["description"].GetString(),
				static_cast<Game::FACTION>((*p)["target"].GetInt())));

		std::cout << "Move id = " << (*p)["id"].GetInt()
			<< "\nname = " << (*p)["name"].GetString()
			<< "\ncoeff = " << (*p)["coefficient"].GetFloat()
			<< "\ndot = " << (*p)["dot"].GetFloat()
			<< "\nbrief = " << (*p)["brief"].GetString()
			<< "\ndesc = " << (*p)["description"].GetString()
			<< "\ntarget = " << (*p)["target"].GetInt() << std::endl;
	}

	moveDatabase[MOVE_BURN_MOVE].moveModifiers = std::vector <MODIFIER_ID>{GENERIC_DOT_BURN};
}