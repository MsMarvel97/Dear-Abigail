#include "CoolDown.h"
void CoolDown::GlobalCoolDown()
{
	if (sequenceStart == false)
	{
		startTime = Timer::time;
	}
	float currentTime = Timer::StopWatch(startTime);

	if (sequenceStart == true)
	{

		if (currentTime > 5)
		{
			isCoolDownActive = false;
			std::cout << "cool down end\n";
			SetSequenceStart(false);
		}
		else
		{
			isCoolDownActive = true;
		}
	}
}
void CoolDown::SetSequenceStart(bool start)
{
	sequenceStart = start;
}

bool CoolDown::GetSequenceStart()
{
	return sequenceStart;
}
