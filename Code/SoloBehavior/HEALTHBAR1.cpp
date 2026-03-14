#include "HEALTHBAR1.hpp"
#include "../BaseSystems/Engine/EntityManager.hpp"
#include "Player.hpp"
#include "../Combat/Character/Character.hpp"

void Healthbar1::awake()
{

}


void Healthbar1::init()
{
	Healthbar1::enSystem = &EntityManager::getInstance();

}

void Healthbar1::update()
{
	AEVec2 pos = this->entity->transform->getPosition();
	float hpperc = this->entity->getComponent<Character>()->GetHealthPercentage();
	if (hpperc >= 0.4f)
	{
		color = Color(0, 255, 0, 1);
	}
	else
	{
		color = Color(255, 0, 0, 1);
	}
	AEVec2 scale = { 300, 10 };
	AEVec2 trueScale = { scale.x * hpperc, scale.y };
	AEVec2 offset{ -scale.x * 0.5f, -100 };
	MeshGen::getInstance().DrawFont((pos.x + offset.x)/ 800.f, (pos.y + offset.y - 30) / 450.f, 0.5f, Color(255, 255, 255, 1), this->entity->getComponent<Character>()->GetName().c_str(), "liberi");
	hpBarBG->transform->setPosition(pos + offset);
	hpBarBG->transform->setScale(scale);

	en->transform->setPosition(pos + offset);
	en->transform->setScale(trueScale);
	en->getComponent<Mesh>()->color = color;

	//Render status icons
	for (auto& Entity : statusIcons)
	{
		Entity->mesh->isActive = false;
	}

	auto& modifiers = this->entity->getComponent<Character>()->GetModifierList();
	int count = 0;
	for (auto& mod : modifiers)
	{
		if (mod->ID != GENERIC_ && mod->icon != "")
		{
			AEGfxTexture* tex = MeshGen::getInstance().getTexture(mod->icon.c_str());
			if (tex != nullptr)
			{
				statusIcons[count]->getComponent<Mesh>()->isActive = true;
				statusIcons[count]->getComponent<Mesh>()->pTex = tex;
				count++;
			}

			if (count >= 3)
			{
				break;
			}
		}
	}

	if (count <= 0)
	{
		return;
	}

	AEVec2 offset2 = { 0, offset.x * 1.1 };
	float x_offset = 30 + 10;

	AEVec2 centerPos = pos + offset2;
	float spacing = x_offset; // horizontal spacing between icons

	int total = std::min(count, 3); // only show up to 3 icons
	for (int i = 0; i < total; ++i)
	{
		// Compute offset so icons are centered as a group
		float offsetX = (i - (total - 1) / 2.0f) * spacing;
		AEVec2 iconPos = { centerPos.x + offsetX, centerPos.y };

		statusIcons[i]->transform->setPosition(iconPos);
	}
}

void Healthbar1::fixedUpdate()
{

}

void Healthbar1::destroy()
{
	Destroy(en);
	Destroy(hpBarBG);
	for (auto& entity : statusIcons)
	{
		Destroy(entity);
	}
}
