#include "Movement.h"

bool Movement::GetMove()
{
    return canMove;
}

void Movement::SetMove(bool newMove)
{
    canMove = newMove;
}

void Movement::SuspendMovement()
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
			canMove = true;
			sequenceStart = false;
		}
		else
		{
			canMove = false;
		}
	}
}

void Movement::setSequenceStart(bool start)
{
    sequenceStart = start;
}

bool Movement::getSequenceStart()
{
    return sequenceStart;
}
