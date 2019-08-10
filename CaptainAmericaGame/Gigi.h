#pragma once
#include "GameObject.h"
#include "GigiState.h"
#include "Constants.h"
#include "Game.h"
#include "SpawnProjectTile.h"
#include "State.h"

class Gigi : public GameObject
{
	Gigi();

	static Gigi *__instance;

	State *state;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

public:
	Gigi(float x, float y);
	static void LoadResources();

	bool isOnGround = false;

	float posx, posy;

	static Gigi *GetInstance();

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

	void OnCollision();
};