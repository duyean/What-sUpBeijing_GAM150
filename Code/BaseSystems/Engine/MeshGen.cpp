#include "MeshGen.hpp"

float capToOne(float oldValue, float oldMin, float oldMax, float newMax, float newMin)
{
	return ((oldValue - oldMin) / (oldMax - oldMin)) * (newMax - newMin) + newMin;
}


void MeshGen::DrawBox(float Xpos, float Ypos, float width, float height, Color color, float Deg)
{
	AEMtx33 scale = { 1 };
	AEMtx33Scale(&scale, width, height);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, Deg * PI / 180.f);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, Xpos, Ypos);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	float red = capToOne(static_cast<float>(color.R), 0.f, 255.f, 1.f, 0.f);
	float green = capToOne(static_cast<float>(color.G), 0.f, 255.f, 1.f, 0.f);
	float blue = capToOne(static_cast<float>(color.B), 0.f, 255.f, 1.f, 0.f);
	AEGfxSetColorToMultiply(red, green, blue, 1.0f);
	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(color.A);

	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh.at("Box"), AE_GFX_MDM_TRIANGLES);

}

void MeshGen::DrawBoxTexture(float Xpos, float Ypos, float width, float height, Color color, float Deg, const char* fileName)
{
	AEMtx33 scale = { 1 };
	AEMtx33Scale(&scale, width, height);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, Deg * PI / 180.f);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, Xpos, Ypos);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	float red = capToOne(static_cast<float>(color.R), 0.f, 255.f, 1.f, 0.f);
	float green = capToOne(static_cast<float>(color.G), 0.f, 255.f, 1.f, 0.f);
	float blue = capToOne(static_cast<float>(color.B), 0.f, 255.f, 1.f, 0.f);
	AEGfxSetColorToMultiply(red, green, blue, 1.0f);
	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, color.A);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	//AEGfxSetTransparency(color.A);

	AEGfxTextureSet(pTex.at(fileName), 0, 0);

	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh.at("Box"), AE_GFX_MDM_TRIANGLES);
}

void MeshGen::DrawCircle(float Xpos, float Ypos, float width, float height, Color color)
{
	AEMtx33 scale = { 1 };
	AEMtx33Scale(&scale, width, height);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, Xpos, Ypos);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	float red = capToOne(static_cast<float>(color.R), 0.f, 255.f, 1.f, 0.f);
	float green = capToOne(static_cast<float>(color.G), 0.f, 255.f, 1.f, 0.f);
	float blue = capToOne(static_cast<float>(color.B), 0.f, 255.f, 1.f, 0.f);
	AEGfxSetColorToMultiply(red, green, blue, 1.0f);
	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(color.A);

	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh.at("Circle"), AE_GFX_MDM_TRIANGLES);

}

void MeshGen::DrawCircleTexture(float Xpos, float Ypos, float width, float height, Color color, const char* fileName)
{
	AEMtx33 scale = { 1 };
	AEMtx33Scale(&scale, width, height);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, Xpos, Ypos);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	float red = capToOne(static_cast<float>(color.R), 0.f, 255.f, 1.f, 0.f);
	float green = capToOne(static_cast<float>(color.G), 0.f, 255.f, 1.f, 0.f);
	float blue = capToOne(static_cast<float>(color.B), 0.f, 255.f, 1.f, 0.f);
	AEGfxSetColorToMultiply(red, green, blue, 1.0f);
	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(color.A);

	AEGfxTextureSet(pTex.at(fileName), 0, 0);

	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh.at("Circle"), AE_GFX_MDM_TRIANGLES);
}


//Overloaded Draw
void MeshGen::DrawBox(AEVec2 position, AEVec2 scale, Color color, float Deg)
{
	AEMtx33 scale_l = { 1 };
	AEMtx33Scale(&scale_l, scale.x, scale.y);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, Deg * PI / 180.f);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, position.x, position.y);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale_l);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	float red = capToOne(static_cast<float>(color.R), 0.f, 255.f, 1.f, 0.f);
	float green = capToOne(static_cast<float>(color.G), 0.f, 255.f, 1.f, 0.f);
	float blue = capToOne(static_cast<float>(color.B), 0.f, 255.f, 1.f, 0.f);
	AEGfxSetColorToMultiply(red, green, blue, 1.0f);
	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(color.A);

	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh.at("Box"), AE_GFX_MDM_TRIANGLES);

}

