/*!
@file CombatEventHandler.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the interface of a Combat Event Handler
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
	DealtCriticalHit,
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

/*!***********************************************************************
* \class CombatEventHandler
* \brief
* A class to handle combat-related events
*************************************************************************/
class CombatEventHandler
{
public:
	//An alias
	using Callback = std::function<void(const EventData&)>;

	/*!***********************************************************************
	* \brief
	* Register a listener
	* \param type
	* The type of Event to listen for
	* \param cb
	* The function to run when the specified type is triggered
	* \return
	* A copied modifier from the database
	*************************************************************************/
	void Register(EventType type, Callback cb);

	/*!***********************************************************************
	* \brief
	* Calls all listeners specified by the event type
	* \param type
	* The event type to call all listeners for
	* \param data
	* A reference to the EventData to write to
	*************************************************************************/
	void Dispatch(EventType type, const EventData& data);

	/*!***********************************************************************
	* \brief
	* Clears all listeners
	*************************************************************************/
	void ClearAll();

	/*!***********************************************************************
	* \brief
	* Clears all listeners of a certain type
	* \param type
	* The specified event type
	*************************************************************************/
	void Clear(EventType type);

	//Singleton accessor
	static CombatEventHandler& Instance();

	//Default constructor
	CombatEventHandler();
private:
	//A map to store pairs of event type and callbacks
	std::unordered_map<EventType, std::vector<Callback>> listeners;
};