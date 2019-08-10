#pragma once
struct ColliedEvent
{
	int collisionID;
	float time;
	float nx;
	float ny;
	bool isAABBCollision;
	ColliedEvent(int id)
	{
		this->collisionID = id;
		this->time = 0;
		this->nx = 0;
		this->ny = 1;
		this->isAABBCollision = true;
	}
	ColliedEvent(int id, float t, float nx, float ny)
	{
		this->collisionID = id;
		this->time = t;
		this->nx = nx;
		this->ny = ny;
		this->isAABBCollision = false;
	}
};