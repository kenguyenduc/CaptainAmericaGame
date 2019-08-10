#pragma once
#include "Constants.h"
#include "State.h"
#include "Gigi.h"

class Gigi;
enum StateGigi
{
	GIGI_STATE_FLYING, //Bay
	GIGI_STATE_DEAD, //chết
};

class GigiState : public State
{
protected:
	static GigiState * __instance;
	StateGigi stateGigi;
	Gigi *gigi;
	Animation * anim;
public:
	float timeCount;
	float shootTimeCount;
	float disableTimeCount;

	GigiState(Gigi *gigi);
	~GigiState();

	static GigiState * GetInstance(Gigi *gigi);

	//Lấy trạng thái
	StateGigi GetState();
	//Set trạng thái
	void SetState(StateGigi State);

	void state_flying();
	void state_dead();

	void Colision() override;
	void Update(DWORD dt) override;
	void Render() override;
};
