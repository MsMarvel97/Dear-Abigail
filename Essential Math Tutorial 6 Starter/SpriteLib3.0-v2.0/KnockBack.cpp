#include "KnockBack.h"

void KnockBack::RunKnockBackTime()
{
	if (sequenceStart == false)
	{
		startTime = Timer::time;
	}
	float currentTime = Timer::StopWatch(startTime);

	if (sequenceStart == true) //this statement will run once the player has entered a ShadowAreaTrigger
	{

		if (currentTime < 2)
		{
			canMove = false;
		}
		else
		{
			canMove = true;
<<<<<<< HEAD
			sequenceStart = false;
=======
			SetSequenceStart(false);
>>>>>>> AngerLevel
		}
	}
}

void KnockBack::SetSequenceStart(bool start)
{
    sequenceStart = start;
}

bool KnockBack::GetSequenceStart()
{
    return sequenceStart;
}

bool KnockBack::GetCanMove()
{
	return canMove;
}

void KnockBack::SetCanMove(bool newBool)
{
	canMove = newBool;
}
