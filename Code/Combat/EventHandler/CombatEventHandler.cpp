#include "CombatEventHandler.hpp"
#include "../Character/Character.hpp"

CombatEventHandler::CombatEventHandler()
{
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
    if (listeners.empty())
    {
        return;
    }

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