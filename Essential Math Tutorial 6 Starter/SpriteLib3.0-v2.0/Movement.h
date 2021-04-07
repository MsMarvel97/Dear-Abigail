#pragma once
#include "ECS.h"
#include "Timer.h"
class Movement
{
public:
	bool GetMove();
	void SetMove(bool newMove);
	void SuspendMovement();
	void setSequenceStart(bool start);
	bool getSequenceStart();
	float startTime = 0.f;
private:
	bool canMove = true;
	bool sequenceStart = false;
};

