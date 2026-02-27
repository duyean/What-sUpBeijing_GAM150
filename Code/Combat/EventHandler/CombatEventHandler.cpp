/*!
@file CombatEventHandler.cpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the implementation of a Combat Event Handler
*//*______________________________________________________________________*/

#include "CombatEventHandler.hpp"
#include "../Character/Character.hpp"

CombatEventHandler::CombatEventHandler()
{
    //Initialise the listeners to an empty map
    listeners = {};
}

CombatEventHandler& CombatEventHandler::Instance()
{
    static CombatEventHandler instance;
    return instance;
}

void CombatEventHandler::Register(EventType type, Callback cb)
{
	listeners[type].push_back(cb);
}

void CombatEventHandler::Dispatch(EventType type, const EventData& data)
{
    //Ensure there is at least one listener
    if (listeners.empty())
    {
        return;
    }

    //Find the key with the type
    auto it = listeners.find(type);
    if (it != listeners.end())
    {
        //Loop through all events of the trigger type
        for (auto& cb : it->second) 
        {
            //Call
            cb(data);
        }
    }
}

void CombatEventHandler::ClearAll()
{
	listeners.clear();
}

void CombatEventHandler::Clear(EventType type)
{
	listeners.erase(type);
}