void MeshGen::DrawBoxLeft(AEVec2 position, AEVec2 scale, Color color, float Deg)
{

	// --- Step 1: Scale Matrix ---
	AEMtx33 scale_l = { 0 };
	AEMtx33Scale(&scale_l, scale.x, scale.y);

	// --- Step 2: Rotation Matrix ---
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, Deg * PI / 180.0f);

	// --- Step 3: Translation Matrix ---
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, position.x, position.y);

	// --- Step 4: Pivot Offset ---
	// Move pivot from center to top-left (unit mesh centered at 0)
	AEMtx33 pivotOffset = { 0 };
	AEMtx33Trans(&pivotOffset, 0.5f, 0.5f); // +0.5 because mesh goes from -0.5 to 0.5

	// --- Step 5: Concatenate Matrices ---
	// Scale around pivot, then rotate, then translate
	AEMtx33 temp = { 0 };
	AEMtx33 transform = { 0 };

	AEMtx33Concat(&temp, &scale_l, &pivotOffset);  // scale * pivotOffset
	AEMtx33Concat(&transform, &rotate, &temp);   // rotate * (scale * pivotOffset)
	AEMtx33Concat(&transform, &translate, &transform); // translate last

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	float red = capToOne(static_cast<float>(color.R), 0.f, 255.f, 1.f, 0.f);
	float green = capToOne(static_cast<float>(color.G), 0.f, 255.f, 1.f, 0.f);
	float blue = capToOne(static_cast<float>(color.B), 0.f, 255.f, 1.f, 0.f);
	AEGfxSetColorToMultiply(red, green, blue, 1.0f);
	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(color.A);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh.at("Box"), AE_GFX_MDM_TRIANGLES);

}



void MeshGen::DrawBoxTexture(AEVec2 position, AEVec2 scale, Color color, float Deg, AEGfxTexture* texture)
{

	AEMtx33 scale_l = { 1 };
	AEMtx33Scale(&scale_l, scale.x, scale.y);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, Deg * PI / 180.f);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, position.x, position.y);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale_l);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	float red = capToOne(static_cast<float>(color.R), 0.f, 255.f, 1.f, 0.f);
	float green = capToOne(static_cast<float>(color.G), 0.f, 255.f, 1.f, 0.f);
	float blue = capToOne(static_cast<float>(color.B), 0.f, 255.f, 1.f, 0.f);
	AEGfxSetColorToMultiply(red, green, blue, 1.0f);
	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(color.A);

	AEGfxTextureSet(texture, 0, 0);

	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh.at("Box"), AE_GFX_MDM_TRIANGLES);
}

void MeshGen::DrawCircle(AEVec2 position, AEVec2 scale, Color color)
{
	AEMtx33 scale_l = { 1 };
	AEMtx33Scale(&scale_l, scale.x, scale.y);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, position.x, position.y);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale_l);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	float red = capToOne(static_cast<float>(color.R), 0.f, 255.f, 1.f, 0.f);
	float green = capToOne(static_cast<float>(color.G), 0.f, 255.f, 1.f, 0.f);
	float blue = capToOne(static_cast<float>(color.B), 0.f, 255.f, 1.f, 0.f);
	AEGfxSetColorToMultiply(red, green, blue, 1.0f);
	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(color.A);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh.at("Circle"), AE_GFX_MDM_TRIANGLES);

}

