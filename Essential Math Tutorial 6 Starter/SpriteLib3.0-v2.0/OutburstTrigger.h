#pragma once
#include "Trigger.h"
class OutburstTrigger : public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;
protected:
	bool triggered = false;
};

