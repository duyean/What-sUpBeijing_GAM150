#include "TutorialScreen.hpp"
#include "../BaseSystems/Engine/EventSystem.hpp"
#include "../Code/SoloBehavior/PauseMenu.hpp"
#include "../Audio_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"

void TutorialScreen::NextSlide()
{
	++currentPage;
	if (currentPage == tutorialPages.size()-1)
	{
		nextButton->entity->isActive = false;
		prevButton->entity->isActive = true;
		closeButton->entity->isActive = true;
	}
	else
	{
		prevButton->entity->isActive = true;
		nextButton->entity->isActive = true;
	}
	tutorial_tb->text = tutorialPages[currentPage].desc;
	tutorial_img->setTexture(tutorialPages[currentPage].textureName);
}

void TutorialScreen::PrevSlide()
{
	--currentPage;

	if (currentPage == 0)
	{
		prevButton->entity->isActive = false;
		nextButton->entity->isActive = true;
	}
	else prevButton->entity->isActive = true;

	tutorial_tb->text = tutorialPages[currentPage].desc;
	tutorial_img->setTexture(tutorialPages[currentPage].textureName);
}

void TutorialScreen::ShowTutorial(bool canShow)
{
	for (Entity* en : prevDisplay)
	{
		en->isActive = !canShow;
	}

	for (Transform2D* child : entity->transform->children)
	{
		child->entity->isActive = canShow;
	}

	RunManager::Instance().playerCanMove = !canShow;
}

