#pragma once
#include <functional>
#include <vector>
#include <unordered_map>

class Character;

enum EventType
{
	DealtDamage,
	TookDamage,
	DealtHealing,
	ReceivedHealing,
	OnCriticalHP,
	ModifierAdded,
};

struct EventData
{
	Character* source;
	Character* target;
	float eventValue;
};

class CombatEventHandler
{
public:
	using Callback = std::function<void(const EventData&)>;

	void Register(EventType type, Callback cb);
	void Dispatch(EventType type, const EventData& data);
	void ClearAll();
	void Clear(EventType type);
	static CombatEventHandler* instance;

	CombatEventHandler();
private:
	std::unordered_map<EventType, std::vector<Callback>> listeners;
};