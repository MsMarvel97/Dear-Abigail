#include "ShadowTime.h"

void ShadowTime::RunShadowTime() //this function is being continuously called in the update function
{
	if (sequenceStart == false)
	{
		target = 2;
		startTime = Timer::time;
	}
	float currentTime = Timer::StopWatch(startTime);
	
	if (sequenceStart == true) //this statement will run once the player has entered a ShadowAreaTrigger
	{
		if (currentTime > target)
		{
			fire = true;
			target += 2;
		}
		else
		{
			fire = false;
		}
	}
}
void ShadowTime::setSequenceStart(bool start)
{
	sequenceStart = start;
}

bool ShadowTime::getSequenceStart()
{
	return sequenceStart;
}