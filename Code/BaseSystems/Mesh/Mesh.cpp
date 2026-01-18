#include "Mesh.hpp"
#include "MeshGen.hpp"

MeshGen* meshSystem = MeshGen::getInstance();

void Mesh::Draw()
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

void Mesh::setMesh(char const* fileName)
{
	targetMesh = meshSystem->getMesh(fileName);
}
void Mesh::setTexture(char const* fileName)
{
	pTex = meshSystem->getTexture(fileName);
}


void Mesh::awake()
{

}


void Mesh::init()
{

}

void Mesh::update()
{
	Draw();

}

void Mesh::fixedUpdate()
{

}

void Mesh::destroy()
{

}
