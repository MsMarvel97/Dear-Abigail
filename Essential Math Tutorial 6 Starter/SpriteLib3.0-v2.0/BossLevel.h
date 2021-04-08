#pragma once
#include "ECS.h"
class BossLevel
{
public:
	void CheckBossStatus();
	void OrbDestroyed();
	void SetHit(bool damaged) { hit = damaged; };
	bool GetBossDefeated();

private:
	bool bossDefeated = false;
	bool hit = false;
	int orbs = 5;	
};

