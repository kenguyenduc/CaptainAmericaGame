#include "GigiState.h"
#include <math.h>

GigiState * GigiState::__instance = NULL;

GigiState *GigiState::GetInstance(Gigi *gigi)
{
	if (__instance == NULL)
		__instance = new GigiState(gigi);
	return __instance;
}


GigiState::GigiState(Gigi *gigi)
{
	this->gigi = gigi;
	this->state_flying();
	this->disableTimeCount = 0;
}

GigiState::~GigiState()
{
	delete anim;
}

//Lấy trạng thái
StateGigi GigiState::GetState()
{
	return this->stateGigi;
}
//Set trạng thái
void GigiState::SetState(StateGigi state)
{
	this->stateGigi = state;
}

void GigiState::state_flying()
{
	this->SetState(GIGI_STATE_FLYING);
	anim = gigi->GetAnimationsList()[GIGI_STATE_FLYING];

	//chuyển động
	if (gigi->GetPositionX() < gigi->posx + 120 && gigi->GetPositionY() >= gigi->posy)
	{
		gigi->SetSpeedX(GIGI_FLY_SPEED);
		gigi->SetSpeedY(0);
	}
	if (gigi->GetPositionX() >= gigi->posx + 120 && gigi->GetPositionY() > gigi->posy - 25)
	{
		gigi->SetSpeedX(0);
		gigi->SetSpeedY(-GIGI_FLY_SPEED / 1.05);
	}
	if (gigi->GetPositionX() > gigi->posx && gigi->GetPositionY() <= gigi->posy - 25)
	{
		gigi->SetSpeedX(-GIGI_FLY_SPEED);
		gigi->SetSpeedY(0);
	}
	if (gigi->GetPositionX() <= gigi->posx && gigi->GetPositionY() < gigi->posy)
	{
		gigi->SetSpeedX(0);
		gigi->SetSpeedY(GIGI_FLY_SPEED / 1.05);
	}

	//bắn tên lửa
	if (this->shootTimeCount > GIGI_DELAY_ATTACK_TIME)
	{
		this->shootTimeCount = 0;
		int direction = gigi->IsLeft() ? 1 : 5;
		float offsetX = gigi->IsLeft() ? -16 : 16;
		float offsetY = -5;
		SpawnProjectTile::GetInstance()->SpawnBullet(gigi->GetPositionX() + offsetX, gigi->GetPositionY() + offsetY,
			direction, BulletType::GIGIROCKET);
	}
}

void GigiState::state_dead()
{
	this->SetState(GIGI_STATE_DEAD);
	anim = gigi->GetAnimationsList()[GIGI_STATE_DEAD];

	gigi->SetSpeedX(0);
	gigi->SetSpeedY(-GIGI_FLY_SPEED * 2);

	if (gigi->isOnGround)
	{
		anim = gigi->GetAnimationsList()[2];

		if (this->disableTimeCount > 150)
			gigi->disable = true;
	}
}

void GigiState::Colision()
{

}

void GigiState::Update(DWORD dt)
{
	this->timeCount += dt;
	this->shootTimeCount += dt;

	if (gigi->isOnGround && stateGigi == StateGigi::GIGI_STATE_DEAD)
		this->disableTimeCount += dt;

	//Update theo state
	switch (stateGigi)
	{
	case GIGI_STATE_FLYING:
		this->state_flying();
		break;

	case GIGI_STATE_DEAD:
		this->state_dead();
		break;

	default:
		break;
	}
}

void GigiState::Render()
{
	SpriteData spriteData;
	if (this->gigi != NULL)
	{
		spriteData.width = ENEMIES_SPRITE_WIDTH;
		spriteData.height = ENEMIES_SPRITE_HEIGHT;
		spriteData.x = gigi->GetPositionX();
		spriteData.y = gigi->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = gigi->IsLeft();
		spriteData.isFlipped = gigi->IsFlipped();
	}

	anim->Render(spriteData);
}

