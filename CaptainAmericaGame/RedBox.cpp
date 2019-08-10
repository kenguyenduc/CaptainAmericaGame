#include "RedBox.h"

vector<Animation *> RedBox::animations = vector<Animation *>();
RedBox *RedBox::__instance = NULL;


RedBox::RedBox()
{
	LoadResources();

	state = RedBoxState::GetInstance(this);

	this->x = 200;
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

RedBox::RedBox(float x, float y, RedBoxType type)
{
	this->state = new RedBoxState(this);

	this->type = type;

	this->x = x;
	this->y = y;
	this->width = TILES_WIDTH_PER_TILE;
	this->height = TILES_HEIGHT_PER_TILE;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = TILES_WIDTH_PER_TILE;
	collider.height = TILES_HEIGHT_PER_TILE;
}

RedBox *RedBox::GetInstance()
{
	if (__instance == NULL)
		__instance = new RedBox();
	return __instance;
}

void RedBox::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	// RED_BOX_ANI_CLOSE
	Animation * anim = new Animation(100);
	for (int i = 96; i < 97; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// RED_BOX_ANI_OPEN
	anim = new Animation(100);
	for (int i = 95; i < 96; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// RED_BOX_MAP_2_ANI_CLOSE
	anim = new Animation(100);
	for (int i = 111; i < 112; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// RED_BOX_MAP_2_ANI_OPEN
	anim = new Animation(100);
	for (int i = 110; i < 111; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void RedBox::Update(DWORD dt)
{
	state->Colision();
	state->Update(dt);
}
void RedBox::Render()
{
	state->Render();
}

void RedBox::OnCollision()
{
	((RedBoxState*)state)->timeCount = 0;
	((RedBoxState*)state)->state_open();
}
