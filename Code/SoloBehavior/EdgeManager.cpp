
#include "EdgeManager.hpp"

void EdgeManager::awake()
{
	enSystem = &EntityManager::getInstance();
	N_path = enSystem->FindByNameGLOBAL("N_Path");
	E_path = enSystem->FindByNameGLOBAL("E_Path");
	S_path = enSystem->FindByNameGLOBAL("S_Path");
	W_path = enSystem->FindByNameGLOBAL("W_Path");
}

void EdgeManager::init()
{
	
}

void EdgeManager::update()
{
	MapNode node = map.playMap.mapNodes[map.yPos][map.xPos];
	N_path->isActive = node.n;
	E_path->isActive = node.e;
	S_path->isActive = node.s;
	W_path->isActive = node.w;
}

void EdgeManager::fixedUpdate()
{

}

void EdgeManager::destroy()
{

}