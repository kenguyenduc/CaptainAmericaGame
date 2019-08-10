#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Viewport.h"
#include "Sprite.h"

class Sprite;

//Lớp Graphics chính
class Graphics
{
	static Graphics *__instance;
	static Viewport *viewport;
	HWND hWnd;									//Xử lí cửa sổ

	LPDIRECT3D9 d3d = NULL;						//Đối tượng Direct3D9
	LPDIRECT3DDEVICE9 d3ddv = NULL;				//Đối tượng thiết bị của Direct3D9

	LPDIRECT3DSURFACE9 backBuffer = NULL;		//Dùng surface cho backbuffer
	LPD3DXSPRITE spriteHandler = NULL;			//Xử lí sprite

public:
	//Khởi tạo Graphics chính
	void Init(HWND hWnd);
	//Load Texture
	HRESULT LoadTexture(LPCWSTR filePath, D3DCOLOR transColor, LPDIRECT3DTEXTURE9 &texture);
	//Vẽ các sprite lấy từ textures
	void Draw(Sprite *sprite, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	//Các hàm lấy thông tin cần thiết
	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }
	//Lấy đối tượng
	static Graphics *GetInstance();
	//Hàm hủy đối tượng
	~Graphics();
};