/*!
@file CombatEventHandler.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the inteface of a Combat Event Handler
*//*______________________________________________________________________*/

#pragma once
#include <functional>
#include <vector>
#include <unordered_map>

class Character;

//An enum of all possible event trigger types
enum struct EventType
{
	DealtDamage,
	TookDamage,
	DealtHealing,
	ReceivedHealing,
	OnCriticalHP,
	ModifierAdded,
};

//A struct that stores the event data
struct EventData
{
	//This is the character that triggered the event, can be null;
	Character* source;
	//This is the character that was affected by the event, can be null;
	Character* target;
	//This is the value associated with the event, be it damage or healing. 0 by default
	float eventValue = 0;
};

class CombatEventHandler
{
public:
	//An alias
	using Callback = std::function<void(const EventData&)>;

	/// <summary>
	/// Registers an event specified by its type and callback function
	/// </summary>
	/// <param name="type">The type of trigger to call this event</param>
	/// <param name="cb">The event that runs when triggered</param>
	void Register(EventType type, Callback cb);

	/// <summary>
	/// Calls all events determined by a certain type
	/// </summary>
	/// <param name="type">The trigger</param>
	/// <param name="data">The event data</param>
	void Dispatch(EventType type, const EventData& data);

	//Clears the listeners
	void ClearAll();

	//Clears all events of a certain type
	void Clear(EventType type);
	/*
	* Work in progress to allow removal of specific callback??? Pending
	*/

	//Singleton accessor
	static CombatEventHandler& Instance();
	CombatEventHandler();
private:
	std::unordered_map<EventType, std::vector<Callback>> listeners;
};