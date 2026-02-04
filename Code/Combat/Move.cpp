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
		Move m = Move((*p)["name"].GetString(),
			(*p)["coefficient"].GetFloat(),
			(*p)["dot"].GetFloat(),
			(*p)["brief"].GetString(),
			(*p)["description"].GetString(),
			static_cast<Game::MOVE_TARGET_GROUP>((*p)["target"].GetInt()));

		const rapidjson::Value& modifiers = (*p)["modifiers"];
		for (rapidjson::SizeType q = 0; q < modifiers.Size(); ++q)
		{
			m.moveModifiers.push_back(static_cast<MODIFIER_ID>(modifiers[q].GetInt()));
			std::cout << "modifier" << modifiers[q].GetInt() << " set for next move " << std::endl;
		}

		moveDatabase.emplace(static_cast<MOVE_ID>((*p)["id"].GetInt()), m);

		std::cout << "Move id = " << (*p)["id"].GetInt()
			<< "\nname = " << (*p)["name"].GetString()
			<< "\ncoeff = " << (*p)["coefficient"].GetFloat()
			<< "\ndot = " << (*p)["dot"].GetFloat()
			<< "\nbrief = " << (*p)["brief"].GetString()
			<< "\ndesc = " << (*p)["description"].GetString()
			<< "\ntarget = " << (*p)["target"].GetInt() << std::endl;
	}
}