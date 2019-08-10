#include "CaptainState.h"
#include <math.h>

CaptainState *CaptainState::__instance = NULL;

CaptainState *CaptainState::GetInstance(Captain *captain)
{
	if (__instance == NULL)
		__instance = new CaptainState(captain);
	return __instance;
}


CaptainState::CaptainState(Captain *captain)
{
	this->captain = captain;
	this->stateCaptain = STATE_JUMPING;
	this->startJumpY == NULL;
	this->startDash == NULL;
	this->captain->SetSpeedY(-CAPTAIN_JUMP_SPEED_Y);
}

CaptainState::~CaptainState()
{
	delete anim;
	delete listSprite;
}

//Lấy trạng thái
StateCaptain CaptainState::GetState()
{
	if (this->stateCaptain == STATE_STANDING)
		int a = 0;
	return this->stateCaptain;
}
//Set trạng thái
void CaptainState::SetState(StateCaptain state)
{
	this->stateCaptain = state;
}

void CaptainState::state_standing()
{
	//Hàm KeyHandle nếu viết class hàm này chỉ set state mới
	if (Keyboard::GetInstance()->IsKeyDown(DIK_Z)) // Bàn phím ấn nút Z thì nhảy
	{
		startJumpY = captain->GetPositionY();
		captain->SetSpeedY(CAPTAIN_JUMP_SPEED_Y);
		this->SetState(STATE_JUMPING); //Chuyển sang trạng thái nhảy
		return;
	}

	if (Keyboard::GetInstance()->IsKeyDown(DIK_C) && startDash == NULL)
	{
		startDash = captain->GetPositionX();
		this->SetState(STATE_DASH);
		return;
	}

	if (Keyboard::GetInstance()->IsKeyDown(DIK_X)) //Tấn công 
	{
		if (captain->IsShield()) // Nếu có khiên
		{
			this->SetState(STATE_THROW_SHIELD); //Ném khiên
			this->state_throw_shield();
			captain->SetIsShield(false);
			return;
		}
		else
		{
			this->state_punch(); //Tạm thời thôi chứ hình như là phải xét bên state ném khiên nếu anim->IsDone() thì chuyển sang đấm
			return;
		}

	}

	if (Keyboard::GetInstance()->IsKeyDown(DIK_RIGHT) || Keyboard::GetInstance()->IsKeyDown(DIK_LEFT)) // Bàn phím nhấn nút trái phải
	{
		this->SetState(STATE_WALKING); //Chuyển sang trạng thái di chuyển
		return;//Phải có return để không làm câu lệnh dưới
	}


	if (Keyboard::GetInstance()->IsKeyDown(DIK_UP))
	{
		this->SetState(STATE_STANDING_UP); //Chuyển sang trạng thái nhìn lên trên
		return;
	}

	if (Keyboard::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		this->SetState(STATE_CROUCH); //Chuyển sang trạng thái ngồi
		return;
	}

	//Hàm Update nếu viết class
		//Logic state Standing
	captain->SetSpeedX(0);
	captain->SetSpeedY(-CAPTAIN_JUMP_SPEED_Y);
	anim = captain->GetAnimationsList()[STATE_STANDING];

	//Hàm Colision sau khi kiểm tra va chạm tổng
		//Xử lý riêng;
}

void CaptainState::state_standing_up()
{
	//HandleKey
	if (Keyboard::GetInstance()->IsKeyDown(DIK_RIGHT) || Keyboard::GetInstance()->IsKeyDown(DIK_LEFT) ||
		Keyboard::GetInstance()->IsKeyDown(DIK_Z) || Keyboard::GetInstance()->IsKeyDown(DIK_X) || //Các state ưu tiên đưa ra trước
		!Keyboard::GetInstance()->IsKeyDown(DIK_UP)) //Không bấm lên thì đổi state
	{
		this->SetState(STATE_STANDING);
		return;
	}

	//Update state
	captain->SetSpeedX(0);
	captain->SetSpeedY(-CAPTAIN_JUMP_SPEED_Y);
	anim = captain->GetAnimationsList()[STATE_STANDING_UP];
}

