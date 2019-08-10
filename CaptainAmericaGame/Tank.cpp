#include "Tank.h"

vector<Animation *> Tank::animations = vector<Animation *>();
Tank *Tank::__instance = NULL;


Tank::Tank()
{
	LoadResources();

	state = TankState::GetInstance(this);

	this->x = 230;
	this->y = 100;
	this->width = TILES_WIDTH_PER_TILE;
	this->height = TILES_HEIGHT_PER_TILE;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = TILES_WIDTH_PER_TILE;
	collider.height = TILES_HEIGHT_PER_TILE;
}

Tank::Tank(float x, float y, TankType type)
{
	this->state = new TankState(this);

	this->type = type;

	switch (type)
	{
	case TOP:
		((TankState*)state)->SetDirection(7);
		break;
	case BOTTOM:
		((TankState*)state)->SetDirection(3);
		break;
	case LEFT:
		((TankState*)state)->SetDirection(1);
		break;
	case RIGHT:
		((TankState*)state)->SetDirection(5);
		break;
	default:
		break;
	}

	this->x = x;
	this->y = y;
	this->width = TILES_WIDTH_PER_TILE;
	this->height = TILES_WIDTH_PER_TILE;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = TILES_WIDTH_PER_TILE;
	collider.height = TILES_WIDTH_PER_TILE;
}

Tank *Tank::GetInstance()
{
	if (__instance == NULL)
		__instance = new Tank();
	return __instance;
}

void Tank::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	// TANK_ANI_BLEEDING
	Animation * anim = new Animation(10);
	for (int i = 79; i < 87; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// TANK_ANI_LEFT
	anim = new Animation(100);
	for (int i = 85; i < 86; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// TANK_ANI_BOTTOM_LEFT
	anim = new Animation(100);
	for (int i = 84; i < 85; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// TANK_ANI_BOTTOM
	anim = new Animation(100);
	for (int i = 83; i < 84; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// TANK_ANI_BOTTOM_RIGHT
	anim = new Animation(100);
	for (int i = 82; i < 83; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// TANK_ANI_RIGHT
	anim = new Animation(100);
	for (int i = 81; i < 82; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// TANK_ANI_TOP_RIGHT
	anim = new Animation(100);
	for (int i = 80; i < 81; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// TANK_ANI_TOP
	anim = new Animation(100);
	for (int i = 79; i < 80; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// TANK_ANI_TOP_LEFT
	anim = new Animation(100);
	for (int i = 86; i < 87; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void Tank::Update(DWORD dt)
{
	state->Colision();
	state->Update(dt);
}
void Tank::Render()
{
	this->state->Render();
}

void Tank::OnCollision()
{
	((TankState*)state)->timeCount = 0;
	((TankState*)state)->SetDirection(0);
}
