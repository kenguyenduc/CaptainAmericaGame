#include "Bullet.h"

vector<Animation *> Bullet::animations;

Bullet::Bullet(float x, float y, int direction, BulletType type)
{
	//LoadResources();
	Initialize(x, y, direction, type);
}

void Bullet::Initialize(float x, float y, int direction, BulletType type)
{
	this->timeCount = 0;
	this->type = type;

	this->direction = direction;

	this->SetSpeedX(0);
	this->SetSpeedY(0);

	switch (type)
	{
	case BULLET_NORMAL:
	{
		width = 6;
		height = 6;
		if (direction == 1)
		{
			this->SetSpeedX(-BULLET_NORMAL_SPEED);
			this->SetSpeedY(0);
		}
		else
		{
			this->SetSpeedX(BULLET_NORMAL_SPEED);
			this->SetSpeedY(0);
		}
	}
	break;
	case BULLET_TANK:
	{
		width = 8;
		height = 8;
	}
	break;
	case BULLET_BOSS2:
	{
		width = 16;
		height = 11;
	}
	break;
	case ROCKET:
	{
		width = 15;
		height = 7;
	}
	break;
	case BULLET_NORMAL_BOSS1:
	{
		width = 8;
		height = 5;
	}
	break;
	case BULLET_SPECIAL_BOSS1:
	{
		width = 16;
		height = 16;
	}
	break;
	case BARREL:
	{
		barrelState = 0;
		width = 22;
		height = 14;
	}
	break;
	}


	this->x = x;
	this->y = y;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = vy;
	collider.width = this->width;
	collider.height = this->height;
	this->disable = false;
}

