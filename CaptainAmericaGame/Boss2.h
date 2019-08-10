#pragma once
#include "GameObject.h"
#include "Boss2State.h"
#include "Constants.h"
#include "Game.h"
#include "Constants.h"
#include "SpawnProjectTile.h"
#include "State.h"

class Boss2 : public GameObject
{
	Boss2();

	static Boss2 *__instance;

	State *state;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

public:
	static void LoadResources();

	static Boss2 *GetInstance();

	DWORD GetLastFrameTime() { return this->lastFrameTime; }
	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }

	void SetColliderDemension(float width, float height)
	{
		this->collider.width = width;
		this->collider.height = height;
	}

	vector<Animation *> GetAnimationsList() { return animations; }

	void Update(DWORD dt) override;

	void Render() override;
};