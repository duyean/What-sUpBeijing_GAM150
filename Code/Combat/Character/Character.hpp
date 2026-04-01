/*!
@file Character.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the interface for the Characters in the game
*//*______________________________________________________________________*/

#include "AEEngine.h"
#include "../Globals/Globals.hpp"
#include "../Modifier/Modifier.hpp"
#include "../Move.hpp"
#include "../../BaseSystems/JSONSerializer/JSONSerializer.hpp"
#include <vector>
#include <functional>
#include <string>
#include "../../Engine_WZBJ_Pak.hpp"

//Forward declaration
class MeshGen;

/*!***********************************************************************
* \class Character
* \brief
* The class to store Character data and implementations
*************************************************************************/
class Character : public SoloBehavior
{
private:
	//Enum to store the current SPRITE STATE for character sprites
	enum struct SPRITE_STATE
	{
		IDLE,
		ATTACKING,
	};

	//The timer to handle SPRITE STATE
	float spriteTimer = 0.f;

	//The current sprite state
	SPRITE_STATE spriteState = SPRITE_STATE::IDLE;

	//Pointer to the meshSystem
	MeshGen* meshSystem;

	//Whether the unit has chosen an action and is doing an animation
	bool endingTurn;

	//Name of the unit
	std::string name;

	//Element of the character
	Game::WUXING_ELEMENT element;

	//Probably should just made Enemy and PlayerChar child classes :(
	int enemyLevel;

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

	//Store the viable targets
	std::vector<Character*> targets;

public:
	Character();

	using DeathCallback = std::function<void(Character*)>;
	//The string for the character's base sprite
	std::string characterModelTexture;

	//The string for the character's attacking sprite
	std::string characterModelTexture2;

	//The string for the character's icon sprite
	std::string characterIconTexture;

	/*!***********************************************************************
	* \brief
	* Load the character data from the JSON database
	* \param[in] serializer
	* A reference to the JSON serialiser
	* \param[in] fileName
	* The name of the JSON file to use
	* \return
	* True if the operation was successful
	*************************************************************************/
	 bool LoadCharacter(JSONSerializer& serializer, std::string fileName); 

	 /*!***********************************************************************
	 * \brief
	 * Use a character move, specified by the move_slot
	 * \param[in] slot
	 * The move slot to use
	 * \param[in] target
	 * A pointer to the target of the move
	 * \param[in] renderMoveName
	 * Whether to show the move that was used. This is handled internally
	 *************************************************************************/
	 void UseMove(MOVE_SLOT slot, Character* target, bool renderMoveName = true);

	 /*!***********************************************************************
	 * \brief
	 * Use a character move, specified by the move_slot, overload for a vector of targets
	 * \param[in] slot
	 * The move slot to use
	 * \param[in] targets
	 * A vector of all the targets to use the move on
	 *************************************************************************/
	 void UseMove(MOVE_SLOT slot, std::vector<Character*> targets);

	 /*!***********************************************************************
	 * \brief
	 * Handles incoming damage taken
	 * \param[in] damageInfo
	 * A DamageInfo struct to store the Damage Info
	 *************************************************************************/
	 void TakeDamage(Game::DamageInfo& damageInfo);

	 /*!***********************************************************************
	 * \brief
	 * Handles dealing damage to a target
	 * \param[in] target
	 * The target to use the move on
	 * \param coefficient
	 * The coefficient of the damage, derived from the MOVE used
	 *************************************************************************/
	 void DealDamage(Character* target, float coefficient);

	 /*!***********************************************************************
	 * \brief
	 * Handles any attribute changes in battle
	 *************************************************************************/
	 void UpdateAttributes(void);

	 /*!***********************************************************************
	 * \brief
	 * Handles this unit's turn starting
	 *************************************************************************/
	 void StartTurn(void);

	 /*!***********************************************************************
	 * \brief
	 * Adds a modifier to this unit, this function also calls UpdateAttributes
	 * \param[in] modifier
	 * A unique_ptr to the modifier to be added
	 *************************************************************************/
	 void AddModifier(std::unique_ptr<Modifier> modifier);

	 /*!***********************************************************************
	 * \brief
	 * Process the unit's current modifiers
	 *************************************************************************/
	 void ProcessModifiers(void);

	 /*!***********************************************************************
	 * \brief
	 * Gets the current modifiers of this unit
	 * \return
	 * A vector of all modifiers on the current unit
	 *************************************************************************/
	 std::vector<std::unique_ptr<Modifier>> const& GetModifierList() const;

	 /*!***********************************************************************
	 * \brief
	 * Handles this unit's turn ending
	 *************************************************************************/
	 void EndTurn(void);

	 /*!***********************************************************************
	 * \brief
	 * Handles this unit's death
	 *************************************************************************/
	 void Death(void);
	
	 /*!***********************************************************************
	 * \brief
	 * Initialises the character at the start of battle. Distinct from init()
	 *************************************************************************/
	 void Init(void);

	 /*!***********************************************************************
	 * \brief
	 * Modifies this unit's attribute
	 * \param[in] type
	 * The attribute to modify
	 * \param value
	 * The amount to modify 
	 *************************************************************************/
	 void ModifyAttribute(Game::ATTRIBUTE_TYPE type, float value);

	 /*!***********************************************************************
	 * \brief
	 * Called by non-player controlled units to use a random attack
	 *************************************************************************/
	void AIAttack();

	//Start of Accessors and Mutators
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
	inline int GetLevel() const { return enemyLevel; }
	float GetStat(Game::ATTRIBUTE_TYPE type) const;
	//End of Accessors and Mutators

	void init() override;
	void awake() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

private:
	//A callback for other classes to use
	DeathCallback onDeath;
};