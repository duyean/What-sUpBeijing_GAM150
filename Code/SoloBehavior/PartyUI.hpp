#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include <array>

class BattleManager;

class PartyUI : public SoloBehavior
{
	const std::vector<AEVec2> iconPositions = { {60, -AEGfxGetWindowHeight() * 0.7f * 0.5f}, {300, -AEGfxGetWindowHeight() * 0.7f * 0.5f}, {550, -AEGfxGetWindowHeight() * 0.7f * 0.5f} };
	BattleManager* battleManager = nullptr;
	std::vector<Entity*> icons;
	std::vector<Entity*> healthBars;
	std::array<std::vector<Entity*>, 3> modifierIcons = {};
	Entity* modifierTooltip = nullptr;
	std::string toolTipBuffer;

public:
	void AddIcon(Entity* en);
	void AddModifierIcon(int index, Entity* en);
	void AddHealthBarEntity(Entity* en);
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
	bool IsMouseOverIcon(const s32& mouseX, const s32& mouseY, const Transform2D* transform);
};