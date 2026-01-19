#include "../../BaseSystems_WZBJ_Pak.hpp"

bool Button::CheckClick(AEVec2 mousePos) const
{
	if (mousePos.x >= m_Position.x - width * 0.5f && mousePos.x <= m_Position.x + width * 0.5f)
	{
		if (mousePos.y >= m_Position.y - height * 0.5f && mousePos.y <= m_Position.y + height * 0.5f)
		{
			return true;
		}
	}
	return false;
}

void Button::OnClick(void)
{
	if (OnClickFunction)
	{
		OnClickFunction();
	}
}

void Button::SetButtonImage(Sprite _sprite)
{
	m_ButtonBackground = _sprite;
}

void Button::SetButtonText(const char* text)
{
	m_ButtonText = text;
}

void Button::SetButtonPosition(AEVec2 pos)
{
	m_Position = pos;
}

void Button::Render(void)
{
	/*CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(m_ButtonBackground, m_Position.x, m_Position.y, width, height, 255);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_Fill(textColor);
	CP_Settings_TextSize(30);
	CP_Font_DrawText(m_ButtonText, m_Position.x, m_Position.y);*/
	this->Update();
}


void Button::Update(void)
{
	/*if (CP_Input_MouseClicked() && CheckClick(CP_Vector_Set(CP_Input_GetMousePreviousX(), CP_Input_GetMousePreviousY())))
	{
		OnClick();
	}*/

	//OnHover
	/*if (CheckClick(CP_Vector_Set(CP_Input_GetMousePreviousX(), CP_Input_GetMousePreviousY())))
	{
		if (hoverBuffer)
		{
			CP_Sound_StopGroup(CP_SOUND_GROUP_3);
			AudioManager::GetInstance()->Play(SOUND_ID::SFX_BUTTONHOVER);
			hoverBuffer = false;
		}
		width = fixedWidth * 1.25f;
		height = fixedHeight * 1.25f;
	}
	else
	{
		hoverBuffer = true;
		width = fixedWidth;
		height = fixedHeight;
	}*/
}

//Button::Button():m_ButtonBackground(NULL),m_ButtonText("Text"),m_Position(CP_Vector_Zero()),
//width(100),height(50),fixedHeight(height), fixedWidth(width), hoverBuffer(false), textColor(CP_Color_CreateHex(0xFFFFFFFF)){};

//Button::Button(AEVec2 pos, float width, float height, const char* text, Color4 textColor):m_ButtonBackground(NULL),hoverBuffer(false)
//{
//	m_Position = pos;
//	this->width = width;
//	this->height = height;
//	fixedHeight = height;
//	fixedWidth = width;
//	m_ButtonText = text;
//	this->textColor = textColor;
//}

Button::~Button()
{
	//CP_Image_Free(m_ButtonBackground);
}