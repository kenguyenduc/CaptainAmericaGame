#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Item.h"

class Bullet;
class SpawnProjectTile
{
private:
	static SpawnProjectTile* _instance;
public:
	static SpawnProjectTile* GetInstance();

	vector<Bullet*> listBullet;

	void SpawnBullet(float x, float y, int direction, BulletType type);
	void UpdateBullet(DWORD dt);
	void RenderBullet();

	vector<Item*> listItem;

	void SpawnItem(float x, float y, ItemType type);
	void UpdateItem(DWORD dt);
	void RenderItem();
};