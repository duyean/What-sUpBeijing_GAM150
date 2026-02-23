#include "CombatEventHandler.hpp"
#include "../Character/Character.hpp"

CombatEventHandler::CombatEventHandler()
{
    if (!instance)
    {
        instance = this;
    }
}

void CombatEventHandler::Register(EventType type, Callback cb)
{
	listeners[type].push_back(cb);
}

void CombatEventHandler::Dispatch(EventType type, const EventData& data)
{
    auto it = listeners.find(type);
    if (it != listeners.end())
    {
        for (auto& cb : it->second) 
        {
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