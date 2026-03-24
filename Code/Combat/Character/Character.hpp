#include "AEEngine.h"
#include "../Globals/Globals.hpp"
#include "../Modifier/Modifier.hpp"
#include "../Move.hpp"
#include "../../BaseSystems/JSONSerializer/JSONSerializer.hpp"
#include <vector>
#include <functional>
#include <string>
#include "../../Engine_WZBJ_Pak.hpp"

class MeshGen;

class Character : public SoloBehavior
{
private:
	float timer = 2.f;

	MeshGen* meshSystem;

	//Whether the unit has chosen an action and is doing an animation
	bool endingTurn;

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

	//Whether this unit is dead
	bool isDead;

protected:
	//Whether this unit is an enemy or the player's party
	Game::FACTION faction;

	//A map to store the move set for this character
	std::unordered_map<MOVE_SLOT, MOVE_ID> moveList;

	std::vector<Character*> targets;

public:
	Character();

	using DeathCallback = std::function<void(Character*)>;
	std::string characterModelTexture;
	std::string characterModelTexture2;
	std::string characterIconTexture;

	//Load character data from JSON
	 bool LoadCharacter(JSONSerializer& serializer, std::string fileName); 

	//Use the character's move, specified by the enum MOVE_SLOT
	 void UseMove(MOVE_SLOT slot, Character* target, bool renderMoveName = true);

	//Use the character's move, specified by the enum MOVE_SLOT
	 void UseMove(MOVE_SLOT slot, std::vector<Character*> targets);

	//Handles incoming damage, reduced by DEF and other factors
	 void TakeDamage(Game::DamageInfo& damageInfo);

	//Deals damage to the target, followed by the coefficient of the move
	 void DealDamage(Character* target, float coefficient);

	//Update any attribute modifiers
	 void UpdateAttributes(void);

	//Start this unit's turn
	 void StartTurn(void);

	//Add a Modifier to this unit. Automatically calls UpdateAttribute() 
	 void AddModifier(std::unique_ptr<Modifier> modifier);

	//Process any modifiers, usually used for damage over time effects
	 void ProcessModifiers(void);

	//Get the modifiers of this unit
	 std::vector<std::unique_ptr<Modifier>> const& GetModifierList() const;

	//End this unit's turn. If extra turns are implemented, edit here
	 void EndTurn(void);

	//Process this unit's death
	 void Death(void);
	
	//Initialise the character, typically used at the start of battle
	 void Init(void);

	//Modify the attribute bonus by a value
	 void ModifyAttribute(Game::ATTRIBUTE_TYPE type, float value);

	//TThe character uses a random attack
	void AIAttack();

	inline void SetOnDeath(DeathCallback cb) {onDeath = std::move(cb); }
	inline Game::FACTION GetFaction() const { return faction; }
	inline int GetInitiative(void) const { return initiative; }
	inline bool TurnFinished(void) const { return turnFinished; }
	inline std::string GetName() const { return name; }
	inline void SetName(std::string n) { this->name = n; }
	inline void SetFaction(Game::FACTION f) { this->faction = f; }
	inline float GetHealthPercentage(void) { return hp / maxHP; }
	inline void SetTargets(std::vector<Character*> t) { this->targets = t; }
	inline Game::WUXING_ELEMENT GetElement() const { return element; }
	inline const std::unordered_map<MOVE_SLOT, MOVE_ID>& GetMoveList() const { return moveList; }
	inline bool IsEndingTurn() const { return endingTurn; }
	inline bool IsDead() const { return isDead; }

	void init() override;
	void awake() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

private:
	DeathCallback onDeath;
};