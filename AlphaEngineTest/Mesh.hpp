#pragma once
#include "AEEngine.h"

struct Color4
{
	float r;
	float g;
	float b;
	float a;

	Color4() { r = g = b = a = 1.f; }
	Color4(float r, float g, float b, float a) { this->r = r; this->g = g; this->b = b; this->a = a; }
};

class Mesh
{
public:
	AEGfxVertexList* baseMesh;
	AEGfxVertexList* FilledCircle(int sides);
	AEGfxVertexList* LeftCenterRectangle();

	AEVec2 position;
	AEVec2 offset;
	AEMtx33 scale;
	AEMtx33 rotation;
	AEMtx33 transform;
	AEGfxRenderMode renderMode;
	AEGfxBlendMode blendMode;
	Color4 color;
	float opacity;

	void SetRenderMode(AEGfxRenderMode mode);
	void SetBlendMode(AEGfxBlendMode mode);
	void Draw();
	void SetPosition(float x, float y);
	void Move(float x, float y);
	void SetScale(float x, float y);
	void SetRotation(float angle);
	void SetMesh(AEGfxVertexList* mesh);
	void SetColor(Color4 col);
	void UpdateTransform();
	Mesh();
	~Mesh();

	Mesh& operator=(const Mesh& other) 
	{
		if (this != &other)
		{
			baseMesh = other.baseMesh;
			scale = other.scale;
			position = other.position;
			color = other.color;
			opacity = other.opacity;
			rotation = other.rotation;
		}
		return *this;
	}

};