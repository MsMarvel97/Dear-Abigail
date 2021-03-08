#include "AttackMechanic.h"

void AttackMechanic::Attacking() //runs a timer for when the player is in an attacking state
{
	if (sequenceStart == false)
	{
		startTime = Timer::time;
	}
	float currentTime = Timer::StopWatch(startTime);

	if (sequenceStart == true) //this statement will run once the player has entered a ShadowAreaTrigger
	{

		if (currentTime > 3)
		{
			isAttacking = false;
			std::cout << "Attack end\n";
			setSequenceStart(false);
		}
		else
		{
			isAttacking = true;
		}
	}
}

bool AttackMechanic::GetRange()
{
    return inRange;
}

void AttackMechanic::SetRange(bool newRange)
{
    inRange = newRange;
}

int AttackMechanic::GetShadow()
{
    return shadow;
}

void AttackMechanic::SetShadow(int newShadow)
{
    shadow = newShadow;
}

void AttackMechanic::setSequenceStart(bool start)
{
    sequenceStart = start;
}

bool AttackMechanic::getSequenceStart()
{
    return sequenceStart;
}