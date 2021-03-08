#pragma once
#include "ECS.h"
#include "Timer.h"
class ShieldMechanic
{
public:
	void activateShield();
	bool sequenceStart = false;
	void setSequenceStart(bool start);
	bool getSequenceStart();
	bool restart = true;
	bool shieldOn = false;

	float startTime = 0.f;
};

