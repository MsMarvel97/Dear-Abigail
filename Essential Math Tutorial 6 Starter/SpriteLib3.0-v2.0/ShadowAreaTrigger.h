#pragma once

#include "Trigger.h"

class ShadowAreaTrigger : public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;
protected:
};

