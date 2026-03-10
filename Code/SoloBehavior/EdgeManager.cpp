
#include "EdgeManager.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"
#include "../Code/SoloBehavior/Player.hpp"

void EdgeManager::awake()
{
	enSystem = &EntityManager::getInstance();
	N_path = enSystem->FindByNameGLOBAL("N_Path");
	E_path = enSystem->FindByNameGLOBAL("E_Path");
	S_path = enSystem->FindByNameGLOBAL("S_Path");
	W_path = enSystem->FindByNameGLOBAL("W_Path");

	if(N_path) SE_N = N_path->getComponent<SceneEdge>();
	if(E_path) SE_E = E_path->getComponent<SceneEdge>();
	if (S_path) SE_S = S_path->getComponent<SceneEdge>();
	if (W_path) SE_W = W_path->getComponent<SceneEdge>();

	player = enSystem->FindByNameGLOBAL("Player");
	ts = enSystem->findByComponentGLOBAL<TransitionScreen>()->getComponent<TransitionScreen>();
}

void EdgeManager::UpdateEdges()
{
	MapNode node = map.playMap.mapNodes[map.yPos][map.xPos];
	N_path->isActive = !node.n;
	E_path->isActive = !node.e;
	S_path->isActive = !node.s;
	W_path->isActive = !node.w;	

	NodeType currentNodeType = node.type;

	if (hasTraveled)
	{
		switch (currentNodeType)
		{
		case NodeType::EnemyEncounter:
			player->getComponent<Player>()->canMove = false;
			RunManager::Instance().SetBattleType(BATTLE_TYPE::NORMAL);
			ts->TransitionToScene(GameStateManager::BATTLE_SCENE);
			map.playMap.mapNodes[map.yPos][map.xPos].type = NodeType::Empty;
			break;
		case NodeType::Exit:
			player->getComponent<Player>()->canMove = false;
			RunManager::Instance().SetBattleType(BATTLE_TYPE::BOSS);
			GameStateManager::GetInstance()->NextScene(GameStateManager::BATTLE_SCENE);
			break;
		default:
			break;
		}
	}

	CheckNeighborNode(node);
}

void EdgeManager::CheckNeighborNode(const MapNode& node)
{
	//check east
	if (!node.e)
	{
		MapNode eastNode = map.playMap.mapNodes[map.yPos][map.xPos + 1];
		if (eastNode.type == NodeType::Entry)
		{
			switch_BC = true;
		}
	}

	//check west
	if (!node.w)
	{
		MapNode westNode = map.playMap.mapNodes[map.yPos][map.xPos - 1];
		if (westNode.type == NodeType::Entry)
		{
			switch_BC = true;
		}
	}

	//check north
	if (!node.n)
	{
		MapNode northNode = map.playMap.mapNodes[map.yPos - 1][map.xPos];
		if (northNode.type == NodeType::Entry)
		{
			switch_BC = true;
		}
	}

	//check south
	if (!node.s)
	{
		MapNode southNode = map.playMap.mapNodes[map.yPos + 1][map.xPos];
		if (southNode.type == NodeType::Entry)
		{
			switch_BC = true;
		}
	}
}

void EdgeManager::init()
{
	UpdateEdges();
}

void EdgeManager::update()
{
	
	if (SE_N && SE_N->triggerBuffer)
	{
		hasTraveled = true;
		TravelNode(map, map.xPos, --map.yPos);
		GetCurrentNodeInfo(map);
		UpdateEdges();

		SE_N->triggerBuffer = false;


		AEVec2 playerpos = player->transform->getPosition();
		playerpos.y = -200.f;
		player->transform->setPosition(playerpos);
	}
	if (SE_E && SE_E->triggerBuffer)
	{
		hasTraveled = true;
		TravelNode(map, ++map.xPos, map.yPos);
		GetCurrentNodeInfo(map);
		UpdateEdges();

		SE_E->triggerBuffer = false;

		AEVec2 playerpos = player->transform->getPosition();
		playerpos.x = -600.f;
		player->transform->setPosition(playerpos);
	}
	if (SE_S && SE_S->triggerBuffer)
	{ 
		hasTraveled = true;
		TravelNode(map, map.xPos, ++map.yPos);
		GetCurrentNodeInfo(map);
		UpdateEdges();

		SE_S->triggerBuffer = false;

		AEVec2 playerpos = player->transform->getPosition();
		playerpos.y = 200.f;
		player->transform->setPosition(playerpos);
	}
	if (SE_W && SE_W->triggerBuffer)
	{ 
		hasTraveled = true;
		TravelNode(map, --map.xPos, map.yPos);
		GetCurrentNodeInfo(map);
		UpdateEdges();

		SE_W->triggerBuffer = false;

		AEVec2 playerpos = player->transform->getPosition();
		playerpos.x = 600.f;
		player->transform->setPosition(playerpos);
	}


	if (AEInputCheckTriggered(AEVK_SPACE) && switch_BC) 
	{
		ts->TransitionToScene(GameStateManager::BASE_CAMP);
		switch_BC = false;
	}

}

void EdgeManager::fixedUpdate()
{

}

void EdgeManager::destroy()
{

}

