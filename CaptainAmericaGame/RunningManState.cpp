#include "RunningManState.h"
#include <math.h>

RunningManState * RunningManState::__instance = NULL;

RunningManState *RunningManState::GetInstance(RunningMan *runningMan)
{
	if (__instance == NULL)
		__instance = new RunningManState(runningMan);
	return __instance;
}


RunningManState::RunningManState(RunningMan *runningMan)
{
	this->runningMan = runningMan;

	switch (runningMan->GetRunningManType())
	{
	case RunningManType::ONLY_CROUCH:
		this->state_crouch_shoot();
		break;
	case RunningManType::NORMAL:
	case RunningManType::ONLY_RUN:
		this->state_running();
		break;
	}

}

RunningManState::~RunningManState()
{
	delete anim;
}

//Lấy trạng thái
StateRunningMan RunningManState::GetState()
{
	return this->stateRunningMan;
}
//Set trạng thái
void RunningManState::SetState(StateRunningMan state)
{
	this->stateRunningMan = state;
}

void RunningManState::state_running()
{
	this->SetState(RUNNING_MAN_STATE_RUNNING);
	anim = runningMan->GetAnimationsList()[RUNNING_MAN_STATE_RUNNING];

	runningMan->SetSpeedX(CAPTAIN_WALK_SPEED * (runningMan->IsLeft() ? -1 : 1));

	if (!Captain::GetInstance()->IsShield()
		&& ((runningMan->IsLeft() && !Captain::GetInstance()->IsLeft() && runningMan->GetPositionX() > Captain::GetInstance()->GetPositionX())
			|| (!runningMan->IsLeft() && Captain::GetInstance()->IsLeft() && runningMan->GetPositionX() < Captain::GetInstance()->GetPositionX())))
	{
		runningMan->SetSpeedY(CAPTAIN_JUMP_SPEED_Y * 2);
		runningMan->SetIsGrounded(false);
		this->state_jumping();
		return;
	}

	switch (runningMan->GetRunningManType())
	{
	case RunningManType::NORMAL:
		if (this->timeCount > RUNNING_MAN_TIME_OUT_RUN)
		{
			this->timeCount = 0;
			this->state_standing_shoot();
		}
		break;
	case RunningManType::ONLY_CROUCH:
		// Type này thì không chuyển sang state CROUCH được
		break;
	case RunningManType::ONLY_RUN:
		// Nếu là type ONLY_RUN thì không đi vào state nào khác
		break;
	}
}

void RunningManState::state_standing_shoot()
{
	this->SetState(RUNNING_MAN_STATE_STANDING_SHOOT);
	anim = runningMan->GetAnimationsList()[RUNNING_MAN_STATE_STANDING_SHOOT];

	runningMan->SetSpeedX(0);

	if (this->shootTimeCount > RUNNING_MAN_TIME_OUT_STAND * 1.5)
	{
		this->shootTimeCount = 0;
		int direction = runningMan->IsLeft() ? 1 : 5;
		float offsetX = runningMan->IsLeft() ? -16 : 16;
		float offsetY = -3;
		SpawnProjectTile::GetInstance()->SpawnBullet(runningMan->GetPositionX() + offsetX, runningMan->GetPositionY() + offsetY,
			direction, BulletType::BULLET_NORMAL);
	}

	if (this->timeCount > RUNNING_MAN_TIME_OUT_STAND)
	{
		this->timeCount = 0;
		this->shootTimeCount = 0;
		switch (runningMan->GetRunningManType())
		{
		case RunningManType::NORMAL:
			this->state_running();
			break;
		case RunningManType::ONLY_CROUCH:
			this->state_crouch_shoot();
			break;
		case RunningManType::ONLY_RUN:
			// Nếu là type ONLY_RUN thì không đi vào state này được
			break;
		}
	}
}

void RunningManState::state_crouch_shoot()
{
	this->SetState(RUNNING_MAN_STATE_CROUCH_SHOOT);
	anim = runningMan->GetAnimationsList()[RUNNING_MAN_STATE_CROUCH_SHOOT];

	runningMan->SetSpeedX(0);

	if (this->timeCount > RUNNING_MAN_TIME_OUT_CROUCH)
	{
		this->timeCount = 0;
		this->state_standing_shoot();
	}
}

void RunningManState::state_dead()
{
	this->SetState(RUNNING_MAN_STATE_DEAD);
	anim = runningMan->GetAnimationsList()[RUNNING_MAN_STATE_DEAD];
	runningMan->SetSpeedX(0);
	runningMan->SetSpeedY(0);

	if (this->timeCount > 200)
		anim = runningMan->GetAnimationsList()[4];

	if (this->timeCount > 350)
		runningMan->disable = true;
}


void RunningManState::state_jumping()
{
	this->SetState(RUNNING_MAN_STATE_JUMPING);
	anim = runningMan->GetAnimationsList()[RUNNING_MAN_STATE_CROUCH_SHOOT];

	if (runningMan->IsGrounded())
	{
		this->SetState(RUNNING_MAN_STATE_STANDING_SHOOT);
		return;
	}
}

void RunningManState::Colision()
{

}

void RunningManState::Update(DWORD dt)
{
	// Cap nhat Delta Time
	this->dt = dt;

	this->timeCount += dt;
	this->shootTimeCount += dt;
	//Update theo state
	switch (stateRunningMan)
	{
	case RUNNING_MAN_STATE_RUNNING:
		this->state_running();
		break;

	case RUNNING_MAN_STATE_STANDING_SHOOT:
		this->state_standing_shoot();
		break;

	case RUNNING_MAN_STATE_CROUCH_SHOOT:
		this->state_crouch_shoot();
		break;

	case RUNNING_MAN_STATE_DEAD:
		this->state_dead();
		break;

	case RUNNING_MAN_STATE_JUMPING:
		this->state_jumping();
		break;

	default:
		break;
	}
}

void RunningManState::Render()
{
	SpriteData spriteData;
	if (this->runningMan != NULL)
	{
		spriteData.width = ENEMIES_SPRITE_WIDTH;
		spriteData.height = ENEMIES_SPRITE_HEIGHT;
		spriteData.x = runningMan->GetPositionX();
		spriteData.y = runningMan->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = runningMan->IsLeft();
		spriteData.isFlipped = runningMan->IsFlipped();
	}

	anim->Render(spriteData);
}

