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

class BossShadow : public Trigger
{
	void OnEnter() override;
	void OnExit() override;
};

class SpikeTrigger : public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;
protected:
};

