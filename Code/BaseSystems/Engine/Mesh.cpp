#include "Mesh.hpp"
#include "MeshGen.hpp"



void Mesh::setMesh(char const* fileName)
{
	targetMesh = MeshGen::getInstance().getMesh(fileName);
}
void Mesh::setTexture(char const* fileName)
{
	pTex = MeshGen::getInstance().getTexture(fileName);
}


void Mesh::awake()
{
	meshSystem = &MeshGen::getInstance();
}


void Mesh::init()
{

}

void Mesh::update()
{
	//Moved to a sorted draw layering
	//Draw();

}

void Mesh::fixedUpdate()
{

}

void Mesh::destroy()
{

}
