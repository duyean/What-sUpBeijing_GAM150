#include "ShopBlessing.hpp"

std::string ShopBlessing::GetTextureName()
{
	return blessing.get()->textureName;
}

std::unique_ptr<Blessing>& ShopBlessing::GetBlessing()
{
	return blessing;
}

void ShopBlessing::awake()
{
}

void ShopBlessing::init()
{
}

void ShopBlessing::update()
{
}

void ShopBlessing::fixedUpdate()
{
}

void ShopBlessing::destroy()
{
}

ShopBlessing::ShopBlessing(bool isRare)
{
	std::vector<std::unique_ptr<Blessing>> commonBlessings;
	std::vector<std::unique_ptr<Blessing>> rareBlessings;
	for (auto it = blessingDatabase.begin(); it != blessingDatabase.end(); ++it)
	{
		if (it->second.get()->blessingRarity == BLESSING_RARITY::COMMON || it->second.get()->blessingRarity == BLESSING_RARITY::RARE)
			commonBlessings.push_back(it->second->Clone());
		else
			rareBlessings.push_back(it->second->Clone());
	}
	std::uniform_int_distribution<int> randCommon(0, (int)commonBlessings.size() - 1);
	std::uniform_int_distribution<int> randRare(0, (int)rareBlessings.size() - 1);
	if (isRare)
	{
		auto it = rareBlessings.begin();
		std::advance(it, randRare(Game::gen));
		blessing = it->get()->Clone();
	}
	else
	{
		auto it = commonBlessings.begin();
		std::advance(it, randCommon(Game::gen));
		blessing = it->get()->Clone();
	}
}

ShopBlessing::~ShopBlessing()
{
}
