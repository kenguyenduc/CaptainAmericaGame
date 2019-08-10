#pragma once
#include "GameObject.h"
#include "BatState.h"
#include "Constants.h"
#include "Game.h"
#include "State.h"

enum BatType {
	BAT_NORMAL,
	BAT_CAPSULE,
};

class Bat : public GameObject
{
	Bat();

	static Bat *__instance;

	State *state;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

	BatType type;

public:
	Bat(float x, float y, BatType type);
	static void LoadResources();

	bool isOnGround = false;

	static Bat *GetInstance();

	BatType GetType() { return this->type; }

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