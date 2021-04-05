#pragma once
#include "Trigger.h"

class OrbTrigger : public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;
private:
};

class SpecialOrbTrigger : public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;
private:
};
