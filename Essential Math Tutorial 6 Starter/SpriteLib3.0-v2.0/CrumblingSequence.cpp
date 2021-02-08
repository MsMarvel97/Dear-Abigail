#include "CrumblingSequence.h"

void CrumblingSequence::Crumble()
{
	static float startTime = 0.f;
	if (sequenceStart == false)
	{
		startTime = Timer::time;
	}
	float currentTime = Timer::StopWatch(startTime);
	if (sequenceStart == true)
	{
		if (currentTime < 3)
		{

		}
		else if (currentTime >= 3 && currentTime < 5)
		{
			operation = 1;
			disable = true;
			//ECS::GetComponent<Sprite>(entity).SetTransparency(0.4f);
		}
		else if (currentTime >= 5)
		{
			operation = 0;
			disable = true;
			//ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
			startTime = 0;
			sequenceStart = false;
		}
	}
	
}

void CrumblingSequence::setEntity(int newEntity)
{
	entity = newEntity;
}

void CrumblingSequence::setSequenceStart(bool start)
{
	sequenceStart = start;
}

bool CrumblingSequence::getSequenceStart()
{
	return sequenceStart;
}

int CrumblingSequence::disablePlatform()
{
	if (disable == true)
	{
		return operation;
	}
	else
	{
		return -1;
	}
}

