#pragma once
#include "Trigger.h"
class RespawnTrigger : public Trigger
{
public:
	void OnEnter() override;
	void OnExit() override;

};

