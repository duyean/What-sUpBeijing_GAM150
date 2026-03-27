#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Combat/Globals/Globals.hpp"
#include <queue>


class CombatUIManager : public SoloBehavior
{
private:
	std::unique_ptr<Entity> mainHP;
	//Queue to store the pending text elements to prevent overlapping
	std::queue<std::unique_ptr<Entity>> damageNumbers, messages;
	double dnDelay = 0, messDelay = 0;
	static CombatUIManager* instance;
public:
	static CombatUIManager& Instance();
	/// <summary>
	/// Creates a damage number entity and pushes it to the EntityManager
	/// </summary>
	/// <param name="position">The starting position of the entity</param>
	/// <param name="info">The damage info struct</param>
	void CreateDamageNumber(AEVec2 position, Game::DamageInfo info);
	/// <summary>
	/// Creates a message entity and pushes it to the EntityManager
	/// </summary>
	/// <param name="position">The position of the text</param>
	/// <param name="text">The text to display</param>
	/// <param name="color">The color of the text</param>
	void CreateMessageText(AEVec2 position, std::string text, Color color = Color(255, 255, 255, 1), float size = 1);

	/// <summary>
	/// Clears the queues
	/// </summary>
	void Reset();

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};