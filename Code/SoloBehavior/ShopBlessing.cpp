#include "ShopBlessing.hpp"

std::string ShopBlessing::GetTextureName()
{
	return texture;
}

BLESSING_ID ShopBlessing::GetBlessingId()
{
	return blessingId;
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
	std::uniform_int_distribution<int> rand(0, blessingDatabase.size() - 1);
	auto it = blessingDatabase.begin();
	std::advance(it, rand(Game::gen));
	auto randBlessing = it->second->Clone();
	blessingId = randBlessing.get()->id;
	texture = randBlessing.get()->textureName;
}

ShopBlessing::~ShopBlessing()
{
}
