#pragma once
#include "Trigger.h"
class KnockBackTrigger : public Trigger
{
public:
	void OnTrigger() override;
	void OnEnter() override;
	void OnExit() override;
protected:
};

