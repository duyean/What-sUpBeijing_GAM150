#include "SettingsScreen.hpp"
#include "../BaseSystems/Engine/EventSystem.hpp"
#include "../Code/SoloBehavior/PauseMenu.hpp"
#include "../Audio_WZBJ_Pak.hpp"

void SettingsScreen::ShowSettings(bool canShow)
{
	for (Entity* en : prevDisplay)
	{
		en->isActive = !canShow;
	}

	for (Transform2D* child : entity->transform->children)
	{
		child->entity->isActive = canShow;
	}
	bgm_sl->SliderSetActive(canShow);
	sfx_sl->SliderSetActive(canShow);

	isDisplaying = canShow;
}

void SettingsScreen::awake()
{
	enSystem = &EntityManager::getInstance();

	//background
	auto settings_bg = std::make_unique<Entity>("SETTINGS BG");
	AEVec2 pos = { 0.f ,0.f };
	AEVec2 scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	settings_bg->addComponent<Transform2D>(pos, scale, 0.f);
	settings_bg->addComponent<Mesh>("Box", Color(1, 1, 1, 0.5), 499, MeshType::BOX_B);
	entity->transform->AddChild(settings_bg->transform);

	//pause menu title
	auto title_settings = std::make_unique<Entity>("SETTINGS TITLE");
	pos = { 0.f ,(float)AEGfxGetWindowHeight()/2.f };
	scale = { 1.f, 1.f };
	title_settings->addComponent<Transform2D>(pos, scale, 0.f);
	TextBox* ttb = title_settings->addComponent<TextBox>("SETTINGS", 1.5f, TextBoxVAllign::TOP, TextBoxHAllign::CENTER);
	ttb->padding_v = 100.f;
	entity->transform->AddChild(title_settings->transform);


	auto title_sfx = std::make_unique<Entity>("SFX TITLE");
	pos = { 0.f , 150.f};
	scale = { 1.f, 1.f };
	title_sfx->addComponent<Transform2D>(pos, scale, 0.f);
	title_sfx->addComponent<TextBox>("SFX VOLUME", 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	entity->transform->AddChild(title_sfx->transform);

	auto sfx_slider = std::make_unique<Entity>("SFX Slider");
	pos = { 0.f, 100.f };
	scale = { 1.f, 1.f };
	sfx_slider->addComponent<Transform2D>(pos, scale, 0.f);
	sfx_sl = sfx_slider->addComponent<Slider>(AudioManager::GetInstance()->SFXVolume(), 1.f, .1f);
	entity->transform->AddChild(sfx_slider->transform);

	auto title_bgm = std::make_unique<Entity>("BGM TITLE");
	pos = { 0.f , 50.f };
	scale = { 1.f, 1.f };
	title_bgm->addComponent<Transform2D>(pos, scale, 0.f);
	title_bgm->addComponent<TextBox>("BGM VOLUME", 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	entity->transform->AddChild(title_bgm->transform);

	auto bgm_slider = std::make_unique<Entity>("BGM Slider");
	pos = { 0.f, 0.f };
	scale = { 1.f, 1.f }; 
	bgm_slider->addComponent<Transform2D>(pos, scale, 0.f);
	bgm_sl = bgm_slider->addComponent<Slider>(AudioManager::GetInstance()->BGMVolume(), 1.f, 0.1f);
	entity->transform->AddChild(bgm_slider->transform);


	//Close Button
	auto close_b = std::make_unique<Entity>("CLOSE BUTTON");
	pos = { 0.f, -300.f };
	scale = { 200.f, 80.f };
	close_b->addComponent<Transform2D>(pos, scale, 0.f);
	close_b->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	entity->transform->AddChild(close_b->transform);

	Button* closeButton = close_b->addComponent<Button>();
	closeButton->SetOnClick([this]() {ShowSettings(false); });
	closeButton->SetNormalColor(Color{ 200,200,200,1 });
	closeButton->SetHighlightedColor(Color{ 255,255,255,1 });
	close_b->addComponent<TextBox>("CLOSE", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	

	enSystem->entities.push_back(std::move(settings_bg));
	enSystem->entities.push_back(std::move(title_settings));

	enSystem->entities.push_back(std::move(title_sfx));
	enSystem->entities.push_back(std::move(sfx_slider));

	enSystem->entities.push_back(std::move(title_bgm));
	enSystem->entities.push_back(std::move(bgm_slider));

	enSystem->entities.push_back(std::move(close_b));

	ShowSettings(false);
}

void SettingsScreen::init()
{
	
}

void SettingsScreen::update()
{
	
}

void SettingsScreen::fixedUpdate()
{

}

void SettingsScreen::destroy()
{

}

void SettingsScreen::AddPrevDisplayEntity(Entity* en)
{
	prevDisplay.push_back(en);
}
