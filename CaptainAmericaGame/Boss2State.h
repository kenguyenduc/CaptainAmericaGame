#pragma once
#include "Constants.h"
#include "State.h"
#include "Boss2.h"

class Boss2;
enum StateBoss2
{
	BOSS2_STATE_IDLE,//Đứng 
	BOSS2_STATE_RUNNING,//Chạy
	BOSS2_STATE_STANDING_PUNCH,//Đứng đấm
	BOSS2_STATE_HOLD_BARREL,//Bê thùng
	BOSS2_STATE_THROW_BARREL,//Ném thùng
	BOSS2_STATE_BLEEDING,//Bị thương
	BOSS2_STATE_LOSS_HEAD_IDLE,//Mất đầu
	BOSS2_STATE_LOSS_HEAD_RUNNING,//Chạy khi mất đầu
	BOSS2_STATE_DEAD,
};

class Boss2State : public State
{
protected:
	static Boss2State * __instance;
	StateBoss2 stateBoss2;
	Boss2 *boss2;
	Animation * anim;

	float runTime;

	float shootTimeCount;
public:

	float timeCount;

	Boss2State(Boss2 *boss2);
	~Boss2State();

	static Boss2State * GetInstance(Boss2 *boss2);

	//Lấy trạng thái
	StateBoss2 GetState();
	//Set trạng thái
	void SetState(StateBoss2 State);

	void state_idle();
	void state_running();
	void state_standing_punch();
	void state_hold_barrel();
	void state_throw_barrel();
	void state_bleeding();
	void state_loss_head_idle();
	void state_loss_head_running();
	void state_dead();

	void Colision() override;
	void Update(DWORD dt) override;
	void Render() override;
};
