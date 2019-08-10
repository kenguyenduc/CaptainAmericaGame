#pragma once
#include "Constants.h"
#include "State.h"
#include "Domesto.h"

class Domesto;

class DomestoStayState : public State
{
protected:
	static DomestoStayState * __instance;
	StateDomesto stateDomesto;
	Domesto *domesto;
	Animation * anim;


	float shootTimeCount;
public:
	float timeCount;
	DomestoStayState(Domesto *domesto);
	~DomestoStayState();

	static DomestoStayState * GetInstance(Domesto *domesto);

	//Lấy trạng thái
	StateDomesto GetState();
	//Set trạng thái
	void SetState(StateDomesto State);
	void ChangeStateOverTime(StateDomesto state, float timeOut);

	void state_walking();
	void state_standing_shoot();
	void state_crouch_shoot();
	void state_dead();

	void Colision() override;
	void Update(DWORD dt) override;
	void Render() override;
};
