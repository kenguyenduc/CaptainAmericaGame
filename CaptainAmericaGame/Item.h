#pragma once
#include "GameObject.h"

enum ItemType {
	FIVE_POINT,
	BIG_POWER_STONE,
	SMALL_POWER_STONE,
	BIG_ENERGY,
	SMALL_ENERGY,
	KEY_CRYSTAL
};

class GameObject;
class Item : public GameObject
{
private:
	static vector<Animation *> animations;

	ItemType type;

	float timeCount;



	int state;
public:
	Item(float x, float y, ItemType type);
	~Item();

	static void LoadResources();

	void Initialize(float x, float y, ItemType type);

	void SetItemType(ItemType type) { this->type = type; };
	ItemType GetItemType() { return this->type; }

	bool IsDisable() { return disable; }
	void Disable() { timeCount = 0; disable = true; }

	void Update(DWORD dt);
	void Render();

	bool disable;
};

