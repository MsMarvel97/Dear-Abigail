#pragma once
#include "ECS.h"
#include "Timer.h"
class ShadowLoop
{
public:
	void ShadowRoutine();
	void setSequenceStart(bool start);
	bool getSequenceStart();
	float startTime = 0.f;

	bool s_resting = true;
	bool s_charging = true;
	bool s_attacking = true;

	bool isShadowAlive = true;
private:
	bool sequenceStart = false;

};

