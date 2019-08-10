#pragma once
#include "Constants.h"
#include "State.h"
#include "Domesto.h"

class Domesto;

class DomestoWalkState : public State
{
protected:
	static DomestoWalkState * __instance;
	StateDomesto stateDomesto;
	StateDomesto previousStateDomesto;
	Domesto *domesto;
	Animation * anim;


	float shootTimeCount;
public:

	float timeCount;
	DomestoWalkState(Domesto *domesto);
	~DomestoWalkState();

	static DomestoWalkState * GetInstance(Domesto *domesto);

	//Lấy trạng thái
	StateDomesto GetState();
	//Set trạng thái
	void SetState(StateDomesto State);
	bool ChangeStateOverTime(StateDomesto state, float timeOut);

	void state_walking();
	void state_standing_shoot();
	void state_crouch_shoot();
	void state_dead();
	void state_jumping();

	void Colision() override;
	void Update(DWORD dt) override;
	void Render() override;
};
