#pragma once
#include "ECS.h"
#include "Timer.h"
class CoolDown
{
public: 
	void GlobalCoolDown();
	void SetSequenceStart(bool start);
	bool GetSequenceStart();
	float startTime = 0.f;
	bool isCoolDownActive = false;
	bool shieldCoolDown = false;
	bool attackCoolDown = false;
private:
	bool sequenceStart = false;
};

