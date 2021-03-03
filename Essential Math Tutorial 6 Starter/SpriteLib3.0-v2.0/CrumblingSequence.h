#pragma once
#include "ECS.h"
#include "Timer.h"
class CrumblingSequence
{
public:
	void Crumble();
	bool sequenceStart = false;
	int entity = 0;

	void setEntity(int newEntity);
	void setSequenceStart(bool start);
	bool getSequenceStart();

	int disablePlatform();
	bool disable = false;
	int operation = 0;

	float startTime = 0.f;
};