void Bullet::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Enemies\\Enemies.txt");

	// BULLET_NORMAL
	Animation * anim = new Animation(100);
	for (int i = 6; i < 7; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		sprite->SetOffSetY(12);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BULLET_TANK
	anim = new Animation(100);
	for (int i = 97; i < 98; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	RECT* listSprite1 = loadTXT.LoadRect((char*)"Resources\\Enemies\\Boss2.txt");

	// BULLET_BOSS2
	anim = new Animation(100);
	for (int i = 5; i < 6; i++)
	{
		Sprite * sprite = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite1[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//-----------Rocket------------------------
	// Bay ngang
	anim = new Animation(100);
	Sprite * sprite1 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[15], TEXTURE_TRANS_COLOR);
	//sprite1->SetOffSetX(7);
	sprite1->SetOffSetY(13);
	anim->AddFrame(sprite1);
	Sprite * sprite2 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[17], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite2);
	sprite2->SetOffSetY(11);
	animations.push_back(anim);

	// Bay xéo lên
	anim = new Animation(100);
	Sprite * sprite3 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[16], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite3);
	Sprite * sprite4 = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[18], TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite4);
	animations.push_back(anim);
	//-----------------------------------------

	//-----------Đạn boss 1--------------------
	RECT* listSprite2 = loadTXT.LoadRect((char*)"Resources\\Enemies\\Boss1.txt");

	// SMALL_BULLET_HORIZONTAL_BOSS1 (đạn nhỏ bay ngang)
	anim = new Animation(100);
	for (int i = 23; i < 24; i++)
	{
		Sprite * sprite = new Sprite(BOSS1_TEXTURE_LOCATION, listSprite2[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// SMALL_BULLET_DIAGONAL_BOSS1 (đạn nhỏ bay xéo lên)
	anim = new Animation(100);
	for (int i = 22; i < 23; i++)
	{
		Sprite * sprite = new Sprite(BOSS1_TEXTURE_LOCATION, listSprite2[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BIG_BULLET_HORIZONTAL_BOSS1 (đạn lớn bay ngang)
	anim = new Animation(100);
	for (int i = 18; i < 19; i++)
	{
		Sprite * sprite = new Sprite(BOSS1_TEXTURE_LOCATION, listSprite2[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// BIG_BULLET_DOWN_BOSS1 (đạn lớn bay xuống)
	anim = new Animation(100);
	for (int i = 20; i < 21; i++)
	{
		Sprite * sprite = new Sprite(BOSS1_TEXTURE_LOCATION, listSprite2[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	//-----------------------------------------

	// NO9: GIGI_ROCKET_FLY_DOWN
	anim = new Animation(100);
	for (int i = 108; i < 110; i++)
	{
		Sprite * sprite = new Sprite(ENEMIES_TEXTURE_LOCATION, listSprite[i], TEXTURE_TRANS_COLOR);
		if (i == 108)
			sprite->SetOffSetX(1);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	// NO10: BARREL
	anim = new Animation(100);
	for (int i = 10; i < 11; i++)
	{
		Sprite * sprite = new Sprite(BOSS2_TEXTURE_LOCATION, listSprite1[i], TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	//-----------Hiệu ứng nổ----------------------------------------------------
	RECT* listSprite3 = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");

	// BULLET_ANI_EXPLOSIVE
	anim = new Animation(50);
	for (int i = 53; i < 55; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite3[i], TEXTURE_TRANS_COLOR);
		switch (i)
		{
		case 53:
			sprite->SetOffSetX(-5);
			sprite->SetOffSetY(5);
			break;
		case 54:
			sprite->SetOffSetX(3);
			sprite->SetOffSetY(9);
			break;
		}
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	//-----------Hiệu ứng nổ----------------------------------------------------
}

void Bullet::BulletNormalUpdate(DWORD dt)
{

}

void Bullet::BulletTankUpdate(DWORD dt)
{
	switch (direction)
	{
	case 1:		//Left
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
		break;
	case 2:		//Bottom-Left
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(-BULLET_NORMAL_SPEED);
		break;
	case 3:		//Bottom
		this->SetSpeedX(0);
		this->SetSpeedY(-BULLET_NORMAL_SPEED);
		break;
	case 4:		//Bottom-Right
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(-BULLET_NORMAL_SPEED);
		break;
	case 5:		//Right
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
		break;
	case 6:		//Top-Right
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(BULLET_NORMAL_SPEED);
		break;
	case 7:		//Top
		this->SetSpeedX(0);
		this->SetSpeedY(BULLET_NORMAL_SPEED);
		break;
	case 8:		//Top-Left
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(BULLET_NORMAL_SPEED);
		break;
	}
}

void Bullet::BulletBoss2Update(DWORD dt)
{
	switch (direction)
	{
	case 1:
	{
		this->setIsLeft(true);
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
	}
	break;
	case 5:
	{
		this->setIsLeft(false);
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
	}
	break;
	case 9:
	{
		this->SetSpeedX(0);
		this->SetSpeedY(0);
	}
	break;
	}
}

void Bullet::RocketUpdate(DWORD dt)
{
	// 1:Left	2:B-L	3:Bottom	4:B-R	5:Right	6:T-R	7:Top	8:T-L
	switch (direction)
	{
	case 1:		//Left
		this->setIsLeft(true);
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
		break;
	case 2:		//Bottom-Left
		break;
	case 3:		//Bottom
		break;
	case 4:		//Bottom-Right
		break;
	case 5:		//Right
		this->setIsLeft(false);
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
		break;
	case 6:		//Top-Right
		this->setIsLeft(false);
		this->SetSpeedX(BULLET_NORMAL_SPEED);

		if (timeCount > ROCKET_CHANGE_DIRECTION_TIME)
		{
			this->SetSpeedY(BULLET_NORMAL_SPEED);
		}

		break;
	case 7:		//Top
		break;
	case 8:		//Top-Left
		this->setIsLeft(true);
		this->SetSpeedX(-BULLET_NORMAL_SPEED);

		if (timeCount > ROCKET_CHANGE_DIRECTION_TIME)
		{
			this->SetSpeedY(BULLET_NORMAL_SPEED);
		}
		break;
	case 9:
		this->SetSpeedX(0);
		this->SetSpeedY(0);
		break;
	}
}

void Bullet::GiGiRocketUpdate(DWORD dt)
{
	int timeOut = 100;
	if (timeCount < timeOut)
	{

		timeCount = timeCount - timeOut;

		float distanceX = -(this->GetPositionX() - Captain::GetInstance()->GetPositionX());
		float distanceY = -(this->GetPositionY() - Captain::GetInstance()->GetPositionY());

		switch (direction)
		{
		case 1: // 2 | 8 | 1
			if (abs(distanceY) < 16 && distanceX < 0)
				direction = 1;
			else if (distanceY < 0)
				direction = 2;
			else if (distanceY > 0)
				direction = 8;
			break;
		case 2: // 1 | 2 | 3
			if (distanceY < 0 && distanceX < 0)
				direction = 2;
			else if (distanceY > 0)
				direction = 1;
			else if (distanceX > 0)
				direction = 3;
			break;
		case 3:	//	2 | 3 | 4
			if (distanceY < 0 && abs(distanceX) < 16)
				direction = 3;
			else if (distanceX < 0)
				direction = 2;
			else if (distanceX > 0)
				direction = 4;
			break;
		case 4:	//	3 | 4 | 5
			if (distanceY < 0 && distanceX > 0)
				direction = 4;
			else if (distanceX < 0)
				direction = 3;
			else if (distanceY > 0)
				direction = 5;
			break;
		case 5: // 4 | 5 | 6
			if (abs(distanceY) < 16 && distanceX > 0)
				direction = 5;
			else if (distanceY < 0)
				direction = 4;
			else if (distanceY > 0)
				direction = 6;
			break;
		case 6: // 5 | 6 | 7
			if (distanceY > 0 && distanceX > 0)
				direction = 6;
			else if (distanceX < 0)
				direction = 7;
			else if (distanceY < 0)
				direction = 5;
			break;
		case 7: // 6 | 7 | 8
			if (distanceY < 0 && abs(distanceX) < 16)
				direction = 7;
			else if (distanceX < 0)
				direction = 8;
			else if (distanceX > 0)
				direction = 6;
			break;
		case 8:
			if (distanceY > 0 && distanceX < 0)
				direction = 8;
			else if (distanceX > 0)
				direction = 7;
			else if (distanceY < 0)
				direction = 1;
			break;
		}
	}

	float speed = BULLET_NORMAL_SPEED / 2;
	switch (direction)
	{
	case 1:
		this->setIsLeft(true);
		this->SetSpeedX(-speed);

		this->SetSpeedY(0);
		break;
	case 2:
		this->setIsLeft(true);
		this->setIsFlipDown(true);

		this->SetSpeedX(-speed);
		this->SetSpeedY(-speed);
		break;
	case 3:
		this->SetSpeedX(0);
		this->SetSpeedY(-speed);
		break;
	case 4:
		this->setIsLeft(false);
		this->setIsFlipDown(true);

		this->SetSpeedX(speed);
		this->SetSpeedY(-speed);
		break;
	case 5:
		this->setIsLeft(false);

		this->SetSpeedX(speed);
		this->SetSpeedY(0);
		break;
	case 6:
		this->setIsLeft(false);
		this->setIsFlipDown(false);

		this->SetSpeedX(speed);
		this->SetSpeedY(speed);
		break;
	case 7:
		this->SetSpeedX(0);
		this->SetSpeedY(speed);
		break;
	case 8:
		this->setIsLeft(true);
		this->setIsFlipDown(false);

		this->SetSpeedX(-speed);
		this->SetSpeedY(speed);
		break;
	case 9:
		this->SetSpeedX(0);
		this->SetSpeedY(0);
		break;
	}
}

void Bullet::BulletNormalBoss1Update(DWORD dt)
{
	/*if (direction == 1)
	{
		this->setIsLeft(true);
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
	}
	else
	{
		this->setIsLeft(false);
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
	}*/

	switch (direction)
	{
	case 1:		//Left
		this->setIsLeft(true);
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
		break;
	case 2:		//Bottom-Left
		break;
	case 3:		//Bottom
		break;
	case 4:		//Bottom-Right
		break;
	case 5:		//Right
		this->setIsLeft(false);
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(0);
		break;
	case 6:		//Top-Right
		this->setIsLeft(false);
		this->SetSpeedX(BULLET_NORMAL_SPEED);
		this->SetSpeedY(BULLET_NORMAL_SPEED * 0.5f);

		break;
	case 7:		//Top
		break;
	case 8:		//Top-Left
		this->setIsLeft(true);
		this->SetSpeedX(-BULLET_NORMAL_SPEED);
		this->SetSpeedY(BULLET_NORMAL_SPEED * 0.5f);
		break;
	}
}

void Bullet::BulletSpecialBoss1Update(DWORD dt)
{
	if (direction == 1)
	{
		this->setIsLeft(true);
		this->SetSpeedX(-ROCKET_SPEED);
		this->SetSpeedY(0);
	}
	else if (direction == 3)
	{
		this->SetSpeedX(0);
		this->SetSpeedY(-CAPTAIN_JUMP_SPEED_Y);
		this->setIsFlipDown(false);
	}
	else
	{
		this->setIsLeft(false);
		this->SetSpeedX(ROCKET_SPEED);
		this->SetSpeedY(0);
	}
}

void Bullet::BarrelUpdate(DWORD dt)
{
	switch (barrelState)
	{
	case 0:
		if (timeCount < BOSS2_HOLD_BARREL_TIME)
			return;
		barrelState++;
		timeCount = 0;
		break;
	case 1:
		switch (direction)
		{
		case 1:
			this->SetSpeedX(-0.065f);
			this->SetSpeedY(0.1f);
			break;
		case 5:
			this->SetSpeedX(0.065f);
			this->SetSpeedY(0.1f);
			break;
		case 2:
			this->SetSpeedX(-0.08f);
			this->SetSpeedY(0.15f);
			break;
		case 6:
			this->SetSpeedX(0.08f);
			this->SetSpeedY(0.15f);
			break;
		}
		barrelState++;
		break;
	case 2:
		this->SetSpeedY(this->GetSpeedY() - 0.004f);
		break;
	}
}

void Bullet::Update(DWORD dt)
{
	if (this->disable)
		return;

	this->timeCount += dt;

	float moveX = trunc(this->GetSpeedX()* dt);
	float moveY = trunc(this->GetSpeedY()* dt);
	this->SetPositionX(this->GetPositionX() + moveX);
	this->SetPositionY(this->GetPositionY() + moveY);

	UpdateObjectCollider();

	switch (type)
	{
	case BulletType::BULLET_NORMAL:
		BulletNormalUpdate(dt);
		break;
	case BulletType::BULLET_TANK:
		BulletTankUpdate(dt);
		break;
	case BulletType::BULLET_BOSS2:
		BulletBoss2Update(dt);
		break;
	case BulletType::ROCKET:
		RocketUpdate(dt);
		break;
	case BulletType::GIGIROCKET:
		GiGiRocketUpdate(dt);
		break;
	case BulletType::BULLET_NORMAL_BOSS1:
		BulletNormalBoss1Update(dt);
		break;
	case BulletType::BULLET_SPECIAL_BOSS1:
		BulletSpecialBoss1Update(dt);
		break;
	case BulletType::BARREL:
		BarrelUpdate(dt);
		break;
	}

	if (timeCount > BULLET_TIME_LIFE)
		Disable();
}

void Bullet::OnCollision()
{
	this->direction = 9;
}

void Bullet::Render()
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

	spriteData.isLeft = this->IsLeft();
	spriteData.isFlipped = this->IsFlipped();
	spriteData.isFlipVertical = this->IsFlipDown();

	switch (type)
	{
	case BULLET_NORMAL:
	{
		this->animations[BULLET_NORMAL]->Render(spriteData);
	}
	break;

	case BULLET_TANK:
	{
		this->animations[BULLET_TANK]->Render(spriteData);
	}
	break;

	case BULLET_BOSS2:
	{
		if (direction == 9)
			this->animations[11]->Render(spriteData);
		else
			this->animations[BULLET_BOSS2]->Render(spriteData);
	}
	break;

	case ROCKET:
	{
		switch (direction)
		{
		case 1:
		case 5:
			this->animations[ROCKET]->Render(spriteData);
			break;
		case 6:
		case 8:
			if (timeCount < ROCKET_CHANGE_DIRECTION_TIME)
				this->animations[ROCKET]->Render(spriteData);
			else
				this->animations[4]->Render(spriteData);
			break;
		case 9:
			this->animations[11]->Render(spriteData);
			break;
		}
	}
	break;
	case GIGIROCKET:
		switch (direction)
		{
		case 1:
			this->animations[ROCKET]->Render(spriteData);
			break;
		case 2:
			this->animations[4]->Render(spriteData);
			break;
		case 3:
			this->animations[9]->Render(spriteData);
			break;
		case 4:
			this->animations[4]->Render(spriteData);
			break;
		case 5:
			this->animations[ROCKET]->Render(spriteData);
			break;
		case 6:
			this->animations[4]->Render(spriteData);
			break;
		case 7:
			this->animations[9]->Render(spriteData);
			break;
		case 8:
			this->animations[4]->Render(spriteData);
			break;
		case 9:
			this->animations[11]->Render(spriteData);
			break;
		}
		break;
	case BULLET_NORMAL_BOSS1:
	{
		this->animations[5]->Render(spriteData);
	}
	break;

	case BULLET_SPECIAL_BOSS1:
	{
		if (direction == 3)
			this->animations[8]->Render(spriteData);
		else
			this->animations[7]->Render(spriteData);
	}
	break;

	case BARREL:
	{
		if (direction == 9)
			this->animations[11]->Render(spriteData);
		else
			this->animations[10]->Render(spriteData);
	}
	break;
	}
}

Bullet::~Bullet()
{
}

