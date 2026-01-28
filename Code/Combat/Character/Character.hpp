#include "AEEngine.h"
#include "../Globals/Globals.hpp"
#include "../Modifier/Modifier.hpp"
#include "../Move.hpp"
#include "../../BaseSystems/JSONSerializer/JSONSerializer.hpp"
#include <vector>
#include <functional>
#include <string>
#include "../../Engine_WZBJ_Pak.hpp"

class Character : public SoloBehavior
{
private:
	//Name of the unit
	std::string name;

	//Element of the character
	Game::WUXING_ELEMENT element;

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
	std::vector<std::unique_ptr<Modifier>> effectList;

	//A separate multipler for reducing damage
	float dmgReduction;

	//Determines turn order when combat begins
	int initiative;

	//Used by combat manager to determine this unit has finished acting
	bool turnFinished;

	//Whether this unit is an enemy or the player's party
	Game::FACTION faction;

	//A map to store the move set for this character
	std::unordered_map<MOVE_SLOT, MOVE_ID> moveList;

public:
	using DeathCallback = std::function<void(Character*)>;

	//Load character data from JSON
	virtual void LoadCharacter(JSONSerializer& serializer, std::string fileName); 

	//Use the character's move, specified by the enum MOVE_SLOT
	virtual void UseMove(MOVE_SLOT slot, Character* target);

	//Handles incoming damage, reduced by DEF and other factors
	virtual void TakeDamage(Game::DamageInfo damageInfo);

	//Deals damage to the target, followed by the coefficient of the move
	virtual void DealDamage(Character* target, float coefficient);

	//Update any attribute modifiers
	virtual void UpdateAttributes(void);

	//Start this unit's turn
	virtual void StartTurn(void);

	//Add a Modifier to this unit. Automatically calls UpdateAttribute() 
	virtual void AddModifier(std::unique_ptr<Modifier> modifier);

	//Process any modifiers, usually used for damage over time effects
	virtual void ProcessModifiers(void);

	//End this unit's turn. If extra turns are implemented, edit here
	virtual void EndTurn(void);

	//Process this unit's death
	virtual void Death(void);
	
	//Initialise the character, typically used at the start of battle
	virtual void Init(void);

	//Modify the attribute bonus by a value
	virtual void ModifyAttribute(Game::ATTRIBUTE_TYPE type, float value);

	void SetOnDeath(DeathCallback cb) {onDeath = std::move(cb); }
	Game::FACTION GetFaction() const { return faction; }
	int GetInitiative(void) const { return initiative; }
	bool TurnFinished(void) const { return turnFinished; }
	void SetName(std::string name) { this->name = name; }
	void SetFaction(Game::FACTION faction) { this->faction = faction; }

	void init() override;
	void awake() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

private:
	DeathCallback onDeath;
};