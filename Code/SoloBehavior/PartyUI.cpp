#include "PartyUI.hpp"
#include "../Combat/BattleManager/BattleManager.hpp"
#include "../UI_WZBJ_Pak.hpp"
#include <sstream>

bool PartyUI::IsMouseOverIcon(const s32& mouseX, const s32& mouseY, const Transform2D* transform)
{
	float halfWidth = transform->getLocalScale().x * 0.5f;
	float halfHeight = transform->getLocalScale().y * 0.5f;
	float centerX = transform->getLocalPosition().x;
	float centerY = transform->getLocalPosition().y;

	return std::abs(mouseX - centerX) <= halfWidth &&
		std::abs(mouseY - centerY) <= halfHeight;
}

void PartyUI::AddIcon(Entity* en)
{
	icons.push_back(en);
}

void PartyUI::AddModifierIcon(int index, Entity* en)
{
	if (index < 0 || index >= modifierIcons.size())
	{
		throw std::out_of_range("Index out of range");
	}
	modifierIcons[index].push_back(en);
}

void PartyUI::AddHealthBarEntity(Entity* en)
{
	healthBars.push_back(en);
}

void PartyUI::awake()
{

}

void PartyUI::init()
{
	battleManager = EntityManager::getInstance().findByComponentGLOBAL<BattleManager>()->getComponent<BattleManager>();
	modifierTooltip = EntityManager::getInstance().FindByNameGLOBAL("StatusTooltipUI");
}

void PartyUI::update()
{
	if (battleManager->InBattle())
	{
		auto party = battleManager->GetPlayerParty();
		for (int i = 0; i < party.size(); ++i)
		{
			AEVec2 scale = { 100, 100 };
			if (battleManager->GetActiveUnit())
			{
				if (party[i] == battleManager->GetActiveUnit())
				{
					scale = { 150, 150 };
				}
			}

			if (icons[i]->transform)
			{
				icons[i]->transform->setScale(scale);
			}

			if (party[i]->IsDead())
			{
				icons[i]->mesh->color = Color(255, 0, 0, 1.0f);
			}

			float hpperc = party[i]->GetHealthPercentage();
			AEVec2 trueScale = { 230 * hpperc, 40 };
			healthBars[i]->transform->setScale(trueScale);
		}

		std::unordered_map<Entity*, Modifier*> iconToModifier;

		//Render status icons
		for (auto& vec : modifierIcons)
		{
			for (auto& Entity : vec)
			{
				Entity->mesh->isActive = false;
			}
		}

		for (int i = 0; i < party.size(); ++i)
		{
			auto& modifiers = party[i]->GetModifierList();
			int modCount = 0;
			for (auto& mod : modifiers)
			{
				if (mod->hidden)
				{
					continue;
				}

				AEGfxTexture* tex = MeshGen::getInstance().getTexture(mod->icon.c_str());
				if (tex != nullptr)
				{
					auto* icon = modifierIcons[i][modCount];
					icon->getComponent<Mesh>()->isActive = true;
					icon->getComponent<Mesh>()->pTex = tex;
					iconToModifier[icon] = mod.get();
					++modCount;
				}

				if (modCount >= 3)
				{
					break;
				}
			}

			if (modCount <= 0)
			{
				continue;
			}

			AEVec2 pos = icons[i]->transform->getPosition();
			AEVec2 offset2 = { 0, -icons[i]->transform->getScale().y * 0.5f - 20};
			float x_offset = 30 + 10;

			AEVec2 centerPos = pos + offset2;
			float spacing = x_offset; // horizontal spacing between icons

			int total = std::min(modCount, 3); // only show up to 3 icons
			for (int j = 0; j < total; ++j)
			{
				auto ic = modifierIcons[i][j];
				// Compute offset so icons are centered as a group
				float offsetX = (j - (total - 1) / 2.0f) * spacing;
				AEVec2 iconPos = { centerPos.x + offsetX, centerPos.y };
				ic->transform->setPosition(iconPos);
				float normX = iconPos.x / (AEGfxGetWindowWidth() * 0.5f);
				float normY = (iconPos.y - 15) / (AEGfxGetWindowHeight() * 0.5f);
				MeshGen::getInstance().DrawFont(normX, normY, 0.35f, Color(255, 255, 255, 1.0f),
					std::to_string(iconToModifier[modifierIcons[i][j]]->duration).c_str(), "liberi");
			}
		}

		bool tooltipShown = false;
		for (auto& [icon, mod] : iconToModifier)
		{
			s32 mouseX, mouseY;
			AEInputGetCursorPosition(&mouseX, &mouseY);
			mouseX = mouseX - static_cast<s32>(AEGfxGetWindowWidth() * 0.5f);
			mouseY = static_cast<s32>(AEGfxGetWindowHeight() * 0.5f) - mouseY;

			if (IsMouseOverIcon(mouseX, mouseY, icon->transform))
			{
				std::ostringstream oss;
				oss << mod->name << std::endl;
				oss << mod->description;
				toolTipBuffer = oss.str();
				modifierTooltip->getComponent<TextBox>()->text = toolTipBuffer.c_str();
				tooltipShown = true;
				modifierTooltip->isActive = true;
				AEVec2 ttbox_scale = modifierTooltip->transform->getScale();
				modifierTooltip->transform->setPosition({ mouseX + (ttbox_scale.x / 2), mouseY + (ttbox_scale.y) });
				break;
			}
		}

		if (!tooltipShown)
		{
			modifierTooltip->isActive = false;
		}

	}
}

void PartyUI::fixedUpdate()
{

}

void PartyUI::destroy()
{
	icons.clear();
}