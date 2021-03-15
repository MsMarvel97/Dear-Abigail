#include "ShadowLoop.h"

void ShadowLoop::ShadowRoutine()
{
	if (sequenceStart == false)
	{
		startTime = Timer::time;
	}
	float currentTime = Timer::StopWatch(startTime);

	if (sequenceStart == true) //this statement will run once the player has entered a ShadowAreaTrigger
	{

		if (currentTime >= 0 && currentTime < 3) //resting
		{
			//std::cout << "Resting" << "\n";
			s_resting = true;
			s_charging = false;
			s_attacking = false;
	
		}
		else if (currentTime > 3 && currentTime < 5) //charging 
		{
			//std::cout << "Charging" << "\n";
			s_resting = false;
			s_charging = true;
			s_attacking = false;
		}
		else if (currentTime > 5 && currentTime < 7) //attacking
		{
			//std::cout << "Attacking" << "\n";
			s_resting = false;
			s_charging = false;
			s_attacking = true;
		}
		else
		{
			currentTime = 0.f;
			startTime = Timer::time;
		}
	}
}
void ShadowLoop::setSequenceStart(bool start)
{
    sequenceStart = start;
}

bool ShadowLoop::getSequenceStart()
{
    return sequenceStart;
}