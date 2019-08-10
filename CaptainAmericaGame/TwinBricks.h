#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Game.h"

enum TwinBricksState {
	TWIN_BRICK_IDLE,
	TWIN_BRICK_SEPERATE
};

class TwinBricks : public GameObject
{
	TwinBricks();

	static TwinBricks *__instance;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

	TwinBricksState state;

public:
	TwinBricks(float x, float y);
	static void LoadResources();

	float timeCount;

	//Lấy trạng thái
	TwinBricksState GetState() { return this->state; };
	//Set trạng thái
	void SetState(TwinBricksState state) { this->state = state; };

	static TwinBricks *GetInstance();

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