#include "Elevator.h"

vector<Animation *> Elevator::animations = vector<Animation *>();
Elevator *Elevator::__instance = NULL;


Elevator::Elevator()
{
	type = CIRCLE;

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
}

Elevator::Elevator(float x, float y, ElevatorType type)
{
	//LoadResources();

	this->timeCount = 0;

	this->disable = false;

	this->posx = x;
	this->posy = y;

	this->type = type;

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
}

Elevator *Elevator::GetInstance()
{
	if (__instance == NULL)
		__instance = new Elevator();
	return __instance;
}

void Elevator::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	Animation * anim = new Animation(100);
	for (int i = 89; i < 90; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
}

void Elevator::fly_circle()
{
	float timeOut = 4800;
	float pi = acos(-1);
	float delta = timeCount * pi * 2 / timeOut;
	float speedX = cosf(delta) / 10;
	float speedY = sinf(delta) / 10;

	this->SetSpeedX(speedX);
	this->SetSpeedY(speedY);
}

void Elevator::fly_slash()
{
	if (this->GetPositionX() <= posx)
		this->SetSpeedX(ELEVATOR_SPEED / 1.2);

	if (this->GetPositionX() >= posx + 50)
		this->SetSpeedX(-ELEVATOR_SPEED / 1.2);

	if (this->GetPositionY() <= posy)
		this->SetSpeedY(ELEVATOR_SPEED / 1.2);

	if (this->GetPositionY() >= posy + 50)
		this->SetSpeedY(-ELEVATOR_SPEED / 1.2);
}

void Elevator::fly_horizontal()
{
	if (this->GetPositionX() <= posx)
		this->SetSpeedX(ELEVATOR_SPEED);

	if (this->GetPositionX() >= posx + 100)
		this->SetSpeedX(-ELEVATOR_SPEED);
}

void Elevator::Update(DWORD dt)
{
	if (this->disable)
		return;

	this->timeCount += dt;

	float moveX = trunc(this->GetSpeedX()* dt);
	float moveY = trunc(this->GetSpeedY()* dt);
	this->SetPositionX(this->GetPositionX() + moveX);
	this->SetPositionY(this->GetPositionY() + moveY);

	switch (type)
	{
	case CIRCLE:
		this->fly_circle();
		break;

	case SLASH:
		this->fly_slash();
		break;

	case HORIZONTAL:
		this->fly_horizontal();
		break;

	default:
		break;
	}

}
void Elevator::Render()
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

	this->animations[0]->Render(spriteData);
}

void Elevator::OnCollision()
{

}
