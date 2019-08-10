#include "Boss2State.h"
#include <math.h>

Boss2State * Boss2State::__instance = NULL;

Boss2State *Boss2State::GetInstance(Boss2 *boss2)
{
	if (__instance == NULL)
		__instance = new Boss2State(boss2);
	return __instance;
}


Boss2State::Boss2State(Boss2 *boss2)
{
	this->boss2 = boss2;
	this->state_idle();
	this->timeCount = 0;
}

Boss2State::~Boss2State()
{
	delete anim;
}

//Lấy trạng thái
StateBoss2 Boss2State::GetState()
{
	return this->stateBoss2;
}
//Set trạng thái
void Boss2State::SetState(StateBoss2 state)
{
	this->stateBoss2 = state;
}

void Boss2State::state_idle()
{
	this->SetState(BOSS2_STATE_IDLE);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_IDLE];

	boss2->setIsLeft(Captain::GetInstance()->GetPositionX() - boss2->GetPositionX() > 0 ? false : true);
	if (this->timeCount > 300)
	{
		this->timeCount -= 300;
		this->state_hold_barrel();
		srand(time(NULL));
		int randomState = 1;// rand() % 1 + 2;

		if (randomState == 1)
		{
			SpawnProjectTile::GetInstance()->SpawnBullet(boss2->GetPositionX(), boss2->GetPositionY(),
				boss2->IsLeft() ? 1 : 5, BARREL);
		}
		else
		{
			SpawnProjectTile::GetInstance()->SpawnBullet(boss2->GetPositionX(), boss2->GetPositionY(),
				boss2->IsLeft() ? 2 : 6, BARREL);
		}
	}
}

void Boss2State::state_running()
{
	this->SetState(BOSS2_STATE_RUNNING);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_RUNNING];

	boss2->SetSpeedX(boss2->IsLeft() ? -BOSS2_RUN_SPEED : BOSS2_RUN_SPEED);

	if (this->timeCount > BOSS2_RUN_TIME)
	{
		this->timeCount -= BOSS2_RUN_TIME;
		this->state_idle();
		boss2->SetSpeedX(0);
		boss2->SetSpeedY(0);
	}
}

void Boss2State::state_bleeding()
{
	this->SetState(BOSS2_STATE_BLEEDING);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_BLEEDING];
}

void Boss2State::state_standing_punch()
{
	this->SetState(BOSS2_STATE_STANDING_PUNCH);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_STANDING_PUNCH];

	if (this->shootTimeCount > 600)
	{
		this->shootTimeCount = 0;
		int direction = boss2->IsLeft() ? 1 : 5;
		float offsetX = boss2->IsLeft() ? -16 : 16;
		float offsetY = -16;
		SpawnProjectTile::GetInstance()->SpawnBullet(boss2->GetPositionX() + offsetX, boss2->GetPositionY() + offsetY,
			direction, BulletType::BULLET_BOSS2);
	}

	if (this->timeCount > 2000)
	{
		this->timeCount -= 2000;
		this->state_running();
	}
}

void Boss2State::state_hold_barrel()
{
	this->SetState(BOSS2_STATE_HOLD_BARREL);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_HOLD_BARREL];

	if (this->timeCount > BOSS2_HOLD_BARREL_TIME)
	{
		this->timeCount -= 500;
		this->state_throw_barrel();
	}
}

void Boss2State::state_throw_barrel()
{
	this->SetState(BOSS2_STATE_THROW_BARREL);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_THROW_BARREL];

	if (this->timeCount > 500)
	{
		this->timeCount -= 500;
		this->state_standing_punch();
	}
}

void Boss2State::state_loss_head_idle()
{
	this->SetState(BOSS2_STATE_LOSS_HEAD_IDLE);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_LOSS_HEAD_IDLE];
}

void Boss2State::state_loss_head_running()
{
	this->SetState(BOSS2_STATE_LOSS_HEAD_RUNNING);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_LOSS_HEAD_RUNNING];
}

void Boss2State::state_dead()
{
	this->SetState(BOSS2_STATE_DEAD);
	anim = boss2->GetAnimationsList()[BOSS2_STATE_DEAD];
}

void Boss2State::Colision()
{

}

void Boss2State::Update(DWORD dt)
{
	this->timeCount += dt;
	this->shootTimeCount += dt;

	//Update theo state
	switch (stateBoss2)
	{
	case BOSS2_STATE_IDLE:
		this->state_idle();
		break;

	case BOSS2_STATE_RUNNING:
		this->state_running();
		break;

	case BOSS2_STATE_BLEEDING:
		this->state_bleeding();
		break;

	case BOSS2_STATE_STANDING_PUNCH:
		this->state_standing_punch();
		break;

	case BOSS2_STATE_HOLD_BARREL:
		this->state_hold_barrel();
		break;

	case BOSS2_STATE_THROW_BARREL:
		this->state_throw_barrel();
		break;

	case BOSS2_STATE_LOSS_HEAD_IDLE:
		this->state_loss_head_idle();
		break;

	case BOSS2_STATE_LOSS_HEAD_RUNNING:
		this->state_loss_head_running();
		break;

	case BOSS2_STATE_DEAD:
		this->state_dead();
		break;

	default:
		break;
	}
}

void Boss2State::Render()
{
	SpriteData spriteData;
	if (this->boss2 != NULL)
	{
		spriteData.width = BOSS2_SPRITE_WIDTH;
		spriteData.height = BOSS2_SPRITE_HEIGHT;
		spriteData.x = boss2->GetPositionX();
		spriteData.y = boss2->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = boss2->IsLeft();
		spriteData.isFlipped = boss2->IsFlipped();
	}

	anim->Render(spriteData);
}

