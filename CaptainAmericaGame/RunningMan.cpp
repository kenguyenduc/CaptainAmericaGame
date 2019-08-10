#include "RunningMan.h"

vector<Animation *> RunningMan::animations = vector<Animation *>();
RunningMan *RunningMan::__instance = NULL;


RunningMan::RunningMan()
{
	LoadResources();

	state = RunningManState::GetInstance(this);
	type = RunningManType::NORMAL;

	this->x = 250;
	this->y = 80;
	this->width = ENEMIES_SPRITE_WIDTH;
	this->height = ENEMIES_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = ENEMIES_SPRITE_WIDTH;
	collider.height = ENEMIES_SPRITE_HEIGHT;
}

RunningMan::RunningMan(float x, float y, RunningManType type)
{
	this->state = new RunningManState(this);

	this->type = type;

	switch (type)
	{
	case NORMAL:
		break;
	case ONLY_RUN:
		break;
	case ONLY_CROUCH:
		((RunningManState*)state)->SetState(RUNNING_MAN_STATE_CROUCH_SHOOT);
		break;
	default:
		break;
	}

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

RunningMan *RunningMan::GetInstance()
{
	if (__instance == NULL)
		__instance = new RunningMan();
	return __instance;
}

void RunningMan::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	// RUNNING_MAN_ANI_RUNNING
	Animation * anim = new Animation(100);
	for (int i = 0; i < 3; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// RUNNING_MAN_ANI_STANDING_SHOOT
	anim = new Animation(200);
	for (int i = 3; i < 4; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite, 5000);
	}
	animations.push_back(anim);

	// RUNNING_MAN_ANI_CROUCH_SHOOT
	anim = new Animation(200);
	for (int i = 4; i < 5; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// RUNNING_MAN_ANI_DEAD
	anim = new Animation(100);
	for (int i = 5; i < 6; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//-----------Hiệu ứng nổ----------------------------------------------------
	RECT* listSprite1 = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");

	// RUNNING_MAN_ANI_EXPLOSIVE
	anim = new Animation(50);
	for (int i = 53; i < 55; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite1[i], TEXTURE_TRANS_COLOR);
		switch (i)
		{
		case 53:
			sprite->SetOffSetX(-5);
			sprite->SetOffSetY(-8);
			break;
		case 54:
			sprite->SetOffSetX(3);
			sprite->SetOffSetY(-5);
			break;
		}
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	//-----------Hiệu ứng nổ----------------------------------------------------
}

void RunningMan::Update(DWORD dt)
{
	if (this->disable)
		return;
	// Collide with brick
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
				this->SetIsGrounded(true);
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

	state->Colision();
	state->Update(dt);
}
void RunningMan::Render()
{
	if (this->disable)
		return;
	state->Render();
}

void RunningMan::OnCollision()
{
	((RunningManState*)state)->timeCount = 0;
	((RunningManState*)state)->state_dead();
}
