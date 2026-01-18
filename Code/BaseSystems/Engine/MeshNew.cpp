#include "MeshNew.hpp"
#include "MeshGen.hpp"

MeshGen* meshSystem = MeshGen::getInstance();

void MeshNew::Draw()
{
	switch (type)
	{
	case BOX_B:
	{
		meshSystem->DrawBox(entity->transform->getPosition(), entity->transform->getScale(), color, entity->transform->getRotation());
		break;
	}
	case BOX_BL:
	{
		meshSystem->DrawBoxLeft(entity->transform->getPosition(), entity->transform->getScale(), color, entity->transform->getRotation());
		break;
	}
	case BOX_T:
	{
		meshSystem->DrawBoxTexture(entity->transform->getPosition(), entity->transform->getScale(), color, entity->transform->getRotation(), pTex);
		break;
	}
	case CIRCLE_B:
	{
		meshSystem->DrawCircle(entity->transform->getPosition(), entity->transform->getScale(), color);
		break;
	}
	case SPRITE_T:
	{
		//meshSystem->DrawBox(entity->transform->position, entity->transform->scale, color, entity->transform->Deg);
		break;
	}

	}

}

void MeshNew::setMesh(char const* fileName)
{
	targetMesh = meshSystem->getMesh(fileName);
}
void MeshNew::setTexture(char const* fileName)
{
	pTex = meshSystem->getTexture(fileName);
}


void MeshNew::awake()
{

}


void MeshNew::init()
{

}

void MeshNew::update()
{
	Draw();

}

void MeshNew::fixedUpdate()
{

}

void MeshNew::destroy()
{

}
