
#include "EdgeManager.hpp"

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

	//check east
	if (!node.e)
	{
		if (map.playMap.mapNodes[map.yPos][map.xPos + 1].type == NodeType::Entry)
		{
			std::cout << "//////////////////////" << std::endl;
			std::cout << "EAST NODE IS ENTRY!!!!" << std::endl;
			std::cout << "//////////////////////" << std::endl;

			switch_BC = true;
		}
	}

	//check west
	if (!node.w)
	{
		if (map.playMap.mapNodes[map.yPos][map.xPos - 1].type == NodeType::Entry)
		{
			std::cout << "//////////////////////" << std::endl;
			std::cout << "WEST NODE IS ENTRY!!!!" << std::endl;
			std::cout << "//////////////////////" << std::endl;

			switch_BC = true;
		}
	}
	
	//check north
	if (!node.n)
	{
		if (map.playMap.mapNodes[map.yPos - 1][map.xPos].type == NodeType::Entry)
		{
			std::cout << "//////////////////////" << std::endl;
			std::cout << "NORTH NODE IS ENTRY!!!!" << std::endl;
			std::cout << "//////////////////////" << std::endl;

			switch_BC = true;
		}
	}

	//check south
	if (!node.s)
	{
		if (map.playMap.mapNodes[map.yPos + 1][map.xPos].type == NodeType::Entry)
		{
			std::cout << "//////////////////////" << std::endl;
			std::cout << "SOUTH NODE IS ENTRY!!!!" << std::endl;
			std::cout << "//////////////////////" << std::endl;

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
		TravelNode(map, map.xPos, --map.yPos);
		GetCurrentNodeInfo(map);
		UpdateEdges();

		SE_N->triggerBuffer = false;

		if (player)
		{
			AEVec2 playerpos = player->transform->getPosition();
			playerpos.y = -200.f;
			player->transform->setPosition(playerpos);
		}

	}
	if (SE_E && SE_E->triggerBuffer)
	{
		TravelNode(map, ++map.xPos, map.yPos);
		GetCurrentNodeInfo(map);
		UpdateEdges();

		SE_E->triggerBuffer = false;

		if (player)
		{
			AEVec2 playerpos = player->transform->getPosition();
			playerpos.x = -600.f;
			player->transform->setPosition(playerpos);
		}
	}
	if (SE_S && SE_S->triggerBuffer)
	{ 
		TravelNode(map, map.xPos, ++map.yPos);
		GetCurrentNodeInfo(map);
		UpdateEdges();

		SE_S->triggerBuffer = false;

		if (player)
		{
			AEVec2 playerpos = player->transform->getPosition();
			playerpos.y = 200.f;
			player->transform->setPosition(playerpos);
		}
	}
	if (SE_W && SE_W->triggerBuffer)
	{ 
		TravelNode(map, --map.xPos, map.yPos);
		GetCurrentNodeInfo(map);
		UpdateEdges();

		SE_W->triggerBuffer = false;

		if (player)
		{
			AEVec2 playerpos = player->transform->getPosition();
			playerpos.x = 600.f;
			player->transform->setPosition(playerpos);
		}
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

