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
	background->addComponent<Mesh>("Box", Color(200, 200, 200, 1.f), 100, MeshType::BOX_B);
	entity->transform->AddChild(background->transform);

	auto slider = std::make_unique<Entity>("Slider");
	pos = { 0.f, 0.f };
	scale = { 1., 1.f };
	slider->addComponent<Transform2D>(pos, scale, 0.f);
	slider->addComponent<Mesh>("Box", Color(200, 0.f, 0.f, 1.f), 100, MeshType::BOX_B);
	background->transform->AddChild(slider->transform);

	auto ib = std::make_unique<Entity>("inc button");
	pos = { -150.f, 0.f };
	scale = { 50.f, 50.f };
	ib->addComponent<Transform2D>(pos, scale, 0.f);
	ib->addComponent<Mesh>("Box", Color(200, 200, 200, 1.f), 100, MeshType::BOX_B);
	entity->transform->AddChild(ib->transform);

	button_inc = ib->addComponent<Button>();
	button_inc->SetOnClick([this] {Increase();});

	auto db = std::make_unique<Entity>("dec button");
	pos = { 150.f, 0.f };
	scale = { 50.f, 50.f };
	db->addComponent<Transform2D>(pos, scale, 0.f);
	db->addComponent<Mesh>("Box", Color(200, 200, 200, 1.f), 100, MeshType::BOX_B);
	entity->transform->AddChild(db->transform);

	button_dec = db->addComponent<Button>();
	button_inc->SetOnClick([this] {Decrease();});

	enSystem->entities.push_back(std::move(background));
	enSystem->entities.push_back(std::move(slider));
	enSystem->entities.push_back(std::move(ib));
	enSystem->entities.push_back(std::move(db));
}

void Slider::init()
{	
	
}

void Slider::update()
{
	
}

void Slider::fixedUpdate()
{

}

void Slider::destroy()
{

}

void Slider::Increase()
{
	if (value <= max_value)
		++value;
}

void Slider::Decrease()
{
	if (0 <= value)
		--value;
}
