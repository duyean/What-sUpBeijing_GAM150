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

ShopBlessing::ShopBlessing()
{
	std::uniform_int_distribution<int> rand(0, (int)blessingDatabase.size() - 1);
	auto it = blessingDatabase.begin();
	std::advance(it, rand(Game::gen));
	blessing = it->second->Clone();
}

ShopBlessing::~ShopBlessing()
{
}
