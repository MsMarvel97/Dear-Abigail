#pragma once
#include "Trigger.h"

class OrbTrigger : public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;
private:
	//sound
	ToneFire::CoreSound orbVanish{ "objectVanish.wav", false, false, true };
};

class SpecialOrbTrigger : public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;
private:

};
