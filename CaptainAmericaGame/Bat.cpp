#include "Bat.h"

vector<Animation *> Bat::animations = vector<Animation *>();
Bat *Bat::__instance = NULL;


Bat::Bat()
{
	LoadResources();

	state = BatState::GetInstance(this);

	this->x = 250;
	this->y = 150;
	this->width = 24;
	this->height = 16;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = width;
	collider.height = height;
}

Bat::Bat(float x, float y, BatType type)
{
	//LoadResources();

	this->type = type;

	this->state = new BatState(this);

	this->x = x;
	this->y = y;
	this->width = 24;
	this->height = 16;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = 24;
	collider.height = 16;
}

Bat *Bat::GetInstance()
{
	if (__instance == NULL)
		__instance = new Bat();
	return __instance;
}

void Bat::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	// BAT_IDLE
	Animation * anim = new Animation(100);
	for (int i = 98; i < 99; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		sprite->SetOffSetX(-5);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BAT_GOING_TO_FLY
	anim = new Animation(100);

	Sprite * sprite1 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[99], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite1, 400);

	Sprite * sprite2 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[100], TEXTURE_TRANS_COLOR);
	sprite2->SetOffSetX(3);
	anim->AddFrame(sprite2, 400);

	animations.push_back(anim);

	// BAT_FLYING
	anim = new Animation(100);

	Sprite * sprite3 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[101], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite3);

	Sprite * sprite4 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[102], TEXTURE_TRANS_COLOR);
	sprite4->SetOffSetY(-7);
	anim->AddFrame(sprite4);

	animations.push_back(anim);

	// BAT_DEAD
	anim = new Animation(100);

	anim->AddFrame(sprite4);

	animations.push_back(anim);

	// BAT_FLYING_2
	anim = new Animation(100);

	Sprite * sprite5 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[103], TEXTURE_TRANS_COLOR);
	sprite5->SetOffSetX(5);
	anim->AddFrame(sprite5);

	Sprite * sprite6 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[102], TEXTURE_TRANS_COLOR);
	sprite6->SetOffSetY(-7);
	anim->AddFrame(sprite6);

	animations.push_back(anim);

	// BAT_CAPSULE_IDLE
	anim = new Animation(100);
	for (int i = 105; i < 106; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BAT_CAPSULE_GOING_TO_FLY
	anim = new Animation(200);
	for (int i = 106; i < 108; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//-----------Hiệu ứng nổ----------------------------------------------------
	RECT* listSprite1 = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");

	// BAT_ANI_EXPLOSIVE
	anim = new Animation(50);
	for (int i = 53; i < 55; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite1[i], TEXTURE_TRANS_COLOR);
		switch (i)
		{
		case 53:
			sprite->SetOffSetX(-5);
			sprite->SetOffSetY(-3);
			break;
		case 54:
			sprite->SetOffSetX(3);
			sprite->SetOffSetY(0);
			break;
		}
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	//-----------Hiệu ứng nổ----------------------------------------------------
}

void Bat::Update(DWORD dt)
{
	if (this->disable)
		return;

	//Colision với state để riêng ra
	vector<ColliedEvent*> coEvents;
	vector<ColliedEvent*> coEventsResult;

#pragma region	Collide with map
	vector<Tile2 *> tiles = Grid2::GetInstance()->GetNearbyTiles(this->GetRect());

	coEvents.clear();
	this->SetDt(dt);
	this->UpdateObjectCollider();
	this->MapCollisions(tiles, coEvents);

	if (coEvents.size() == 0)
	{
		float moveX = trunc(this->GetSpeedX()* dt);
		float moveY = trunc(this->GetSpeedY()* dt);
		this->SetPositionX(this->GetPositionX() + moveX);
		this->SetPositionY(this->GetPositionY() + moveY);
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		Collision::GetInstance()->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		float moveX = min_tx * this->GetSpeedX() * dt + nx * 0.4;
		float moveY = min_ty * this->GetSpeedY() * dt + ny * 0.4;

		this->SetPositionX(this->GetPositionX() + moveX);
		this->SetPositionY(this->GetPositionY() + moveY);

		if (coEventsResult[0]->collisionID == 1 || coEventsResult[0]->collisionID == 4)
		{
			if (ny == 1)
			{
				this->isOnGround = true;
			}
		}
	}
	for (int i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion

	state->Colision();
	state->Update(dt);
}
void Bat::Render()
{
	if (this->disable)
		return;

	state->Render();
}

void Bat::OnCollision()
{
	((BatState*)state)->timeCount = 0;
	((BatState*)state)->state_dead();
}
