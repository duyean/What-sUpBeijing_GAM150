#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Combat/Globals/Globals.hpp"


class CombatUIManager : public SoloBehavior
{
public:
	static CombatUIManager* instance;
	/// <summary>
	/// Creates a damage number entity and pushes it to the EntityManager
	/// </summary>
	/// <param name="position">The starting position of the entity</param>
	/// <param name="info">The damage info struct</param>
	void CreateDamageNumber(AEVec2 position, Game::DamageInfo info);
	void CreateMessageText(AEVec2 position, std::string text, Color color = Color(255, 255, 255, 1));
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};