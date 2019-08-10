#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include <algorithm>
#include "Sprite.h"
#include "Animation.h"
#include "LoadTXT.h"
#include "CollideEvent.h"
#include "Collision.h"

class GameObject;
typedef GameObject *LPGAMEOBJECT;

struct Tile;
struct Tile2;

typedef vector<Tile> Row;
typedef vector<Row> Matrix;

class GameObject
{

protected:
	float x;
	float y;

	float vx;
	float vy;

	float width;
	float height;

	float dt;

	bool isLeft;
	bool isFlipped;
	bool isFlipVertical;

	Collider collider;
public:
	bool disable;

	float disableTimeCount;

	void SetPositionX(float x) { this->x = x; }
	void SetPositionY(float y) { this->y = y; }

	void SetSpeedX(float vx) { this->vx = vx; }
	void SetSpeedY(float vy) { this->vy = vy; }

	float GetPositionX() { return this->x; }
	float GetPositionY() { return this->y; }
	float GetSpeedX() { return this->vx; }
	float GetSpeedY() { return this->vy; }

	int GetWidth() { return this->width; }
	int GetHeight() { return this->height; }

	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	RECT GetRect();

	void SetCollider(Collider col) { this->collider = col; }

	void UpdateObjectCollider();
	void UpdateTileCollider();

	void SetDt(float dt) { this->dt = dt; }
	float GetDt() { return dt; }

	Collider GetCollider() { return this->collider; }
	void MapCollisions(vector<Tile2 *> &tiles, vector<ColliedEvent*> &coEvents);

	bool IsCollide(GameObject *CollisionObject);

	void setIsLeft(bool isleft) { isLeft = isleft; }
	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? false : true; return isFlipped; }
	void setIsFlipDown(bool isFlip) { isFlipVertical = isFlip; }
	bool IsFlipDown() { return isFlipVertical; }

	GameObject();
	GameObject(float x, float y, float width, float height);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void OnCollision() { this->disable = true; }
	~GameObject();
};

