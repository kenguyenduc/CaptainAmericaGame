#include "GameObject.h"
#include "Game.h"

GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = 0;
	collider.height = 0;
}
GameObject::GameObject(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	vx = vy = 0;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = width;
	collider.height = height;
}

GameObject::~GameObject()
{
}

//Hàm cập nhật
void GameObject::Update(DWORD dt)
{
}
//Hàm render
void GameObject::Render()
{

}

void GameObject::MapCollisions(vector<Tile2 *> &tiles, vector<ColliedEvent*> &coEvents)
{
	Collider tileCollider;
	tileCollider.width = TILE_SIZE;
	tileCollider.height = TILE_SIZE;
	for (int i = 0; i < tiles.size(); i++)
	{
		tileCollider.x = tiles[i]->x * TILE_SIZE;
		tileCollider.y = tiles[i]->y * TILE_SIZE - TILE_SIZE / 2;

		if (tiles[i]->type == ObjectType::BRICK)
		{
			float time;
			float normalX;
			float normalY;

			time = Collision::GetInstance()->SweptAABB(this->GetCollider(), tileCollider, normalX, normalY);

			if (time >= 0 && time < 1.0f && normalY == 1)
			{
				coEvents.push_back(new ColliedEvent(EVENT_BRICK, time, normalX, normalY));
			}
		}
		else if (tiles[i]->type == ObjectType::WALL)
		{
			float time;
			float normalX;
			float normalY;

			time = Collision::GetInstance()->SweptAABB(this->GetCollider(), tileCollider, normalX, normalY);

			if (time >= 0 && time < 1.0f)
			{
				//trường hợp normalY = -1 không được
				if (normalX == 1 || normalX == -1 || normalY == -1)
					coEvents.push_back(new ColliedEvent(EVENT_WALL, time, normalX, normalY));
			}
		}
		else if (tiles[i]->type == ObjectType::THORN)
		{
			float time;
			float normalX;
			float normalY;

			time = Collision::GetInstance()->SweptAABB(this->GetCollider(), tileCollider, normalX, normalY);

			if (time >= 0 && time < 1.0f && normalY == 1)
			{
				coEvents.push_back(new ColliedEvent(EVENT_THORN, time, normalX, normalY));
			}
		}
		else if (tiles[i]->type == ObjectType::RIVER)
		{
			float time;
			float normalX;
			float normalY;

			time = Collision::GetInstance()->SweptAABB(this->GetCollider(), tileCollider, normalX, normalY);

			if (time >= 0 && time < 1.0f && normalY == 1)
			{
				coEvents.push_back(new ColliedEvent(EVENT_WATER, time, normalX, normalY));
			}
		}
		else if (tiles[i]->type == ObjectType::ROPE_SWING)
		{
			float topCaptainEdge = this->collider.y;
			float topRope = tileCollider.y;

			float distance = topCaptainEdge - topRope;

			if (distance < 16 && distance > 0 && abs(this->collider.x - tileCollider.x) < 16)
				int a = 0;

			//time = Collision::GetInstance()->SweptAABB(this->GetCollider(), tileCollider, normalX, normalY);
			bool isCollide = Collision::GetInstance()->AABB(this->collider, tileCollider);

			if (isCollide)
				int a = 0;

			if (isCollide && distance < 13 && distance > 0)
			{
				coEvents.push_back(new ColliedEvent(EVENT_ROPE_SWING));
			}
		}
	}
}
//
//void GameObject::CalcPotentialMapCollisions(
//	vector<Tile *> &tiles,
//	vector<ColliedEvent*> &coEvents)
//{
//	LPGAMEOBJECT solidTileDummy = new GameObject(0, 0, 16, 16);
//	for (int i = 0; i < tiles.size(); i++)
//	{
//		Tile *curTile = tiles[i];
//		solidTileDummy->SetPositionX(curTile->x);
//		solidTileDummy->SetPositionY(curTile->y);
//		solidTileDummy->UpdateTileCollider();
//
//		if (curTile->type == ObjectType::BRICK || curTile->type == ObjectType::BRICK_NOCOLLISION_BOTTOM)
//		{	
//			ColliedEvent* e = SweptAABBEx(solidTileDummy);
//			e->collisionID = 1;
//
//			if (e->t >= 0 && e->t < 1.0f && e->ny == 1)
//			{
//				coEvents.push_back(e);
//			}
//			else
//			{
//				delete e;
//			}
//		}
//		else if (curTile->type == ObjectType::RIVER)
//		{
//			ColliedEvent* e = SweptAABBEx(solidTileDummy);
//			e->collisionID = 2;
//
//			if (e->t >= 0 && e->t < 1.0f && e->ny == 1)
//			{
//				coEvents.push_back(e);
//			}
//			else
//			{
//				delete e;
//			}
//		}
//	}
//}

//New
//void GameObject::CalcPotentialCollisions(
//	vector<Tile2 *> &tiles,
//	vector<LPCOLLISIONEVENT> &coEvents)
//{
//	UpdateObjectCollider();
//	CalcPotentialMapCollisions(tiles, coEvents);
//
//	sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);
//}

bool GameObject::IsCollide(GameObject *CollisionObject)
{
	Collider MainObject = this->collider;
	RECT rec;
	rec.top = MainObject.y;
	rec.left = MainObject.x;
	rec.right = MainObject.x + MainObject.width;
	rec.bottom = MainObject.y - MainObject.height;

	Collider TargetObject = CollisionObject->collider;
	if (MainObject.direction == 1)
	{
		if (TargetObject.x > rec.left && TargetObject.x < rec.right)
		{
			if ((rec.top < TargetObject.y && rec.top > TargetObject.y - TargetObject.height)
				|| (rec.top > TargetObject.y && rec.bottom < TargetObject.y))
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else if (MainObject.direction == -1)
	{
		if (TargetObject.x + TargetObject.width > rec.left && TargetObject.x + TargetObject.width < rec.right)
		{
			if ((rec.top < TargetObject.y && rec.top > TargetObject.y - TargetObject.height)
				|| (rec.top > TargetObject.y && rec.bottom < TargetObject.y))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return false;
}

void GameObject::UpdateObjectCollider()
{
	int direction = (isLeft == true) ? -1 : 1;
	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.dt = dt;
	collider.direction = direction;
}

void GameObject::UpdateTileCollider()
{
	collider.x = x;
	collider.y = y - 8;
	collider.vx = vx;
	collider.vy = vy;
	collider.dt = dt;
	collider.height = 8;
}
RECT GameObject::GetRect()
{
	RECT rect;
	rect.top = y;
	rect.left = x;
	rect.right = x + width;
	rect.bottom = y - height;
	return rect;
}