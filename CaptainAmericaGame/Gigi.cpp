#include "Gigi.h"

vector<Animation *> Gigi::animations = vector<Animation *>();
Gigi *Gigi::__instance = NULL;


Gigi::Gigi()
{
	LoadResources();

	state = GigiState::GetInstance(this);

	this->x = 250;
	this->y = 150;
	this->width = ENEMIES_SPRITE_WIDTH;
	this->height = ENEMIES_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = ENEMIES_SPRITE_WIDTH;
	collider.height = ENEMIES_SPRITE_HEIGHT;
}

Gigi::Gigi(float x, float y)
{
	this->state = new GigiState(this);

	this->posx = x;
	this->posy = y;

	this->x = x;
	this->y = y;
	this->width = ENEMIES_SPRITE_WIDTH;
	this->height = ENEMIES_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = ENEMIES_SPRITE_WIDTH;
	collider.height = ENEMIES_SPRITE_HEIGHT;
}

Gigi *Gigi::GetInstance()
{
	if (__instance == NULL)
		__instance = new Gigi();
	return __instance;
}

void Gigi::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	//FLY
	Animation * anim = new Animation(100);

	Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[22], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);

	Sprite * sprite1 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[30], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite1);

	animations.push_back(anim);

	//DEAD
	anim = new Animation(20);

	anim->AddFrame(sprite);

	Sprite * sprite3 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[104], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite3);

	animations.push_back(anim);

	//-----------Hiệu ứng nổ----------------------------------------------------
	RECT* listSprite1 = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");

	// GIGI_ANI_EXPLOSIVE
	anim = new Animation(50);
	for (int i = 53; i < 55; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite1[i], TEXTURE_TRANS_COLOR);
		switch (i)
		{
		case 53:
			sprite->SetOffSetX(-5);
			sprite->SetOffSetY(-27);
			break;
		case 54:
			sprite->SetOffSetX(3);
			sprite->SetOffSetY(-21);
			break;
		}
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	//-----------Hiệu ứng nổ----------------------------------------------------
}

void Gigi::Update(DWORD dt)
{
	if (this->disable)
		return;

	if (this->GetPositionX() > Captain::GetInstance()->GetPositionX())
		this->setIsLeft(true);
	else
		this->setIsLeft(false);

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

		if (coEventsResult[0]->collisionID == 1)
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
void Gigi::Render()
{
	if (this->disable)
		return;

	state->Render();
}

void Gigi::OnCollision()
{
	((GigiState*)state)->timeCount = 0;
	((GigiState*)state)->state_dead();
}
