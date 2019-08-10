#pragma once
#include "Constants.h"
#include "State.h"
#include "RedBox.h"

class RedBox;
enum StateRedBox
{
	RED_BOX_STATE_CLOSE,
	RED_BOX_STATE_OPEN,
	RED_BOX_MAP_2_STATE_CLOSE,
	RED_BOX_MAP_2_STATE_OPEN,
};

class RedBoxState : public State
{
protected:
	static RedBoxState * __instance;
	StateRedBox stateRedBox;
	RedBox *redbox;
	Animation * anim;

	DWORD dt;

	bool isSpawn = false;
public:
	RedBoxState(RedBox *redbox);
	~RedBoxState();

	float timeCount;

	static RedBoxState * GetInstance(RedBox *redbox);

	//Lấy trạng thái
	StateRedBox GetState();
	//Set trạng thái
	void SetState(StateRedBox State);

	bool IsSpawn() { return this->isSpawn; }
	void SetIsSpawn(bool isSpawn) { this->isSpawn = isSpawn; }

	void state_close();
	void state_open();

	void Colision() override;
	void Update(DWORD dt) override;
	void Render() override;
};
