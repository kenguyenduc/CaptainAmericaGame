#pragma once
#include "GameObject.h"

class Shield : public GameObject
{
	vector<Animation *> animations;
	static Shield * __instance;

	int state;

	bool isStartThrow = true;

	bool isReturn = true;

	bool isCaptainLeft;

	float maxDistance;

	float distance;
public:
	Shield();

	bool isFlying = false;

	bool IsFlying() { return this->isFlying; }
	void SetIsFlying(bool isFlying) { this->isFlying = isFlying; }

	static Shield * GetInstance();

	void LoadResources();

	void ShieldFlying();

	void Update(DWORD dt);
	void Render();

	float GetDistance() { return this->distance; }

	~Shield();
};