void CaptainState::state_walking()
{
	captain->SetSpeedY(-CAPTAIN_JUMP_SPEED_Y);
	if (Keyboard::GetInstance()->IsKeyDown(DIK_RIGHT) || Keyboard::GetInstance()->IsKeyDown(DIK_LEFT)) //Ưu tiên qua lại nên để trước
	{
		if (Keyboard::GetInstance()->IsKeyDown(DIK_Z) || Keyboard::GetInstance()->IsKeyDown(DIK_X) || (Keyboard::GetInstance()->IsKeyDown(DIK_C) && startDash == NULL))//Đang đi mà nhảy, tấn công hay dash thì chuyển state
		{
			this->SetState(STATE_STANDING);
			return;
		}

		anim = captain->GetAnimationsList()[STATE_WALKING];
		return;
	}

	this->SetState(STATE_STANDING); //Không bấm gì hết
}

void CaptainState::state_jumping()
{
	//HandleKey
	if (!Keyboard::GetInstance()->IsKeyDown(DIK_Z))
	{
		captain->SetSpeedY(-CAPTAIN_JUMP_SPEED_Y);
	}

	if (this->GetState() == STATE_CROUCH_SHIELD)
	{
		return;
	}
	//Update
	if (this->startJumpY != NULL && captain->GetPositionY() - this->startJumpY >= CAPTAIN_JUMP_MAX)//Nhảy đủ cao thì role
	{
		this->SetState(STATE_JUMPING_ROLE);
		this->state_jumping_role();
		return;
	}

	this->SetState(STATE_JUMPING);

	anim = captain->GetAnimationsList()[STATE_JUMPING];

	if (Keyboard::GetInstance()->IsKeyDown(DIK_X))//Đá
	{
		this->state_jumping_kick();
		return;
	}
}

void CaptainState::state_jumping_role()
{
	//HandleKey
	if (Keyboard::GetInstance()->IsKeyDown(DIK_DOWN) && captain->IsShield())//Ngồi lên khiên
	{
		this->state_crouch_shield();
		return;
	}
	//Update
	captain->SetSpeedY(captain->GetSpeedY() - CAPTAIN_GRAVITY);
	if (captain->GetPositionY() - this->startJumpY < CAPTAIN_JUMP_MAX)
	{
		captain->SetSpeedY(-CAPTAIN_JUMP_SPEED_Y);//Rơi xuống
		this->SetState(STATE_JUMPING);
		this->startJumpY == NULL;
	}
	anim = captain->GetAnimationsList()[STATE_JUMPING_ROLE];

	if (Keyboard::GetInstance()->IsKeyDown(DIK_X))//Đá
	{
		this->state_jumping_kick();
		return;
	}
}

void CaptainState::state_crouch()
{
	//HandleKey
	if (Keyboard::GetInstance()->IsKeyDown(DIK_Z))//bay xuống
	{

		captain->SetPositionY(captain->GetPositionY() - 0.5);
		return;
	}

	if (Keyboard::GetInstance()->IsKeyDown(DIK_X))//ngồi đấm
	{
		this->SetState(STATE_CROUCH_PUNCH);
		return;
	}

	if (Keyboard::GetInstance()->IsKeyDown(DIK_RIGHT) || Keyboard::GetInstance()->IsKeyDown(DIK_LEFT) ||
		Keyboard::GetInstance()->IsKeyDown(DIK_Z) || //Các state ưu tiên đưa ra trước
		!Keyboard::GetInstance()->IsKeyDown(DIK_DOWN)) //Không bấm lên thì đổi state
	{
		this->SetState(STATE_STANDING);
		return;
	}

	//Update state
	captain->SetSpeedX(0);
	captain->SetSpeedY(-CAPTAIN_JUMP_SPEED_Y);
	anim = captain->GetAnimationsList()[STATE_CROUCH];
}

void CaptainState::state_swimming()
{
	this->SetState(STATE_SWIMMING);

	if (Keyboard::GetInstance()->IsKeyDown(DIK_Z)) // Bàn phím ấn nút Z thì nhảy
	{
		startJumpY = captain->GetPositionY();
		captain->SetSpeedY(CAPTAIN_JUMP_SPEED_Y);
		this->SetState(STATE_JUMPING); //Chuyển sang trạng thái nhảy

		captain->SetIsSwimming(false);
		return;
	}

	if (Keyboard::GetInstance()->IsKeyDown(DIK_DOWN) && !Keyboard::GetInstance()->IsKeyDown(DIK_Z)) // Lặn
	{
		this->state_diving();
		return;
	}

	anim = captain->GetAnimationsList()[STATE_SWIMMING];
}

