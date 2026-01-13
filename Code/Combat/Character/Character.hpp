#include "AEEngine.h"
#include "../Globals/Globals.hpp"
#include <vector>
#include <functional>

class Character
{
private:
	//How much health the unit has
	float hp;

	//How much maximum health the unit has
	float baseMaxHP, maxHPBonus, maxHP;

	//The offensive power of the unit
	float baseATK, atkBonus, atk;

	//The defensive power of the unit
	float baseDEF, defBonus, def;

	//Determines the probability of critical hits and bonus damage dealt
	float critRate, critDMG;
	
	//Separate multiplier for outgoing damage
	float dmgBonus;

	//Storing the modifiers of the unit
	std::vector<Game::Modifier> effectList;

	//A separate multipler for reducing damage
	float dmgReduction;

	//Determines turn order when combat begins
	int initiative;

	//Used by combat manager to determine this unit has finished acting
	bool turnFinished;

	//Whether this unit is an enemy or the player's party
	Game::FACTION faction;
public:
	using DeathCallback = std::function<void(Character*)>;

	virtual void TakeDamage(float incomingDamage);
	virtual void DealDamage(Character* target, float coefficient);
	virtual void UpdateAttributes(void);
	virtual void StartTurn(void);
	virtual void ProcessModifiers(void);
	virtual void EndTurn(void);
	virtual void Death(void);
	
	void SetOnDeath(DeathCallback cb) {onDeath = std::move(cb); }
	Game::FACTION GetFaction() const { return faction; }
	int GetInitiative(void) const { return initiative; }
	bool TurnFinished(void) const { return turnFinished; }

private:
	DeathCallback onDeath;
};