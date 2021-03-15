#pragma once
#include "Trigger.h"
class BreakableWallTrigger : public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;
};

