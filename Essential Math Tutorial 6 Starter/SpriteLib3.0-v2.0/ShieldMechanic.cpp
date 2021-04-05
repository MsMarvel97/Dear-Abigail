#include "ShieldMechanic.h"

void ShieldMechanic::activateShield()
{
	if (sequenceStart == false)
	{
		startTime = Timer::time;
	}

	float currentTime = Timer::StopWatch(startTime);

	if (sequenceStart == true)
	{
		if (currentTime < 2)
		{
			shieldOn = true; //turn on shield
			restart = false; //player can't spam shield
		}
		else if (currentTime >= 2 && currentTime < 5)
		{
			shieldOn = false; //turn shield off, this is the cool down period, player can't use the shield during the cool down period
			std::cout << "Shield Off\n";
		}
		else if (currentTime >= 5)
		{
			restart = true; //shield can be activated again.
			sequenceStart = false;
			std::cout << "Shield cool down finished.\n";
		}
	}
}

void ShieldMechanic::setSequenceStart(bool start)
{
	sequenceStart = start;
}

bool ShieldMechanic::getSequenceStart()
{
	return sequenceStart;
}
