#include "TextBox.hpp"

TextBox::TextBox()
{
	text = "text";
	text_allign = TextAlignment::LEFT;
	text_size = 0.5f;
	v_allign = TextBoxVAllign::TOP;
	h_allign = TextBoxHAllign::LEFT;

	line_padding = 1.f;
	padding_h = padding_v = 5.f;
}

TextBox::TextBox(const char* _text, float _size, TextBoxVAllign _allign_v, TextBoxHAllign _allign_h)
	:text(_text), text_size(_size), v_allign(_allign_v), h_allign(_allign_h)
{
	line_padding = 1.f;
	padding_h = padding_v = 5.f;
}

void TextBox::awake()
{
	textMesh = entity->addComponent<TextMesh>(AEVec2{ entity->transform->getPosition().x - (entity->transform->getScale().x/2),
		entity->transform->getPosition().y + (entity->transform->getScale().y / 2) }, text_size, "text", Color{ 255, 255, 255, 1.f }, text_allign);
}

void TextBox::init()
{
	textMesh->text = text;
	textMesh->size = text_size;
	textMesh->t_allign = text_allign;
	textMesh->padding = line_padding;


	switch (v_allign)
	{
	case TextBoxVAllign::TOP:
		textMesh->pos.y = entity->transform->getPosition().y + (entity->transform->getScale().y * 0.5f - padding_v);
		textMesh->tl_allign = TextLineAllignment::TOP;
		break;
	case TextBoxVAllign::CENTER:
		textMesh->pos.y = entity->transform->getPosition().y;
		textMesh->tl_allign = TextLineAllignment::CENTER;
		break;
	case TextBoxVAllign::BOTTOM:
		textMesh->pos.y = entity->transform->getPosition().y - (entity->transform->getScale().y * 0.5f + padding_v);
		textMesh->tl_allign = TextLineAllignment::BOTTOM;
		break;
	default:
		break;
	}

	switch (h_allign)
	{
	case TextBoxHAllign::LEFT:
		textMesh->pos.x = entity->transform->getPosition().x - (entity->transform->getScale().x * 0.5f - padding_h);
		textMesh->t_allign = TextAlignment::LEFT;
		break;
	case TextBoxHAllign::CENTER:
		textMesh->pos.x = entity->transform->getPosition().x;
		textMesh->t_allign = TextAlignment::CENTER;
		break;
	case TextBoxHAllign::RIGHT:
		textMesh->pos.x = entity->transform->getPosition().x + (entity->transform->getScale().x * 0.5f + padding_h);
		textMesh->t_allign = TextAlignment::RIGHT;
		break;
	default:
		break;
	}
}

void TextBox::update()
{
	textMesh->text = text;
}

void TextBox::fixedUpdate()
{
}

void TextBox::destroy()
{
}


