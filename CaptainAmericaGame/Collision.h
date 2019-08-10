#pragma once
#include <math.h>
#include <vector>
#include "CollideEvent.h"

using namespace std;

struct Collider
{
	float x, y;
	float width, height;
	float vx = 0, vy = 0;
	float dt = 0;
	int direction;
};

class Collision
{
private:
	static Collision* _instance;

public:
	static Collision* GetInstance();

	bool AABB(const Collider &c1, const Collider &c2);
	Collider GetSweptBroadphaseRect(const Collider &object);
	float SweptAABB(Collider c1, Collider c2, float &normalx, float &normaly);
	void FilterCollision(vector<ColliedEvent*> &coEvents, vector<ColliedEvent*> &coEventsResult,
		float &min_tx, float &min_ty, float &nx, float &ny);
};