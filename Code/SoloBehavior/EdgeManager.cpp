
#include "EdgeManager.hpp"

void EdgeManager::awake()
{
	enSystem = &EntityManager::getInstance();
	N_path = enSystem->FindByNameGLOBAL("N_Path");
	E_path = enSystem->FindByNameGLOBAL("E_Path");
	S_path = enSystem->FindByNameGLOBAL("S_Path");
	W_path = enSystem->FindByNameGLOBAL("W_Path");

	SE_N = N_path->getComponent<SceneEdge>();
	SE_E = E_path->getComponent<SceneEdge>();
	SE_S = S_path->getComponent<SceneEdge>();
	SE_W = W_path->getComponent<SceneEdge>();

	player = enSystem->FindByNameGLOBAL("Player");
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

	if (SE_N->triggerBuffer)
	{
		TravelNode(map, map.xPos, ++map.yPos);
		GetCurrentNodeInfo(map);
		SE_N->triggerBuffer = false;

		AEVec2 playerpos = player->transform->getPosition();
		playerpos.y = -200.f;
		player->transform->setPosition(playerpos);
	}
	if (SE_E->triggerBuffer)
	{
		TravelNode(map, ++map.xPos, map.yPos);
		GetCurrentNodeInfo(map);
		SE_E->triggerBuffer = false;

		AEVec2 playerpos = player->transform->getPosition();
		playerpos.x = -600.f;
		player->transform->setPosition(playerpos);
	}
	if (SE_S->triggerBuffer) 
	{ 
		TravelNode(map, map.xPos, --map.yPos); 
		GetCurrentNodeInfo(map);
		SE_S->triggerBuffer = false;

		AEVec2 playerpos = player->transform->getPosition();
		playerpos.y = 200.f;
		player->transform->setPosition(playerpos);
	}
	if (SE_W->triggerBuffer) 
	{ 
		TravelNode(map, --map.xPos, map.yPos); 
		GetCurrentNodeInfo(map);
		SE_W->triggerBuffer = false;

		AEVec2 playerpos = player->transform->getPosition();
		playerpos.x = 600.f;
		player->transform->setPosition(playerpos);
	}
}

void EdgeManager::fixedUpdate()
{

}

void EdgeManager::destroy()
{

}