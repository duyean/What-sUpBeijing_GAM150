#include "MeshNew.hpp"
#include "MeshGen.hpp"

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
	//Moved to a sorted draw layering
	//Draw();

}

void MeshNew::fixedUpdate()
{

}

void MeshNew::destroy()
{

}
