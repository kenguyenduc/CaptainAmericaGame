#include "Collision.h"

Collision* Collision::_instance;

Collision* Collision::GetInstance()
{
	if (_instance == nullptr)
		_instance = new Collision();
	return _instance;
}

bool Collision::AABB(const Collider &c1, const Collider &c2)
{
	return (
		c1.x < c2.x + c2.width &&
		c1.x + c1.width > c2.x &&
		c1.y > c2.y - c2.height &&
		c1.y - c1.height < c2.y
		);
	/*if (c1.x + c1.width < c2.x || c1.x > c2.x + c2.width ||
		c1.y + c1.height < c2.y || c1.y > c2.y + c2.height)
		return false;
	return true;*/
}

Collider Collision::GetSweptBroadphaseRect(const Collider &object)
{
	Collider broadphaseBox;
	broadphaseBox.x = object.vx == 0 ? object.x : object.x + object.vx * object.dt;
	broadphaseBox.y = object.vy < 0 ? object.y : object.y + object.vy * object.dt;
	broadphaseBox.width = object.width + abs(object.vx * object.dt);
	broadphaseBox.height = object.height + abs(object.vy * object.dt);

	return broadphaseBox;
}

float Collision::SweptAABB(Collider c1, Collider c2, float &normalx, float &normaly)
{
	float dxEntry, dyEntry;
	float dxExit, dyExit;

	c1.vx = c1.vx - c2.vx;
	c1.vy = c1.vy - c2.vy;

	float dx = c1.vx * c1.dt;
	float dy = c1.vy * c1.dt;


	Collider broadphaseBox = GetSweptBroadphaseRect(c1);
	if (!AABB(broadphaseBox, c2))
	{
		return 1.0f;
	}
	if (dx > 0.0f)
	{
		dxEntry = c2.x - (c1.x + c1.width);
		dxExit = (c2.x + c2.width) - c1.x;
	}
	else
	{
		dxEntry = (c2.x + c2.width) - c1.x;
		dxExit = c2.x - (c1.x + c1.width);
	}

	if (dy > 0.0f)
	{
		dyEntry = (c2.y - c2.height) - c1.y;
		dyExit = c2.y - (c1.y - c1.height);
	}
	else
	{
		dyEntry = c2.y - (c1.y - c1.height);
		dyExit = (c2.y - c2.height) - c1.y;
	}

	float txEntry, tyEntry;
	float txExit, tyExit;

	if (dx == 0)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / dx;
		txExit = dxExit / dx;
	}

	if (dy == 0)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / dy;
		tyExit = dyExit / dy;
	}

	float entryTime = std::fmax(txEntry, tyEntry);
	float exitTime = std::fmin(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else
	{
		if (txEntry > tyEntry)
		{
			if (dxEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else if (dxEntry > 0.0f)
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
			else
			{
				if (c1.x <= c2.x)
				{
					normalx = -1.0f;
					normaly = 0.0f;
				}
				else
				{
					normalx = 1.0f;
					normaly = 0.0f;
				}
			}
		}
		else
		{
			if (dyEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else if (dyEntry > 0.0f)
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
			else
			{
				if (c1.y <= c2.y)
				{
					normalx = 0.0f;
					normaly = -1.0f;
				}
				else
				{
					normalx = 0.0f;
					normaly = 1.0f;
				}
			}
		}
		return entryTime;
	}
}

// NEED FIX
void Collision::FilterCollision(
	vector<ColliedEvent*> &coEvents,
	vector<ColliedEvent*> &coEventsResult,
	float &min_tx, float &min_ty,
	float &nx, float &ny)
{
	if (coEvents.size() == 1)
	{
		min_tx = coEvents[0]->time;
	}

	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (int i = 0; i < coEvents.size(); i++)
	{
		ColliedEvent* c = coEvents[i];

		if (c->isAABBCollision)
		{
			coEventsResult.push_back(c);
			ny = 1;
			return;
		}


		//NEED FIX
		if (c->time < min_tx && c->nx != 0)
		{
			min_tx = c->time;
			nx = c->nx;
			min_ix = i;
		}

		if (c->time < min_ty  && c->ny != 0)
		{
			min_ty = c->time;
			ny = c->ny;
			min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}