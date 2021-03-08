#pragma once
#include "ECS.h"
#include "Timer.h"
class ShadowTime
{
public:
	void RunShadowTime();
	
	void setSequenceStart(bool start);
	bool getSequenceStart();
	bool fire = false;
	double target = 4;
	bool sequenceStart = false;
	float startTime = 0.f;
};

