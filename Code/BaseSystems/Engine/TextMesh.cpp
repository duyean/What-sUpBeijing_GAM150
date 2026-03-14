#include "TextMesh.hpp"

TextMesh::TextMesh()
{
	color = {0,0,0,255};
	pos = {0, 0};
	size = 1;
	text = "text";
	font = "liberi";
	padding = 1.f;
	t_allign = TextAlignment::LEFT;
	tl_allign = TextLineAllignment::TOP;
}

TextMesh::TextMesh(AEVec2 _pos, float _size, const char* _text, TextAlignment _allign)
	: pos(_pos), size(_size), text(_text), t_allign(_allign)
{	
	font = "liberi";
	padding = 1.f;
	tl_allign = TextLineAllignment::TOP;
}

TextMesh::TextMesh(AEVec2 _pos, float _size, const char* _text, Color _color, TextAlignment _allign)
	: pos(_pos), size(_size), text(_text), color(_color), t_allign(_allign)
{
	font = "liberi";
	padding = 1.f;
	tl_allign = TextLineAllignment::TOP;
}


void TextMesh::ReadText(const char* _text)
{
	if (!lines.empty())
		lines.clear();

	std::string copy = _text;
	int start = 0;

	for (int i = 0; i < copy.size(); ++i)
	{
		if (copy[i] == '\n')
		{
			std::string newStr = copy.substr(start, i - start);
			lines.push_back(newStr);
			start = i + 1;
		}
	}
	lines.push_back(copy.substr(start));
}

void TextMesh::awake()
{
	
}

void TextMesh::init()
{	
	ReadText(text);
}

void TextMesh::update()
{
	ReadText(text);
	AEVec2 normalised = { pos.x / (AEGfxGetWindowWidth() / 2.f), pos.y / (AEGfxGetWindowHeight() / 2.f) };
	for (size_t i = 0; i < lines.size(); i++)
	{
		f32 width, height;
		AEGfxGetPrintSize(MeshGen::getInstance().GetFontID(font), lines[i].c_str(), size, &width, &height);

		switch (tl_allign)
		{
		case TextLineAllignment::TOP:
			MeshGen::getInstance().DrawFont(normalised.x, normalised.y - (i * height) - (i * padding * 0.01f), size, Color{ 255,255,255,1 }, lines[i].c_str(), font, t_allign);
			break;
		case TextLineAllignment::CENTER:
			MeshGen::getInstance().DrawFont(normalised.x, normalised.y - (i * height) - (i * padding * 0.01f) + (lines.size() * height * 0.5), size, Color{ 255,255,255,1 }, lines[i].c_str(), font, t_allign);
			break;
		case TextLineAllignment::BOTTOM:
			MeshGen::getInstance().DrawFont(normalised.x, normalised.y - (i * height) - (i * padding * 0.01f) + (lines.size() * height), size, Color{ 255,255,255,1 }, lines[i].c_str(), font, t_allign);
			break;
		default:
			break;
		}
		
	}
}

void TextMesh::fixedUpdate()
{
	
}

void TextMesh::destroy()
{
	
}





