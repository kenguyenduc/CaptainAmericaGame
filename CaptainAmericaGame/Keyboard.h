#pragma once
#include <dinput.h>

class Keyboard
{
	static Keyboard *__instance;
	//Đối tượng nhập xuất
	LPDIRECTINPUT8 Di8;
	//Thiết bị nhập xuất
	LPDIRECTINPUTDEVICE8 DiD8;
	//Buffer lưu dữ liệu lấy từ thiết bị
	char key_buffer[256];
	//Handle cửa sổ vẽ
	HWND Hwnd;

public:
	~Keyboard();
	//Cài đặt bàn phím
	bool InitKeyboard(HWND hwnd);
	//Lấy trạng thái bàn phím
	void Update();
	//Nhận diện phím nhấn
	bool IsKeyDown(int key);
	//Nhận diện phím nhả
	bool IsKeyUp(int key);
	//Hủy phím
	void KillKeyboard();
	//Lấy đối tượng
	static Keyboard *GetInstance();
};