void TutorialScreen::awake()
{
	enSystem = &EntityManager::getInstance();
	meSystem = &MeshGen::getInstance();

	//background
	auto tutorial_bg = std::make_unique<Entity>("TUTORIAL BG");
	AEVec2 pos = { 0.f ,0.f };
	AEVec2 scale = { (float)AEGfxGetWindowWidth() * 0.8f, (float)AEGfxGetWindowHeight() * 0.95f };
	tutorial_bg->addComponent<Transform2D>(pos, scale, 0.f);
	tutorial_bg->addComponent<Mesh>("Box", Color(1, 1, 1, 0.8f), 900, MeshType::BOX_B);
	entity->transform->AddChild(tutorial_bg->transform);

	//Tutorial page title
	auto tutorial_title = std::make_unique<Entity>("TUTORIAL TITLE");
	pos = { 0.f ,(float)AEGfxGetWindowHeight()/2.f };
	scale = { 1.f, 1.f };
	tutorial_title->addComponent<Transform2D>(pos, scale, 0.f);
	switch (tut_type)
	{
	case TutorialScreen::TUTORIAL_TYPE::TUTORIAL_BASE_CAMP:
		tutorialTitle = "BASE CAMP TUTORIAL";
		break;
	case TutorialScreen::TUTORIAL_TYPE::TUTORIAL_EXPLORATION:
		tutorialTitle = "EXPLORATION TUTORIAL";
		break;
	case TutorialScreen::TUTORIAL_TYPE::TUTORIAL_COMBAT:
		tutorialTitle = "COMBAT TUTORIAL";
		break;
	default:
		break;
	}
	TextBox* ttb = tutorial_title->addComponent<TextBox>(tutorialTitle, 1.5f, TextBoxVAllign::TOP, TextBoxHAllign::CENTER);
	ttb->padding_v = 100.f;
	ttb->text_layer = 902;
	entity->transform->AddChild(tutorial_title->transform);

	//Tutorial image
	auto tutorial_image = std::make_unique<Entity>("TUTORIAL IMAGE");
	pos = { 0.f ,50.f};
	scale = { 600.f, 400.f };
	tutorial_image->addComponent<Transform2D>(pos, scale, 0.f);	
	switch (tut_type)
	{
	case TutorialScreen::TUTORIAL_TYPE::TUTORIAL_BASE_CAMP:
		for (int i = 0; i < BCT_PAGES; i++)
		{
			meSystem->CreateTexture(bc_tut_pages[i].textureDir, bc_tut_pages[i].textureName);
			tutorialPages.push_back(bc_tut_pages[i]);
		}
		tutorial_img = tutorial_image->addComponent<Mesh>("Box", bc_tut_pages[0].textureName, Color(255, 255, 255, 1.0f), 901, MeshType::BOX_T);
		break;
	case TutorialScreen::TUTORIAL_TYPE::TUTORIAL_EXPLORATION:
		for (int i = 0; i < ET_PAGES; i++)
		{
			meSystem->CreateTexture(explr_tut_pages[i].textureDir, explr_tut_pages[i].textureName);
			tutorialPages.push_back(explr_tut_pages[i]);
		}
		tutorial_img = tutorial_image->addComponent<Mesh>("Box", explr_tut_pages[0].textureName, Color(255, 255, 255, 1.0f), 901, MeshType::BOX_T);
		break;
	case TutorialScreen::TUTORIAL_TYPE::TUTORIAL_COMBAT:
		for (int i = 0; i < CT_PAGES; i++)
		{
			meSystem->CreateTexture(cmbt_tut_pages[i].textureDir, cmbt_tut_pages[i].textureName);
			tutorialPages.push_back(cmbt_tut_pages[i]);
		}
		tutorial_img = tutorial_image->addComponent<Mesh>("Box", cmbt_tut_pages[0].textureName, Color(255, 255, 255, 1.0f), 901, MeshType::BOX_T);
		break;
	}
	entity->transform->AddChild(tutorial_image->transform);

	//tutorial description
	auto tutorial_desc = std::make_unique<Entity>("TUTORIAL DESC");
	pos = { 0.f ,-(float)AEGfxGetWindowHeight() / 2.f };
	scale = { (float)AEGfxGetWindowWidth() * 0.8f, 1.f };
	tutorial_desc->addComponent<Transform2D>(pos, scale, 0.f);
	tutorial_tb = tutorial_desc->addComponent<TextBox>(
		tutorialPages[0].desc,
		0.6f, TextBoxVAllign::BOTTOM, TextBoxHAllign::CENTER);
	tutorial_tb->padding_v = -250.f;
	tutorial_tb->text_layer = 902;
	entity->transform->AddChild(tutorial_desc->transform);

	//Prev Page Button
	auto prev_b = std::make_unique<Entity>("PREV PAGE BUTTON");
	pos = { -200.f, -300.f };
	scale = { 200.f, 80.f };
	prev_b->addComponent<Transform2D>(pos, scale, 0.f);
	prev_b->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 901, MeshType::BOX_T);
	entity->transform->AddChild(prev_b->transform);

	prevButton = prev_b->addComponent<Button>();
	prevButton->SetOnClick([this]() {PrevSlide(); });
	prevButton->SetNormalColor(Color{ 200,200,200,1 });
	prevButton->SetHighlightedColor(Color{ 255,255,255,1 });
	TextBox* pb_tb = prev_b->addComponent<TextBox>("PREV", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	pb_tb->text_layer = 902;

	//Next Page Button
	auto next_b = std::make_unique<Entity>("NEXT PAGE BUTTON");
	pos = { 200.f, -300.f };
	scale = { 200.f, 80.f };
	next_b->addComponent<Transform2D>(pos, scale, 0.f);
	next_b->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 901, MeshType::BOX_T);
	entity->transform->AddChild(next_b->transform);

	nextButton = next_b->addComponent<Button>();
	nextButton->SetOnClick([this]() {NextSlide(); });
	nextButton->SetNormalColor(Color{ 200,200,200,1 });
	nextButton->SetHighlightedColor(Color{ 255,255,255,1 });
	TextBox* nb_tb = next_b->addComponent<TextBox>("NEXT", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	nb_tb->text_layer = 902;

	//Close Button
	auto close_b = std::make_unique<Entity>("CLOSE BUTTON");
	pos = { 550.f, 350.f };
	scale = { 50.f, 50.f };
	close_b->addComponent<Transform2D>(pos, scale, 0.f);
	close_b->addComponent<Mesh>("Box", Color(200, 1, 1, 1.f), 901, MeshType::BOX_B);
	entity->transform->AddChild(close_b->transform);

	closeButton = close_b->addComponent<Button>();
	closeButton->SetOnClick([this]() {ShowTutorial(false); });
	closeButton->SetNormalColor(Color{ 200,1,1,1 });
	closeButton->SetHighlightedColor(Color{ 255,1,1,1 });
	TextBox* cb_tb = close_b->addComponent<TextBox>("X", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	cb_tb->text_layer = 902;
	

	enSystem->entities.push_back(std::move(tutorial_bg));
	enSystem->entities.push_back(std::move(tutorial_title));
	enSystem->entities.push_back(std::move(tutorial_image));
	enSystem->entities.push_back(std::move(tutorial_desc));
	enSystem->entities.push_back(std::move(next_b));
	enSystem->entities.push_back(std::move(prev_b));
	enSystem->entities.push_back(std::move(close_b));
}

void TutorialScreen::init()
{
	prevButton->entity->isActive = false;
	currentPage = 0;
	RunManager::Instance().playerCanMove = false;
}

void TutorialScreen::update()
{
	if (RunManager::Instance().game_paused)
		ShowTutorial(false);
}

void TutorialScreen::fixedUpdate()
{

}

void TutorialScreen::destroy()
{

}

void TutorialScreen::AddPrevDisplayEntity(Entity* en)
{
	prevDisplay.push_back(en);
}
