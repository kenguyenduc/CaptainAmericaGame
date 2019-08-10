#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Graphics.h"

struct SpriteData {
	int width;
	int height;
	float x;
	float y;
	float scale = 1;
	float angle = 0;
	bool isLeft = false;
	bool isFlipped = false;
	bool isFlipVertical = false;

	SpriteData(float iX = 0, float iY = 0, int iWidth = 1, int iHeight = 1)
	{
		x = iX;
		y = iY;
		width = iWidth;
		height = iHeight;
		scale = 1;
		angle = 0;
	}
};
class Sprite
{
	int width;
	int height;
	float x;
	float y;
	float offsetX;
	float offsetY;
	float scale;
	float angle;
	bool flipHorizontal;
	bool flipVertical;

	RECT rect;
	LPDIRECT3DTEXTURE9 texture;
public:
	Sprite(LPCWSTR filePath, RECT rect, D3DCOLOR transColor);

	void SetTexture(LPCWSTR filePath, D3DCOLOR transColor);
	void SetRect(RECT rect);
	void SetData(SpriteData spriteData);

	LPDIRECT3DTEXTURE9 GetTexture() { return texture; };
	RECT GetRect() { return rect; };
	float GetAngle() { return angle; };
	D3DXVECTOR2 GetCenter();
	D3DXVECTOR2 GetOffset();
	void SetOffSetX(float x) { offsetX = x; }
	void SetOffSetY(float y) { offsetY = y; }
	D3DXVECTOR2 GetTranslate();
	D3DXVECTOR2 GetScaling();
};

