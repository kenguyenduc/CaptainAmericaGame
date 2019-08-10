#pragma once
#include "Constants.h"
#include "State.h"
#include "Bat.h"

class Bat;
enum StateBat
{
	BAT_STATE_IDLE,//đứng yên
	BAT_STATE_GOING_TO_FLY,//chuẩn bị bay
	BAT_STATE_FLYING,//bay
	BAT_STATE_DEAD, //chết
};

class BatState : public State
{
protected:
	static BatState * __instance;
	StateBat stateBat;
	Bat *bat;
	Animation * anim;
	DWORD dt;

	int flyStage;
public:
	float timeCount;
	float timeChangeFlyState;
	float disableTimeCount;

	BatState(Bat *bat);
	~BatState();

	static BatState * GetInstance(Bat *bat);

	//Lấy trạng thái
	StateBat GetState();
	//Set trạng thái
	void SetState(StateBat State);

	void state_idle();
	void state_going_to_fly();
	void state_flying();
	void state_dead();

	void Colision() override;
	void Update(DWORD dt) override;
	void Render() override;
};
