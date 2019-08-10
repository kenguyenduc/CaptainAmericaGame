#pragma once
#include "d3d9.h"
#include "Keyboard.h"

class Captain;
class State
{
public:
	State();
	virtual void KeyHandle(); //Hàm xử lý khi có phím thay đổi (chạy trước update)
	virtual void Colision(); //Hàm xử lý khi có va chạm (chạy trước update)
	virtual void Update(DWORD dt);
	virtual void Render();
};