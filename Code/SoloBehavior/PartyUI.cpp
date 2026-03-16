#include "PartyUI.hpp"
#include "../Combat/BattleManager/BattleManager.hpp"

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
				std::cout << "Party[" << i << "] Modifier: " << mod->name
					<< " Icon: " << mod->icon
					<< " Hidden: " << mod->hidden
					<< std::endl;

				if (!mod->hidden)
				{
					AEGfxTexture* tex = MeshGen::getInstance().getTexture(mod->icon.c_str());
					if (tex != nullptr)
					{
						modifierIcons[i][modCount]->getComponent<Mesh>()->isActive = true;
						modifierIcons[i][modCount]->getComponent<Mesh>()->pTex = tex;
						modCount++;
					}

					if (modCount >= 3)
					{
						break;
					}
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
				// Compute offset so icons are centered as a group
				float offsetX = (j - (total - 1) / 2.0f) * spacing;
				AEVec2 iconPos = { centerPos.x + offsetX, centerPos.y };

				modifierIcons[i][j]->transform->setPosition(iconPos);
			}
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