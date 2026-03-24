#include "Slider.hpp"
#include "../BaseSystems/Engine/EventSystem.hpp"

void Slider::awake()
{
	enSystem = &EntityManager::getInstance();
	meSystem = &MeshGen::getInstance();

	auto background = std::make_unique<Entity>("Background");
	AEVec2 pos = { 0.f, 0.f };
	AEVec2 scale = { 200.f, 50.f };
	background->addComponent<Transform2D>(pos, scale, 0.f);
	background->addComponent<Mesh>("Box",background_color, 100, MeshType::BOX_B);
	entity->transform->AddChild(background->transform);
	sliderComp.push_back(background.get());

	auto slider = std::make_unique<Entity>("Slider");
	pos = { -(scale.x * 0.5f), -(scale.y * 0.5f)};
	scale = { 1.f, 1.f };
	slider->addComponent<Transform2D>(pos, scale, 0.f);
	slider->addComponent<Mesh>("Box", slider_color, 100, MeshType::BOX_BL);
	background->transform->AddChild(slider->transform);
	sliderComp.push_back(slider.get());

	auto ib = std::make_unique<Entity>("inc button");
	pos = { 150.f, 0.f };
	scale = { 50.f, 50.f };
	ib->addComponent<Transform2D>(pos, scale, 0.f);
	ib->addComponent<Mesh>("Box", Color(200, 200, 200, 1.f), 100, MeshType::BOX_B);
	entity->transform->AddChild(ib->transform);
	
	Button* button_inc = ib->addComponent<Button>();
	button_inc->SetOnClick([this]() {Increase(this->value, this->max_value);});
	button_inc->SetNormalColor(Color{ 200,200,200,1 });
	button_inc->SetHighlightedColor(Color{ 255,255,255,1 });
	sliderComp.push_back(ib.get());

	auto db = std::make_unique<Entity>("dec button");
	pos = { -150.f, 0.f };
	scale = { 50.f, 50.f };
	db->addComponent<Transform2D>(pos, scale, 0.f);
	db->addComponent<Mesh>("Box", Color(200, 200, 200, 1.f), 100, MeshType::BOX_B);
	entity->transform->AddChild(db->transform);
	

	Button* button_dec = db->addComponent<Button>();
	button_dec->SetOnClick([this]() {Decrease(this->value);});
	button_dec->SetNormalColor(Color{ 200,200,200,1 });
	button_dec->SetHighlightedColor(Color{ 255,255,255,1 });

	sliderComp.push_back(db.get());

	enSystem->entities.push_back(std::move(background));
	enSystem->entities.push_back(std::move(slider));
	enSystem->entities.push_back(std::move(ib));
	enSystem->entities.push_back(std::move(db));
}

void Slider::init()
{	
	slider = entity->transform->children[0]->children[0]->entity;
}

void Slider::update()
{
	float slider_length = (float)value / (float)max_value;
	slider->transform->setLocalScale({ slider_length , 1.f });
}

void Slider::fixedUpdate()
{

}

void Slider::destroy()
{

}

void Slider::SliderSetActive(bool active)
{
	for (Entity* en : sliderComp)
	{
		en->isActive = active;
	}
}

void Slider::Increase(float& val, float const& max_val)
{
	if(val < max_val) val += changeFactor;
	if (val > max_val) val = max_val;
}

void Slider::Decrease(float& val)
{
	if(val > 0) val -= changeFactor;
	if (val < 0) val = 0.f;
}
