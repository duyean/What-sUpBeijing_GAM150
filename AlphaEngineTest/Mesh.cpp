#pragma once
#include "Mesh.h"

void Mesh::Draw()
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetColorToMultiply(color.r, color.g, color.b, color.a);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(opacity);
	//AEGfxSetColorToAdd(color.r, color.g, color.b, color.a);
	UpdateTransform();
	AEGfxSetTransform(transform.m);

	AEGfxMeshDraw(baseMesh, AE_GFX_MDM_TRIANGLES);
}

void Mesh::SetMesh(AEGfxVertexList* mesh)
{
	baseMesh = mesh;
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
}

Mesh::~Mesh()
{

}