void CaptainState::state_throw_shield()
{
	captain->SetSpeedX(0);
	captain->SetSpeedY(-CAPTAIN_JUMP_SPEED_Y);
	anim = captain->GetAnimationsList()[STATE_THROW_SHIELD];

	if (anim->IsDone())//Hàm isDone hình như bị lỗi
	{
		this->SetState(STATE_PUNCH); //Đấm
		return;
	}
}

void CaptainState::state_punch()
{
	if (Keyboard::GetInstance()->IsKeyDown(DIK_Z))
	{
		this->state_jumping();
		return;
	}

	//Update
	captain->SetSpeedX(0);
	captain->SetSpeedY(-CAPTAIN_JUMP_SPEED_Y);//Lúc nào nó cũng hướng xuống để xét va chạm đất
	anim = captain->GetAnimationsList()[STATE_PUNCH];
	if (anim->IsDone())//Hàm isDone hình như bị lỗi
		this->SetState(STATE_STANDING);
}

void CaptainState::state_jumping_kick()
{
	this->SetState(STATE_JUMPING_KICK);

	//Update
	anim = captain->GetAnimationsList()[STATE_JUMPING_KICK];//Cái này làm cho có thêm thời gian tấn công với event upKey vô

	/*if (anim->IsDone())
	{
		this->SetState(STATE_JUMPING);
	}*/
}
void CaptainState::state_crouch_punch()
{
	//Update
	captain->SetSpeedX(0);
	captain->SetSpeedY(-CAPTAIN_JUMP_SPEED_Y);
	anim = captain->GetAnimationsList()[STATE_CROUCH_PUNCH];

	if (anim->IsDone())
	{
		this->SetState(STATE_CROUCH);
	}
}

void CaptainState::state_crouch_shield()
{
	this->SetState(STATE_CROUCH_SHIELD);

	if (!Keyboard::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		this->SetState(STATE_STANDING);
		this->state_standing();
		return;
	}

	captain->SetSpeedY(-CAPTAIN_JUMP_SPEED_Y);
	captain->SetSpeedX(0);
	anim = captain->GetAnimationsList()[STATE_CROUCH_SHIELD];
}

void CaptainState::state_dash()
{
	captain->SetSpeedX(CAPTAIN_WALK_SPEED * (captain->IsLeft() ? -5 : 5));

	if (startDash != NULL && abs(captain->GetPositionX() - startDash) >= 150)
	{
		this->SetState(STATE_STANDING);
		return;
	}

	if (Keyboard::GetInstance()->IsKeyUp(DIK_C)) // Nhả phím dash
	{
		startDash = NULL;
		this->SetState(STATE_STANDING); //Chuyển sang trạng thái đứng
		return;
	}

	this->SetState(STATE_DASH);
	anim = captain->GetAnimationsList()[STATE_DASH];
}

void CaptainState::state_throw_shield_2()
{
	this->SetState(STATE_THROW_SHIELD_2);
	anim = captain->GetAnimationsList()[STATE_THROW_SHIELD_2];
}

void CaptainState::state_bleeing()
{
	this->SetState(STATE_BLEEING);
	anim = captain->GetAnimationsList()[STATE_BLEEING];
	captain->SetSpeedX(CAPTAIN_WALK_SPEED * (captain->IsLeft() ? 1 : -1));

	if (timeCount >= 100)
	{
		captain->SetSpeedX(0);
		this->state_bleeing_2();
		return;
	}
}

void CaptainState::state_dieing()
{
	this->SetState(STATE_DIEING);
	anim = captain->GetAnimationsList()[STATE_DIEING];
}

void CaptainState::state_diving()
{
	captain->SetSpeedX(0);

	this->SetState(STATE_DIVING);
	anim = captain->GetAnimationsList()[STATE_DIVING];
}

void CaptainState::state_swing()
{
	if (Keyboard::GetInstance()->IsKeyDown(DIK_Z))
	{
		this->SetState(STATE_STANDING);
		this->state_standing();
		captain->SetIsSwing(false);
		return;
	}

	if (Keyboard::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		this->SetState(STATE_JUMPING);
		captain->SetIsSwing(false);
		return;
	}

	if (captain->IsBleeding())
	{
		this->SetState(STATE_BLEEING);
		captain->SetIsSwing(false);
		return;
	}

	anim = captain->GetAnimationsList()[STATE_SWING];

	captain->SetSpeedX(0);
	captain->SetSpeedY(0);
}

