#pragma once
#include "ECS.h"
#include "Timer.h"
class AttackMechanic
{
public:
	void Attacking();
	bool GetRange();
	void SetRange(bool newRange);
	
	int GetShadow();
	void SetShadow(int newShadow);
	void setSequenceStart(bool start);
	bool getSequenceStart();
	float startTime = 0.f;
	bool isAttacking = false;
private:
	bool inRange = false;
	int shadow = 0;
	bool sequenceStart = false;

	//Sound Library
};

