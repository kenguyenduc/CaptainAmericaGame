#include "Sprite.h"

Sprite::Sprite(LPCWSTR filePath, RECT rect, D3DCOLOR transColor)
{
	width = 0;
	height = 0;
	x = 0;
	y = 0;
	offsetX = 0;
	offsetY = 0;
	scale = 1;
	angle = 0;
	flipHorizontal = false;
	flipVertical = false;

	SetTexture(filePath, transColor);
	SetRect(rect);
}
void Sprite::SetTexture(LPCWSTR filePath, D3DCOLOR transColor)
{
	HRESULT result = Graphics::GetInstance()->LoadTexture(filePath, transColor, this->texture);

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] Sprite's texture loading failed\n");
		return;
	}
}
void Sprite::SetData(SpriteData spriteData)
{
	width = spriteData.width;
	height = spriteData.height;
	x = spriteData.x;
	y = spriteData.y;
	scale = spriteData.scale;
	angle = spriteData.angle;

	if (spriteData.isFlipped)
		flipHorizontal = true;
	else
		flipHorizontal = false;

	if (spriteData.isFlipVertical)
		flipVertical = true;
	else
		flipVertical = false;
}
void Sprite::SetRect(RECT rect)
{
	this->rect = rect;
}
D3DXVECTOR2 Sprite::GetCenter()
{
	float x = ((float)this->width / 2 + offsetX) * this->scale;
	float y = ((float)this->height / 2 + offsetY)* this->scale;
	if (flipHorizontal)
	{
		x -= (float)this->width * this->scale;
	}
	if (flipVertical)
	{
		y -= (float)this->height * this->scale;
	}
	return D3DXVECTOR2(x, y);
}
D3DXVECTOR2 Sprite::GetOffset()
{
	float x = offsetX;
	float y = offsetY;

	//x = flipHorizontal ? (float)this->width - x : x;
	//y = flipVertical ? (float)this->height - y : y;

	return D3DXVECTOR2(x, y);
}
D3DXVECTOR2 Sprite::GetTranslate()
{
	float x = (float)this->x;
	float y = (float)this->y;
	if (flipHorizontal)
	{
		x += (float)this->width * this->scale;
	}
	if (flipVertical)
	{
		y += (float)this->height * this->scale;
	}
	return D3DXVECTOR2(x, y);
}
D3DXVECTOR2 Sprite::GetScaling()
{
	float x = (float)this->scale;
	float y = (float)this->scale;
	if (flipHorizontal)
	{
		x *= -1;
	}
	if (flipVertical)
	{
		y *= -1;
	}
	return D3DXVECTOR2(x, y);
}
