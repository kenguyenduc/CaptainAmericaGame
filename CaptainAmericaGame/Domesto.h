#pragma once
#include "GameObject.h"
#include "DomestoStayState.h"
#include "DomestoWalkState.h"
#include "Constants.h"
#include "Game.h"
#include "SpawnProjectTile.h"
#include "State.h"

enum DemestoType
{
	STAY_FIRE_STRAIGHT,
	WALK_FIRE_STAIGHT,
};



class Domesto : public GameObject
{
	Domesto();

	static Domesto *__instance;

	State *state;
	DemestoType type;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

	bool isGrounded = false;
public:
	Domesto(float x, float y, DemestoType type = STAY_FIRE_STRAIGHT);
	static void LoadResources();

	static Domesto *GetInstance();

	DWORD GetLastFrameTime() { return this->lastFrameTime; }
	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }

	void SetIsGrounded(bool isGrounded) { this->isGrounded = isGrounded; }
	bool IsGrounded() { return isGrounded; }

	void SetColliderDemension(float width, float height)
	{
		this->collider.width = width;
		this->collider.height = height;
	}

	vector<Animation *> GetAnimationsList() { return animations; }

	DemestoType GetType() { return type; }

	void Update(DWORD dt) override;

	void Render() override;

	void OnCollision();
};