#include "RedBoxState.h"
#include <math.h>

RedBoxState * RedBoxState::__instance = NULL;

RedBoxState *RedBoxState::GetInstance(RedBox *redbox)
{
	if (__instance == NULL)
		__instance = new RedBoxState(redbox);
	return __instance;
}


RedBoxState::RedBoxState(RedBox *redbox)
{
	this->redbox = redbox;
	this->state_close();
	//this->SetIsSpawn(true);
}

RedBoxState::~RedBoxState()
{
	delete anim;
}

//Lấy trạng thái
StateRedBox RedBoxState::GetState()
{
	return this->stateRedBox;
}
//Set trạng thái
void RedBoxState::SetState(StateRedBox state)
{
	this->stateRedBox = state;
}

void RedBoxState::state_close()
{
	this->SetIsSpawn(true);

	this->SetState(RED_BOX_STATE_CLOSE);

	switch (redbox->GetType())
	{
	case RedBoxType::MAP_1:
		anim = redbox->GetAnimationsList()[RED_BOX_STATE_CLOSE];
		break;
	case RedBoxType::MAP_2:
		anim = redbox->GetAnimationsList()[RED_BOX_MAP_2_STATE_CLOSE];
		break;
	}
}

void RedBoxState::state_open()
{
	this->SetState(RED_BOX_STATE_OPEN);

	switch (redbox->GetType())
	{
	case RedBoxType::MAP_1:
		anim = redbox->GetAnimationsList()[RED_BOX_STATE_OPEN];
		break;
	case RedBoxType::MAP_2:
		anim = redbox->GetAnimationsList()[RED_BOX_MAP_2_STATE_OPEN];
		break;
	}

	if (IsSpawn())
	{
		srand((int)time(0));
		SpawnProjectTile::GetInstance()->SpawnItem(redbox->GetPositionX(), redbox->GetPositionY(), ItemType(rand() % 5 + 0));
		this->SetIsSpawn(false);
	}

	if (this->timeCount > 500)
	{
		this->SetState(RED_BOX_STATE_CLOSE);
	}
}

void RedBoxState::Colision()
{

}

void RedBoxState::Update(DWORD dt)
{
	// Cap nhat Delta Time
	this->dt = dt;

	this->timeCount += dt;

	//Update theo state
	switch (stateRedBox)
	{
	case RED_BOX_STATE_CLOSE:
		this->state_close();
		break;

	case RED_BOX_STATE_OPEN:
		this->state_open();
		break;

	default:
		break;
	}
}

void RedBoxState::Render()
{
	SpriteData spriteData;
	if (this->redbox != NULL)
	{
		spriteData.width = TILES_WIDTH_PER_TILE;
		spriteData.height = TILES_HEIGHT_PER_TILE;
		spriteData.x = redbox->GetPositionX();
		spriteData.y = redbox->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = redbox->IsLeft();
		spriteData.isFlipped = redbox->IsFlipped();
	}

	anim->Render(spriteData);
}

