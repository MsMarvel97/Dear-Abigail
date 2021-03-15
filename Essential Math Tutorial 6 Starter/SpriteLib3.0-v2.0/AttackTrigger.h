#pragma once
#include "Trigger.h"
class AttackTrigger : public Trigger
{
public:
	void OnTrigger() override;

	void OnEnter() override;
	void OnExit() override;
protected:
};