void MeshGen::DrawCircleTexture(AEVec2 position, AEVec2 scale, Color color, AEGfxTexture* texture)
{
	AEMtx33 scale_l = { 1 };
	AEMtx33Scale(&scale_l, scale.x, scale.y);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, position.x, position.y);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale_l);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	float red = capToOne(static_cast<float>(color.R), 0.f, 255.f, 1.f, 0.f);
	float green = capToOne(static_cast<float>(color.G), 0.f, 255.f, 1.f, 0.f);
	float blue = capToOne(static_cast<float>(color.B), 0.f, 255.f, 1.f, 0.f);
	AEGfxSetColorToMultiply(red, green, blue, 1.0f);
	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(color.A);

	AEGfxTextureSet(texture, 0, 0);

	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh.at("Circle"), AE_GFX_MDM_TRIANGLES);
}


AEGfxVertexList* MeshGen::getMesh(const char* fileName)
{
	return pMesh.at(fileName);
}

AEGfxTexture* MeshGen::getTexture(const char* fileName)
{
	return pTex.at(fileName);
}


void MeshGen::SetFont(const char* filePath, const char* fileName, int pixelSize)
{
	pFont.insert({ fileName, AEGfxCreateFont(filePath, pixelSize) });
}

void MeshGen::DrawFont(float Xpos, float Ypos, float scale, Color color, const char* text, const char* fileName)
{
	float red = capToOne(static_cast<float>(color.R), 0.f, 255.f, 1.f, 0.f);
	float green = capToOne(static_cast<float>(color.G), 0.f, 255.f, 1.f, 0.f);
	float blue = capToOne(static_cast<float>(color.B), 0.f, 255.f, 1.f, 0.f);
	AEGfxPrint(pFont.at(fileName),
		text,
		Xpos,
		Ypos,
		scale,
		red,
		green,
		blue,
		color.A);
}

void MeshGen::ClearFont(string name)
{
	AEGfxDestroyFont(pFont.at(name));
}

void MeshGen::ClearAllFont()
{
	for (auto const& pair : pFont)
	{
		AEGfxDestroyFont(pair.second);
	}

}


void MeshGen::CreateTexture(const char* filePath, const char* fileName)
{
	pTex.insert({ fileName, AEGfxTextureLoad(filePath) });
}

void MeshGen::CreateSpriteSheet(int column, int row, int fps, const char* fileName)
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1 / static_cast<float>(row),
		0.5f, -0.5f, 0xFFFFFFFF, 1 / static_cast<float>(column), 1 / static_cast<float>(row),
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1 / static_cast<float>(column), 1 / static_cast<float>(row),
		0.5f, 0.5f, 0xFFFFFFFF, 1 / static_cast<float>(column), 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	pMesh.insert({ fileName,  AEGfxMeshEnd() });
	//int r, int c, int cF, int fps, float cT
	sSprite.push_back({ new SpriteSheetMesh(row, column, 0, fps, 0.f) });
}

void MeshGen::CreateAnimatedSprite(float Xpos, float Ypos, float width, float height, float animationSpeed, int face, float Deg, Color color, const char* fileName)
{
	//use sMesh
	float timePerframe = 1.f / animationSpeed;

	if (timePerframe)
	{

	}
	AEMtx33 scale = { 1 };
	AEMtx33Scale(&scale, width, height);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, Deg * PI / 180.f);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, Xpos, Ypos);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);


	float red = capToOne(static_cast<float>(color.R), 0.f, 255.f, 1.f, 0.f);
	float green = capToOne(static_cast<float>(color.G), 0.f, 255.f, 1.f, 0.f);
	float blue = capToOne(static_cast<float>(color.B), 0.f, 255.f, 1.f, 0.f);
	AEGfxSetColorToMultiply(red, green, blue, static_cast<float>(color.A));
	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	AEGfxTextureSet(pTex.at(fileName), 0, 0);

	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMesh.at(fileName), AE_GFX_MDM_TRIANGLES);
}


void MeshGen::ClearMesh(string name)
{
	AEGfxMeshFree(pMesh.at(name));

}

void MeshGen::ClearTex(string name)
{
	AEGfxTextureUnload(pTex.at(name));
}

void MeshGen::ClearAllMesh()
{
	for (auto const& pair : pMesh)
	{
		AEGfxMeshFree(pair.second);
	}
	for (auto const& pair : pTex)
	{
		AEGfxTextureUnload(pair.second);
	}
}