#pragma once
#include "ECS.h"
class BossLevel
{
public:
	void CheckBossStatus();
	void OrbDestroyed();
	bool GetBossDefeated();
private:
	bool bossDefeated = false;
	int orbs = 5;
};

