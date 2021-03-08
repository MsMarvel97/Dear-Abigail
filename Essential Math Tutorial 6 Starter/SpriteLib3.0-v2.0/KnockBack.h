#pragma once
#include "ECS.h"
#include "Timer.h"
class KnockBack
{
public:
	void RunKnockBackTime();
	void SetSequenceStart(bool start);
	bool GetSequenceStart();
	float startTime = 0.f;
	bool GetCanMove();
	void SetCanMove(bool newBool);
private:
	bool sequenceStart = false;
	bool canMove = true;
};

