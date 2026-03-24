
#include "EdgeManager.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"
#include "../Code/SoloBehavior/Player.hpp"
#include "../SoloBehavior/Occurence.hpp"
#include "../UI_WZBJ_Pak.hpp"
#include "../Audio_WZBJ_Pak.hpp"

void EdgeManager::awake()
{
	enSystem = &EntityManager::getInstance();
	N_path = enSystem->FindByNameGLOBAL("N_Path");
	E_path = enSystem->FindByNameGLOBAL("E_Path");
	S_path = enSystem->FindByNameGLOBAL("S_Path");
	W_path = enSystem->FindByNameGLOBAL("W_Path");
	notif = enSystem->FindByNameGLOBAL("Notification");

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

	N_path->transform->children[0]->entity->isActive = !node.n;
	E_path->transform->children[0]->entity->isActive = !node.e;
	S_path->transform->children[0]->entity->isActive = !node.s;
	W_path->transform->children[0]->entity->isActive = !node.w;

	NodeType currentNodeType = node.type;

	if (currentNodeType == NodeType::Entry)
	{
		switch_BC = true;
		notif->isActive = true;
	}
	else
	{
		switch_BC = false;
		notif->isActive = false;
	}

	if (hasTraveled)
	{
		switch (currentNodeType)
		{
		case NodeType::EnemyEncounter:
			player->getComponent<Player>()->canMove = false;
			RunManager::Instance().SetBattleType(BATTLE_TYPE::NORMAL);
			ts->TransitionToScene(GameStateManager::BATTLE_SCENE);
			map.playMap.mapNodes[map.yPos][map.xPos].type = NodeType::Empty;
			AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_BATTLE_START);
			break;
		case NodeType::Exit:
			player->getComponent<Player>()->canMove = false;
			RunManager::Instance().SetBattleType(BATTLE_TYPE::BOSS);
			ts->TransitionToScene(GameStateManager::BATTLE_SCENE);
			map.playMap.mapNodes[map.yPos][map.xPos].type = NodeType::Empty;
			AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_BATTLE_START);
			break;
		case NodeType::FixedEvent:
			player->getComponent<Player>()->canMove = false;
			RunManager::Instance().SetBattleType(BATTLE_TYPE::MINI_BOSS);
			ts->TransitionToScene(GameStateManager::BATTLE_SCENE);
			map.playMap.mapNodes[map.yPos][map.xPos].type = NodeType::Empty;
			AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_BATTLE_START);
			break;
		case NodeType::RandomEvent:
		{
			if (eventsDatabase.empty())
			{
				std::cout << "No events available!" << std::endl;
				break;
			}

			AEVec2 pos = { 0.f,0.f };
			AEVec2 scale = { 1.f, 1.f };
			std::uniform_int_distribution<int> dist(0, eventsDatabase.size() - 1);
			Occurence& randomOccurence = eventsDatabase.at(static_cast<OCCURENCE_ID>(dist(Game::gen)));
			pos = { 0.f, 0.f };
			scale = { 1.f, 1.f };
			auto decisionBoxManager = std::make_unique<Entity>("DecisionBoxManager");
			decisionBoxManager->addComponent<Transform2D>(pos, scale, 0.f);
			decisionBoxManager->addComponent<DecisionBoxManager>();
			enSystem->rootEntity->transform->AddChild(decisionBoxManager->transform);

			pos = { 0.f, 0.f };
			scale = { AEGfxGetWindowWidth() * 0.8f, AEGfxGetWindowHeight() * 0.8f };
			auto decisionBox = std::make_unique<Entity>("DecisionBox");
			decisionBox->addComponent<Transform2D>(pos, scale, 0.f);
			decisionBox->addComponent<Mesh>("Box", Color(0, 0, 0, 0.5f), 200, MeshType::BOX_B);
			decisionBoxManager->transform->AddChild(decisionBox->transform);

			pos = { -AEGfxGetWindowWidth() * 0.2f, -AEGfxGetWindowHeight() * 0.3f };
			scale = { AEGfxGetWindowWidth() * 0.3f, AEGfxGetWindowHeight() * 0.1f };
			auto decisionButtonLeft = std::make_unique<Entity>("DecisionButtonLeft");
			decisionButtonLeft->addComponent<Transform2D>(pos, scale, 0.f);
			decisionButtonLeft->addComponent<Mesh>("Box", Color(255, 255, 55, 1.f), 201, MeshType::BOX_B);
			decisionButtonLeft->addComponent<TextBox>(randomOccurence.option1Text, .5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);

			Button* leftDecButton = decisionButtonLeft->addComponent<Button>();
			leftDecButton->SetNormalColor(Color{ 55, 255, 55, 1.f });
			leftDecButton->SetHighlightedColor(Color{ 155, 255, 155, 1.f });
			leftDecButton->SetOnClick([this, randomOccurence, manager=decisionBoxManager.get()]() {
				if (randomOccurence.option1) {
					randomOccurence.option1(&RunManager::Instance());
				}
				manager->getComponent<DecisionBoxManager>()->ToggleDecisionBox(false);
				});	
			decisionBoxManager->transform->AddChild(decisionButtonLeft->transform);

			pos = { AEGfxGetWindowWidth() * 0.2f, -AEGfxGetWindowHeight() * 0.3f };
			scale = { AEGfxGetWindowWidth() * 0.3f, AEGfxGetWindowHeight() * 0.1f };
			auto decisionButtonRight = std::make_unique<Entity>("DecisionButtonRight");
			decisionButtonRight->addComponent<Transform2D>(pos, scale, 0.f);
			decisionButtonRight->addComponent<Mesh>("Box", Color(255, 255, 255, 1.f), 201, MeshType::BOX_B);
			decisionButtonRight->addComponent<TextBox>(randomOccurence.option2Text, .5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);

			Button* rightDecButton = decisionButtonRight->addComponent<Button>();
			rightDecButton->SetNormalColor(Color{ 255, 55, 55, 1.f });
			rightDecButton->SetHighlightedColor(Color{ 255, 155, 155, 1.f });
			rightDecButton->SetOnClick([this, randomOccurence, manager = decisionBoxManager.get()]() {
				if (randomOccurence.option2) {
					randomOccurence.option2(&RunManager::Instance());
				}
				manager->getComponent<DecisionBoxManager>()->ToggleDecisionBox(false);
				});
			decisionBoxManager->transform->AddChild(decisionButtonRight->transform);

			pos = { AEGfxGetWindowWidth() * 0.f, AEGfxGetWindowHeight() * 0.35f };
			scale = { AEGfxGetWindowWidth() * 0.8f, AEGfxGetWindowHeight() * 0.1f };
			auto decisionTitle = std::make_unique<Entity>("DecisionTitle");
			decisionTitle->addComponent<Transform2D>(pos, scale, 0.f);
			decisionTitle->addComponent<Mesh>("Box", Color(255, 255, 255, 0.f), 201, MeshType::BOX_B);
			decisionTitle->addComponent<TextBox>(randomOccurence.name, 1.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
			decisionBoxManager->transform->AddChild(decisionTitle->transform);
			pos = { AEGfxGetWindowWidth() * 0.f, AEGfxGetWindowHeight() * 0.05f };
			scale = { AEGfxGetWindowWidth() * 0.8f, AEGfxGetWindowHeight() * 0.5f };
			auto decisionTitle2 = std::make_unique<Entity>("DecisionTitle2");
			decisionTitle2->addComponent<Transform2D>(pos, scale, 0.f);
			decisionTitle2->addComponent<Mesh>("Box", Color(255, 255, 255, 0.f), 201, MeshType::BOX_B);
			decisionTitle2->addComponent<TextBox>(randomOccurence.desc, 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
			decisionBoxManager->transform->AddChild(decisionTitle2->transform);
			map.playMap.mapNodes[map.yPos][map.xPos].type = NodeType::Empty;

			enSystem->entities.push_back(std::move(decisionBox));
			enSystem->entities.push_back(std::move(decisionBoxManager));
			enSystem->entities.push_back(std::move(decisionButtonLeft));
			enSystem->entities.push_back(std::move(decisionButtonRight));
			enSystem->entities.push_back(std::move(decisionTitle));
			enSystem->entities.push_back(std::move(decisionTitle2));
			break;
		}
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
	}

	//check west
	if (!node.w)
	{
		MapNode westNode = map.playMap.mapNodes[map.yPos][map.xPos - 1];
	}

	//check north
	if (!node.n)
	{
		MapNode northNode = map.playMap.mapNodes[map.yPos - 1][map.xPos];
	}

	//check south
	if (!node.s)
	{
		MapNode southNode = map.playMap.mapNodes[map.yPos + 1][map.xPos];
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
		TravelNode(map, map.xPos, map.yPos - 1);
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
		TravelNode(map, map.xPos + 1, map.yPos);
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
		TravelNode(map, map.xPos, map.yPos + 1);
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
		TravelNode(map, map.xPos - 1, map.yPos);
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
		notif->isActive = false;
	}

}

void EdgeManager::fixedUpdate()
{

}

void EdgeManager::destroy()
{

}

