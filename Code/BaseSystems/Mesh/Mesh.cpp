#pragma once
#include "MeshClass.hpp"

AEGfxVertexList* Mesh::FilledCircle(int sides)
{
	AEGfxMeshStart();

	for (int i = 0; i <= sides; i++)
	{
		float angle1 = i * 2 * PI / sides;
		float angle2 = (i + 1) * 2 * PI / sides;
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f,
			cosf(angle1), sinf(angle1), 0xFFFFFFFF, 0.0f, 0.0f,
			cosf(angle2), sinf(angle2), 0xFFFFFFFF, 0.0f, 0.0f
		);
	}

	return AEGfxMeshEnd();
}

AEGfxVertexList* Mesh::LeftCenterRectangle()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		0, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		1, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		1, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		1, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		0, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	return AEGfxMeshEnd();

}

void Mesh::Draw()
{
	AEGfxSetRenderMode(renderMode);
	AEGfxSetColorToMultiply(color.r, color.g, color.b, color.a);
	AEGfxSetBlendMode(blendMode);
	AEGfxSetTransparency(opacity);
	UpdateTransform();
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(baseMesh, AE_GFX_MDM_TRIANGLES);
}

void Mesh::SetMesh(AEGfxVertexList* mesh)
{
	baseMesh = mesh;
}

void Mesh::SetRenderMode(AEGfxRenderMode mode)
{
	renderMode = mode;
}

void Mesh::SetBlendMode(AEGfxBlendMode mode)
{
	blendMode = mode;
}

void Mesh::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Mesh::Move(float x, float y)
{
	position.x += x;
	position.y += y;
}

void Mesh::SetScale(float x, float y)
{
	AEMtx33Scale(&scale, x, y);
}

void Mesh::SetRotation(float angleInDegrees)
{
	AEMtx33Rot(&rotation, angleInDegrees * PI / 180);
}

void Mesh::UpdateTransform()
{
	AEMtx33 pos = { 0 };
	AEMtx33Trans(&pos, position.x + offset.x, position.y + offset.y);
	AEMtx33Concat(&transform, &rotation, &scale);
	AEMtx33Concat(&transform, &pos, &transform);
}

void Mesh::SetColor(Color4 col)
{
	color = col;
}

Mesh::Mesh()
{
	position = offset = { 0 };
	scale = transform = { 0 };
	AEMtx33Identity(&rotation);
	opacity = 1;
	color = Color4(1.f, 1.f, 1.f, 1.f);
	baseMesh = nullptr;
	//set default render mode to color
	renderMode = AE_GFX_RM_COLOR;
	//set default blend mode to blend
	blendMode = AE_GFX_BM_BLEND;
}

Mesh::~Mesh()
{

}