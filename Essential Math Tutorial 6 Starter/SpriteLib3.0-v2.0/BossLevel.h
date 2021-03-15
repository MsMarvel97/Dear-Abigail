#pragma once
#include "ECS.h"
class BossLevel
{
public:
	void CheckBossStatus();
	int GetOrbs();
	void SetOrbs(int orbsCount);
	void OrbDestroyed();
	bool GetBossDefeated();
	void SetBossDefeated(bool updateBoss);
private:
	bool bossDefeated = false;
	int orbs = 5;
};

