#pragma once
#include "Trigger.h"
#include "ECS.h"

class KnockBackTrigger : public Trigger
{
public:
	void OnTrigger() override;
	void OnEnter() override;
	void OnExit() override;
protected:
};

