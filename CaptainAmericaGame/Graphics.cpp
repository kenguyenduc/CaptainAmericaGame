#include "Graphics.h"
#include "Debug.h"

Graphics *Graphics::__instance = NULL;
Viewport *Graphics::viewport = NULL;
//Khởi tạo Graphics chính
void Graphics::Init(HWND hWnd)
{
	//Khởi tạo đối tượng Direct3D9
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	//Gán biến xử lí cửa sổ
	this->hWnd = hWnd;
	//Tạo biến thông số khởi tạo thiết bị
	D3DPRESENT_PARAMETERS d3dpp;
	//Reset thông số của d3dpp
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	//Thêm các thông số của d3dpp
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	//Lấy cửa sổ chương trình
	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 
	//Thêm thông số kích cỡ backbuffer
	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;
	//Khởi tạo đối tượng thiết bị Direct3D9
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);
	//Kiểm tra lỗi khi khởi tạo
	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}
	//Lấy thông tin backbuffer
	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	//Khởi tạo sprite handler
	D3DXCreateSprite(d3ddv, &spriteHandler);

	viewport = Viewport::GetInstance();
	//In ra khởi tạo Graphics thành công
	OutputDebugString(L"[INFO] InitGraphics done;\n");
}
//Load textures
HRESULT Graphics::LoadTexture(LPCWSTR filePath, D3DCOLOR transColor, LPDIRECT3DTEXTURE9 &texture)
{
	if (filePath == NULL)
	{
		texture = NULL;
		return D3DERR_INVALIDCALL;
	}
	HRESULT result;
	//Thông tin texture
	D3DXIMAGE_INFO info;
	//Lấy thông tin texture từ đường dẫn file
	result = D3DXGetImageInfoFromFile(filePath, &info);
	//Kiểm tra lỗi khi lấy thông tin
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return result;
	}
	//Tạo texture từ đường dẫn file
	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		transColor,
		&info,
		NULL,
		&texture);								// Created texture pointer
	//Kiểm tra lỗi khi tạo
	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return result;
	}

	DebugOut(L"[INFO] Texture loaded Ok: %s \n", filePath);
	return result;
}
//Hàm vẽ
void Graphics::Draw(Sprite *sprite, D3DCOLOR color)
{
	if (sprite->GetTexture() == NULL)
		return;

	D3DXVECTOR2 center = sprite->GetCenter();
	D3DXVECTOR3 offset = D3DXVECTOR3(sprite->GetOffset().x, sprite->GetOffset().y, 0);//D3DXVECTOR3(center.x, center.y, 0);
	D3DXVECTOR2 translate = sprite->GetTranslate();
	D3DXVECTOR2 scaling = sprite->GetScaling();
	viewport->SetRenderData(center, translate, scaling);



	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,
		NULL,
		0.0f,
		&scaling,
		NULL,
		sprite->GetAngle(),
		&translate
	);

	spriteHandler->SetTransform(&matrix);
	spriteHandler->Draw(sprite->GetTexture(), &(sprite->GetRect()), &offset, NULL, color);
}
//Hàm hủy Graphics chính
Graphics::~Graphics()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}
//Hàm lấy đối tượng
Graphics *Graphics::GetInstance()
{
	if (__instance == NULL) __instance = new Graphics();
	return __instance;
}
