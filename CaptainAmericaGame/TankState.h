#pragma once
#include "Constants.h"
#include "State.h"
#include "Tank.h"

class Tank;

class TankState : public State
{
protected:
	static TankState * __instance;
	Tank *tank;
	Animation * anim;

	// 1:Left	2:B-L	3:Bottom	4:B-R	5:Right	6:T-R	7:Top	8:T-L
	int direction;
public:
	float timeCount;
	float shootTimeCount;

	TankState(Tank *tank);
	~TankState();

	int GetDirection() { return this->direction; }
	void SetDirection(int direction) { this->direction = direction; }

	static TankState * GetInstance(Tank *tank);

	void state_bleeding();
	void state_left();
	void state_bottom_left();
	void state_bottom();
	void state_bottom_right();
	void state_right();
	void state_top_right();
	void state_top();
	void state_top_left();

	void Colision() override;
	void Update(DWORD dt) override;
	void Render() override;
};
