#pragma once

#include "Trigger.h"

class ShadowAreaTrigger : public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;
	bool isBoss = false;
protected:
	
};

class BossAreaTrigger : public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;
	bool isBoss = false;
protected:

	//Sound Library


};

