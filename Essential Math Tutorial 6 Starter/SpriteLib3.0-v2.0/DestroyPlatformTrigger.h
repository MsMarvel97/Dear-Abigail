#pragma once
#include "Trigger.h"
class DestroyPlatformTrigger : public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;
	float startTime = 0.f;
};

