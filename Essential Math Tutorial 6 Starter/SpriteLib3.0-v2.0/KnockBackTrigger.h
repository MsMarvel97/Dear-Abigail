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

class SpikeTrigger : public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;
protected:
};

