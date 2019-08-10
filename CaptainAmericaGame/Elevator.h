#pragma once
#include "GameObject.h"
#include "Constants.h"
#include "Game.h"

enum ElevatorType
{
	CIRCLE, //di chuyển vòng tròn
	SLASH, //di chuyển chéo lên xuống
	HORIZONTAL, // di chuyển qua lại
};

class Elevator : public GameObject
{
	Elevator();

	static Elevator *__instance;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

	ElevatorType type;

public:
	Elevator(float x, float y, ElevatorType type);
	static void LoadResources();

	float timeCount;
	float posx, posy;

	static Elevator *GetInstance();

	DWORD GetLastFrameTime() { return this->lastFrameTime; }
	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }

	void SetColliderDemension(float width, float height)
	{
		this->collider.width = width;
		this->collider.height = height;
	}

	vector<Animation *> GetAnimationsList() { return animations; }

	ElevatorType GetElevatorType() { return type; }

	void fly_circle();
	void fly_slash();
	void fly_horizontal();

	void Update(DWORD dt) override;

	void Render() override;

	void OnCollision();
};