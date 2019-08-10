#include "DomestoStayState.h"
#include <math.h>

DomestoStayState * DomestoStayState::__instance = NULL;

DomestoStayState *DomestoStayState::GetInstance(Domesto *domesto)
{
	if (__instance == NULL)
		__instance = new DomestoStayState(domesto);
	return __instance;
}

DomestoStayState::DomestoStayState(Domesto *domesto)
{
	this->domesto = domesto;
	switch (domesto->GetType())
	{
	case DemestoType::STAY_FIRE_STRAIGHT:
		this->state_standing_shoot();
		break;
	case DemestoType::WALK_FIRE_STAIGHT:
		this->state_walking();
		break;
	}
}

DomestoStayState::~DomestoStayState()
{
	delete anim;
}

//Lấy trạng thái
StateDomesto DomestoStayState::GetState()
{
	return this->stateDomesto;
}
//Set trạng thái
void DomestoStayState::SetState(StateDomesto state)
{
	this->stateDomesto = state;
}

// Chuyển state khi timeCount qua mốc thời gian xác định
void DomestoStayState::ChangeStateOverTime(StateDomesto state, float timeOut)
{
	if (this->timeCount > timeOut)
	{
		this->timeCount = 0;
		switch (state)
		{
		case DOMESTO_STATE_WALKING:
			this->state_walking();
			break;

		case DOMESTO_STATE_STANDING_SHOOT:
			this->state_standing_shoot();
			break;

		case DOMESTO_STATE_CROUCH_SHOOT:
			this->state_crouch_shoot();
			break;

		case DOMESTO_STATE_DEAD:
			this->state_dead();
			break;

		default:
			break;
		}
	}
}

void DomestoStayState::state_walking()
{
	this->SetState(StateDomesto::DOMESTO_STATE_WALKING);
	anim = domesto->GetAnimationsList()[StateDomesto::DOMESTO_STATE_WALKING];
}

void DomestoStayState::state_standing_shoot()
{
	this->SetState(StateDomesto::DOMESTO_STATE_STANDING_SHOOT);
	anim = domesto->GetAnimationsList()[StateDomesto::DOMESTO_STATE_STANDING_SHOOT];

	if (this->shootTimeCount > DOMESTO_TIME_OUT_STAND * 3)
	{
		this->shootTimeCount = 0;
		int direction = domesto->IsLeft() ? 1 : 5;
		float offsetX = domesto->IsLeft() ? -16 : 16;
		float offsetY = 0;
		SpawnProjectTile::GetInstance()->SpawnBullet(domesto->GetPositionX() + offsetX, domesto->GetPositionY() + offsetY,
			direction, BulletType::ROCKET);
	}

	this->ChangeStateOverTime(StateDomesto::DOMESTO_STATE_CROUCH_SHOOT,
		DOMESTO_TIME_OUT_STAND + DOMESTO_TIME_OUT_STAND_SHOOT);
}

void DomestoStayState::state_crouch_shoot()
{
	this->SetState(StateDomesto::DOMESTO_STATE_CROUCH_SHOOT);
	anim = domesto->GetAnimationsList()[StateDomesto::DOMESTO_STATE_CROUCH_SHOOT];

	if (this->shootTimeCount > DOMESTO_TIME_OUT_CROUCH * 2)
	{
		this->shootTimeCount = 0;
		int direction = domesto->IsLeft() ? 1 : 5;
		float offsetX = domesto->IsLeft() ? -16 : 16;
		float offsetY = -16;
		SpawnProjectTile::GetInstance()->SpawnBullet(domesto->GetPositionX() + offsetX, domesto->GetPositionY() + offsetY,
			direction, BulletType::ROCKET);
	}

	this->ChangeStateOverTime(StateDomesto::DOMESTO_STATE_STANDING_SHOOT,
		DOMESTO_TIME_OUT_CROUCH + DOMESTO_TIME_OUT_CROUCH_SHOOT);
}

void DomestoStayState::state_dead()
{
	this->SetState(StateDomesto::DOMESTO_STATE_DEAD);
	anim = domesto->GetAnimationsList()[StateDomesto::DOMESTO_STATE_DEAD];

	domesto->SetSpeedX(0);

	if (this->timeCount > 200)
		anim = domesto->GetAnimationsList()[4];

	if (this->timeCount > 350)
		domesto->disable = true;
}

void DomestoStayState::Colision()
{

}

void DomestoStayState::Update(DWORD dt)
{
	timeCount += dt;
	this->shootTimeCount += dt;

	//Update theo state
	switch (stateDomesto)
	{
	case DOMESTO_STATE_WALKING:
		this->state_walking();
		break;

	case DOMESTO_STATE_STANDING_SHOOT:
		this->state_standing_shoot();
		break;

	case DOMESTO_STATE_CROUCH_SHOOT:
		this->state_crouch_shoot();
		break;

	case DOMESTO_STATE_DEAD:
		this->state_dead();
		break;

	default:
		break;
	}
}

void DomestoStayState::Render()
{
	SpriteData spriteData;
	if (this->domesto != NULL)
	{
		spriteData.width = 24;
		spriteData.height = 46;
		spriteData.x = domesto->GetPositionX();
		spriteData.y = domesto->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = domesto->IsLeft();
		spriteData.isFlipped = domesto->IsFlipped();
	}

	anim->Render(spriteData);
}

