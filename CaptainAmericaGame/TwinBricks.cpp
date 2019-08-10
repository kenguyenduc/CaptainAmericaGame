#include "TwinBricks.h"

vector<Animation *> TwinBricks::animations = vector<Animation *>();
TwinBricks *TwinBricks::__instance = NULL;


TwinBricks::TwinBricks()
{
	this->x = 250;
	this->y = 100;
	this->width = 32;
	this->height = 16;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = width;
	collider.height = height;

	this->disable = false;
	this->timeCount = 0;

	this->state = TwinBricksState::TWIN_BRICK_IDLE;
}

TwinBricks::TwinBricks(float x, float y)
{
	//LoadResources();

	this->timeCount = 0;

	this->disable = false;

	this->x = x;
	this->y = y;
	this->width = 32;
	this->height = 16;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = 32;
	collider.height = 16;

	this->state = TwinBricksState::TWIN_BRICK_IDLE;
}

TwinBricks *TwinBricks::GetInstance()
{
	if (__instance == NULL)
		__instance = new TwinBricks();
	return __instance;
}

void TwinBricks::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	//IDLE
	Animation * anim = new Animation(100);
	for (int i = 88; i < 89; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//SEPERATE
	anim = new Animation(20);
	for (int i = 112; i < 114; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		sprite->SetOffSetX(16);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void TwinBricks::Update(DWORD dt)
{
	if (this->disable)
		return;

	this->timeCount += dt;
}

void TwinBricks::Render()
{
	if (this->disable)
		return;

	SpriteData spriteData;

	spriteData.width = this->width;
	spriteData.height = this->height;
	spriteData.x = this->GetPositionX();
	spriteData.y = this->GetPositionY();

	spriteData.scale = 1;
	spriteData.angle = 0;


	switch (this->state)
	{
	case TwinBricksState::TWIN_BRICK_IDLE:
		this->animations[TWIN_BRICK_IDLE]->Render(spriteData);
		break;

	case TwinBricksState::TWIN_BRICK_SEPERATE:
		this->animations[TWIN_BRICK_SEPERATE]->Render(spriteData);
		break;
	}
}

void TwinBricks::OnCollision()
{
	this->state = TwinBricksState::TWIN_BRICK_SEPERATE;

	if (this->timeCount > 2000)
	{
		this->timeCount = 0;
		this->state = TwinBricksState::TWIN_BRICK_IDLE;
	}
}
