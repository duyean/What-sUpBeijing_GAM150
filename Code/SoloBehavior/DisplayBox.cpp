#include "DisplayBox.hpp"
#include "../UI_WZBJ_Pak.hpp"

DisplayBox::DisplayBox() : header(""), title(""), desc(""), footer(""), onClickDestroyTimer(0), children({})
{

}

DisplayBox::DisplayBox(const char* head, const char* t, const char* d, const char* foot) : header(head), 
title(t), desc(d), footer(foot), onClickDestroyTimer(0), children({})
{

}

void DisplayBox::awake()
{

}

void DisplayBox::init()
{
	onClickDestroyTimer = 0.5f;
	float parentYScale = entity->transform->getScale().y;
	AEVec2 pos = { 0, parentYScale * 0.5f - parentYScale * 0.05f};
	AEVec2 scale = { 600 , 100 };
	TextBox* ref = nullptr;

	auto headerEn = std::make_unique<Entity>("Header");
	headerEn->addComponent<Transform2D>(pos, scale, 0.f);
	headerEn->addComponent<Mesh>("Box", Color(255, 255, 255, 0.0f), 1003, MeshType::BOX_B);
	ref = headerEn->addComponent<TextBox>(header, 0.8f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	ref->text_layer = 9999;
	children.push_back(headerEn.get());
	
	pos = { 0, parentYScale * 0.5f - parentYScale * 0.3f };
	auto titleEn = std::make_unique<Entity>("Title");
	titleEn->addComponent<Transform2D>(pos, scale, 0.f);
	titleEn->addComponent<Mesh>("Box", Color(255, 255, 255, 0.f), 201, MeshType::BOX_B);
	ref = titleEn->addComponent<TextBox>(title, 0.7f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	ref->text_layer = 9999;
	children.push_back(titleEn.get());

	pos = { 0, parentYScale * 0.5f - parentYScale * 0.5f };
	auto descEn = std::make_unique<Entity>("Desc");
	descEn->addComponent<Transform2D>(pos, scale, 0.f);
	descEn->addComponent<Mesh>("Box", Color(255, 255, 255, 0.f), 201, MeshType::BOX_B);
	ref = descEn->addComponent<TextBox>(desc, 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	ref->text_layer = 9999;
	children.push_back(descEn.get());

	pos = { 0, -parentYScale * 0.5f + parentYScale * 0.1f };
	auto footerEn = std::make_unique<Entity>("Footer");
	footerEn->addComponent<Transform2D>(pos, scale, 0.5f);
	footerEn->addComponent<Mesh>("Box", Color(255, 255, 255, 0.f), 201, MeshType::BOX_B);
	ref = footerEn->addComponent<TextBox>(footer, 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	ref->text_layer = 9999;
	children.push_back(footerEn.get());

	EntityManager::getInstance().rootEntity->transform->AddChild(headerEn->transform);
	EntityManager::getInstance().rootEntity->transform->AddChild(titleEn->transform);
	EntityManager::getInstance().rootEntity->transform->AddChild(descEn->transform);
	EntityManager::getInstance().rootEntity->transform->AddChild(footerEn->transform);

	EntityManager::getInstance().entities.push_back(std::move(headerEn));
	EntityManager::getInstance().entities.push_back(std::move(titleEn));
	EntityManager::getInstance().entities.push_back(std::move(descEn));
	EntityManager::getInstance().entities.push_back(std::move(footerEn));
}

void DisplayBox::update()
{
	if (onClickDestroyTimer > 0)
	{
		onClickDestroyTimer -= (float)AEFrameRateControllerGetFrameTime();
	}

	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		if (onClickDestroyTimer <= 0)
		{
			for (auto& e : children)
			{
				Destroy(e);
			}
			Destroy(this->entity);
		}
	}
}

void DisplayBox::fixedUpdate()
{
}

void DisplayBox::destroy()
{

}