void CaptainState::state_bleeing_2()
{
	this->SetState(STATE_BLEEING_2);
	anim = captain->GetAnimationsList()[STATE_BLEEING_2];

	if (Keyboard::GetInstance()->IsKeyDown(DIK_Z) || Keyboard::GetInstance()->IsKeyDown(DIK_X))
	{
		this->SetState(STATE_STANDING);
		this->state_standing();
		return;
	}

	if (timeCount >= 300)
	{
		timeCount = 0;
		this->SetState(STATE_STANDING);
		captain->SetIsBleeding(false);
		return;
	}
}

void CaptainState::KeyHandle()
{
	//Do viết hàm nên không có lệnh
}

void CaptainState::Colision()
{
	if (Keyboard::GetInstance()->IsKeyUp(DIK_C)) // Nhả phím dash
	{
		startDash = NULL;
	}

	if (captain->IsBleeding())
	{
		this->state_bleeing();
	}

	//Không chạm đất thì rơi
	if (!captain->IsGrounded())
	{
		this->state_jumping();
	}
	else if (this->GetState() == STATE_JUMPING || this->GetState() == STATE_JUMPING_ROLE || this->GetState() == STATE_JUMPING_KICK)
	{
		if (captain->GetSpeedY() < 0)
		{
			this->SetState(STATE_STANDING);
			this->state_standing();
		}
	}

	//Nếu chạm sông thì bơi
	if (captain->IsSwimming())
	{
		this->SetState(STATE_SWIMMING);
		this->state_swimming();
	}

	//Đu dây
	if (captain->IsSwing())
	{
		this->SetState(STATE_SWING);
	}

	captain->SetIsGrounded(false);
}

void CaptainState::Update(DWORD dt)
{
	timeCount += dt;
	//Kiểm tra tốc độ trục X
	if (Keyboard::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		captain->setIsLeft(false);
		captain->SetSpeedX(CAPTAIN_WALK_SPEED * (captain->IsLeft() ? -1 : 1));
	}
	else if (Keyboard::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		captain->setIsLeft(true);
		captain->SetSpeedX(CAPTAIN_WALK_SPEED * (captain->IsLeft() ? -1 : 1));
	}
	else
		captain->SetSpeedX(0);

	if (captain->GetPositionX() < 10)
		captain->SetPositionX(10);

	//Update theo state
	switch (stateCaptain)
	{
	case STATE_STANDING:
		this->state_standing();
		break;

	case STATE_STANDING_UP:
		this->state_standing_up();
		break;

	case STATE_WALKING:
		this->state_walking();
		break;

	case STATE_JUMPING:
		this->state_jumping();
		break;

	case STATE_JUMPING_ROLE:
		this->state_jumping_role();
		break;

	case STATE_CROUCH:
		this->state_crouch();
		break;

	case STATE_SWIMMING:
		this->state_swimming();
		break;

	case STATE_THROW_SHIELD:
		this->state_throw_shield();
		break;

	case STATE_PUNCH:
		this->state_punch();
		break;

	case STATE_JUMPING_KICK:
		this->state_jumping_kick();
		break;

	case STATE_CROUCH_PUNCH:
		this->state_crouch_punch();
		break;

	case STATE_CROUCH_SHIELD:
		this->state_crouch_shield();
		break;

	case STATE_DASH:
		this->state_dash();
		break;

	case STATE_THROW_SHIELD_2:
		this->state_throw_shield_2();
		break;

	case STATE_BLEEING:
		this->state_bleeing();
		break;

	case STATE_DIEING:
		this->state_dieing();
		break;

	case STATE_DIVING:
		this->state_diving();
		break;

	case STATE_BLEEING_2:
		this->state_bleeing_2();
		break;

	case STATE_SWING:
		this->state_swing();
		break;

	default:
		break;
	}
}

void CaptainState::Render()
{
	SpriteData spriteData;
	if (this->captain != NULL)
	{
		spriteData.width = CAPTAIN_SPRITE_WIDTH;
		spriteData.height = CAPTAIN_SPRITE_HEIGHT;
		spriteData.x = captain->GetPositionX();
		spriteData.y = captain->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = captain->IsLeft();
		spriteData.isFlipped = captain->IsFlipped();
	}

	anim->Render(spriteData);
}

