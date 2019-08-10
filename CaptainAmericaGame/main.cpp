#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Debug.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game::GetInstance()->Run();

	return 0;
}