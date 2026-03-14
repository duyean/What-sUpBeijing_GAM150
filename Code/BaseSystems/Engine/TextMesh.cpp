#include "TextMesh.hpp"

TextMesh::TextMesh()
{
	color = {0,0,0,255};
	pos = {0, 0};
	size = 1;
	text = "text";
	font = "liberi";
}

TextMesh::TextMesh(AEVec2 _pos, double _size, const char* _text, TextAlignment _allign)
	: pos(_pos), size(_size), text(_text), allign(_allign)
{	
	font = "liberi";
}

TextMesh::TextMesh(AEVec2 _pos, double _size, const char* _text, Color _color, TextAlignment _allign)
	: pos(_pos), size(_size), text(_text), color(_color), allign(_allign)
{
	font = "liberi";
}

void TextMesh::awake()
{
	
}

void TextMesh::init()
{
	parent = entity->transform->parent;
}

void TextMesh::update()
{
	AEVec2 normalised = { pos.x / (AEGfxGetWindowWidth() / 2.f), pos.y / (AEGfxGetWindowHeight() / 2.f) };
	MeshGen::getInstance().DrawFont(normalised.x, normalised.y, size, color, text, font, allign);	

}

void TextMesh::fixedUpdate()
{
	
}

void TextMesh::destroy()
{
	
}





