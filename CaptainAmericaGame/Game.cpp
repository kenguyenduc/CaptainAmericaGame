#include "Game.h"
#include "Debug.h"

Game *Game::__instance = NULL;
HINSTANCE Game::hInstance = NULL;
//Khởi tạo game chính
void Game::Init()
{
	hInstance = GetModuleHandle(NULL);

	this->hWnd = CreateGameWindow(hInstance, SCREEN_WIDTH, SCREEN_HEIGHT);

	graphics = Graphics::GetInstance();
	graphics->Init(hWnd);

	keyboard = Keyboard::GetInstance();
	keyboard->InitKeyboard(hWnd);

	this->stage = STAGE_1;
	LoadResources();
	OutputDebugString(L"[INFO] InitGame done;\n");
}
HWND Game::CreateGameWindow(HINSTANCE hInstance, int ScreenWidth, int ScreenHeight)
{
	//Lớp cửa sổ
	WNDCLASSEX wc;
	//Thông số lớp cửa sổ
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;
	//Đăng kí lớp cửa sổ
	RegisterClassEx(&wc);
	DWORD wflags = WS_OVERLAPPEDWINDOW;
	RECT rect;
	rect.left = rect.top = 0;
	rect.right = ScreenWidth;
	rect.bottom = ScreenHeight;
	AdjustWindowRect(&rect, wflags, false);
	//Tạo cửa sổ
	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			wflags, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			hInstance,
			NULL);
	//Kiểm tra lỗi khi tạo
	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}
	//Hiện cửa sổ lên màn hình
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	return hWnd;
}
void Game::LoadResources()
{
	if (NULL == tileMap2)
		tileMap2 = TileMap2::GetInstance();
	tileMap2->SetCurrentMap(this->stage);
	Grid2::GetInstance()->InitializeMapGrid(tileMap2);
	if (NULL == captain)
		captain = Captain::GetInstance();
	if (viewport == NULL)
		viewport = Viewport::GetInstance();



}

void Game::Update(DWORD dt)
{
	keyboard->Update();
	Grid2::GetInstance()->Update(dt);
	viewport->Update(dt);
}
void Game::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = graphics->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = graphics->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = graphics->GetSpriteHandler();
	if (SUCCEEDED(d3ddv->BeginScene()))
	{

		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		//grid->Render();
		Grid2::GetInstance()->Render();

		spriteHandler->End();

		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}
int Game::Run()
{
	if (!initialized)
	{
		Init();
		initialized = true;
	}
	//Tạo message
	MSG msg;
	int done = 0;
	//Thời gian frame hiện tại bắt đầu
	DWORD frameStart = GetTickCount();
	//Tính thời gian của mỗi frame xuất hiện trên màn hình
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;
	//Vòng lặp xử lí message
	while (!done)
	{
		//Tìm message thoát chương trình
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//Lấy giá trị thời gian hiện tại
		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		//Tính giá trị delta time = thời gian hiện tại - thời gian bắt đầu frame trước
		DWORD dt = now - frameStart;

		//Nếu dt > tickPerFram, hay đến lúc xử lí frame tiếp theo, bắt đầu Update và Render
		if (dt >= tickPerFrame)
		{
			frameStart = now;

			Update(dt);
			Render();
		}
		else //Ngược lại, chờ đến khi đủ thời gian xử lí frame tiếp theo
			Sleep(tickPerFrame - dt);
	}

	return 1;
}
Game::~Game()
{

}

Captain* Game::GetCaptain()
{
	return captain;
}

//Hàm lấy đối tượng
Game *Game::GetInstance()
{
	if (__instance == NULL) __instance = new Game();
	return __instance;
}

LRESULT CALLBACK Game::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0); //Nếu message là WM_DESTROY thì thoát
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}