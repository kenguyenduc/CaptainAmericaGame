#pragma once

#ifndef _ANIMATION_H__
#define _ANIMATION_H__

#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Sprite.h"
#include "Graphics.h"
using namespace std;

class Animation
{
	DWORD lastFrameTime;
	DWORD defaultDelayTime;

	vector< pair<Sprite *, DWORD> > frames;
	int curFrame;
	bool done = false;
public:
	Animation(DWORD defaultDelayTime) { this->defaultDelayTime = defaultDelayTime; };

	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }
	DWORD GetLastFrameTime() { return this->lastFrameTime; }
	void SetCurFrame(int frame) { this->curFrame = frame; }
	int GetCurFrame() { return curFrame; }
	bool IsDone() { return done; }

	void Reset() { curFrame = -1; }
	void AddFrame(Sprite *sprite, DWORD time = 0);
	void Render(SpriteData spriteData);
};

#endif _ANIMATION_H__