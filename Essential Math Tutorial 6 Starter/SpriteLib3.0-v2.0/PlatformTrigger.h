#pragma once
#include "Trigger.h"
#include "ECS.h"

class VerticalPlatformTrigger :
	public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;
};

