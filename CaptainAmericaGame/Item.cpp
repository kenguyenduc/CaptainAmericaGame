#include "Item.h"
#include "Grid2.h"

vector<Animation *> Item::animations;

Item::Item(float x, float y, ItemType type)
{
	Initialize(x, y, type);
}

void Item::Initialize(float x, float y, ItemType type)
{
	this->type = type;

	this->state = ITEM_APPEAR;

	switch (type)
	{
	case FIVE_POINT:
	{
		width = FIVE_POINT_ITEM_WIDTH;
		height = FIVE_POINT_ITEM_HEIGHT;
	}
	break;
	case BIG_POWER_STONE:
	{
		width = BIG_POWER_STONE_WIDTH;
		height = BIG_POWER_STONE_HEIGHT;
	}
	break;
	case SMALL_POWER_STONE:
	{
		width = SMALL_POWER_STONE_WIDTH;
		height = SMALL_POWER_STONE_HEIGHT;
	}
	break;
	case BIG_ENERGY:
	{
		width = BIG_ENERGY_WIDTH;
		height = BIG_ENERGY_HEIGHT;
	}
	break;
	case SMALL_ENERGY:
	{
		width = SMALL_ENERGY_WIDTH;
		height = SMALL_ENERGY_HEIGHT;
	}
	break;
	case KEY_CRYSTAL:
	{
		width = KEY_CRYSTAL_WIDTH;
		height = KEY_CRYSTAL_HEIGHT;
	}
	break;
	}

	vy = -CAPTAIN_GRAVITY;

	this->x = x;
	this->y = y;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = vy;
	collider.width = this->width;
	collider.height = this->height;

	this->disable = false;

	this->SetSpeedY(CAPTAIN_JUMP_SPEED_Y);
}

void Item::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");

	// FIVE POINT APPEAR
	Animation * anim = new Animation(50);
	for (int i = 59; i < 60; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// FIVE POINT ALMOST DISAPPEAR
	anim = new Animation(50);
	for (int i = 59; i < 60; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	Sprite * sprite1 = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[66], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite1);
	animations.push_back(anim);

	// BIG POWER STONE APPEAR
	anim = new Animation(50);
	for (int i = 57; i < 59; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BIG POWER STONE ALMOST DISAPPEAR
	anim = new Animation(50);
	for (int i = 58; i < 59; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	anim->AddFrame(sprite1);
	animations.push_back(anim);

	// SMALL POWER STONE APPEAR
	anim = new Animation(50);
	for (int i = 55; i < 57; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// SMALL POWER STONE ALMOST DISAPPEAR
	anim = new Animation(50);
	for (int i = 56; i < 57; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	anim->AddFrame(sprite1);
	animations.push_back(anim);

	// BIG ENERGY APPEAR
	anim = new Animation(50);
	for (int i = 61; i < 62; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BIG ENERGY ALMOST DISAPPEAR
	anim = new Animation(50);
	for (int i = 61; i < 62; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	anim->AddFrame(sprite1);
	animations.push_back(anim);

	// SMALL ENERGY APPEAR
	anim = new Animation(50);
	for (int i = 60; i < 61; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// SMALL ENERGY ALMOST DISAPPEAR
	anim = new Animation(50);
	for (int i = 60; i < 61; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	anim->AddFrame(sprite1);

	animations.push_back(anim);

	// KEY CRYSTAL APPEAR
	anim = new Animation(50);
	for (int i = 63; i < 65; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// KEY CRYSTAL ALMOST DISAPPEAR
	anim = new Animation(50);
	for (int i = 63; i < 65; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	anim->AddFrame(sprite1);

	animations.push_back(anim);

}


Item::~Item()
{
}

void Item::Update(DWORD dt)
{
	if (this->IsDisable())
		return;

	this->timeCount += dt;

	if (this->timeCount > 4000)
		this->state = ITEM_ALMOST_DISAPPEAR;
	if (this->timeCount > 6000)
		this->Disable();

	if (Viewport::GetInstance()->IsObjectInCamera(this) == true)
	{
		vector<ColliedEvent*> coEvents;
		vector<ColliedEvent*> coEventsResult;

		vector<Tile2 *> tiles = Grid2::GetInstance()->GetNearbyTiles(this->GetRect());

		this->SetSpeedY(this->GetSpeedY() - CAPTAIN_GRAVITY);

		coEvents.clear();
		this->SetDt(dt);
		this->UpdateObjectCollider();
		this->MapCollisions(tiles, coEvents);

		if (coEvents.size() == 0)
		{
			float moveY = trunc(this->GetSpeedY()* dt);
			this->SetPositionY(this->GetPositionY() + moveY);
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			Collision::GetInstance()->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			float moveX = min_tx * this->GetSpeedX() * dt + nx * 0.4;
			float moveY = min_ty * this->GetSpeedY() * dt + ny * 0.4;
			this->SetPositionY(this->GetPositionY() + moveY);
			if (ny != 0) this->SetSpeedY(0);
		}
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
}

void Item::Render()
{
	if (this->IsDisable())
		return;

	SpriteData spriteData;

	spriteData.width = this->width;
	spriteData.height = this->height;
	spriteData.x = this->GetPositionX();
	spriteData.y = this->GetPositionY();

	spriteData.scale = 1;
	spriteData.angle = 0;

	switch (type)
	{
	case FIVE_POINT:
	{
		if (state == ITEM_APPEAR)
			this->animations[0]->Render(spriteData);
		else
			this->animations[1]->Render(spriteData);
	}
	break;
	case BIG_POWER_STONE:
	{
		if (state == ITEM_APPEAR)
			this->animations[2]->Render(spriteData);
		else
			this->animations[3]->Render(spriteData);
	}
	break;
	case SMALL_POWER_STONE:
	{
		if (state == ITEM_APPEAR)
			this->animations[4]->Render(spriteData);
		else
			this->animations[5]->Render(spriteData);
	}
	break;
	case BIG_ENERGY:
	{
		if (state == ITEM_APPEAR)
			this->animations[6]->Render(spriteData);
		else
			this->animations[7]->Render(spriteData);
	}
	break;
	case SMALL_ENERGY:
	{
		if (state == ITEM_APPEAR)
			this->animations[8]->Render(spriteData);
		else
			this->animations[9]->Render(spriteData);
	}
	break;
	case KEY_CRYSTAL:
	{
		if (state == ITEM_APPEAR)
			this->animations[10]->Render(spriteData);
		else
			this->animations[11]->Render(spriteData);
	}
	break;
	}
}
