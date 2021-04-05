#include "BossLevel.h"

void BossLevel::CheckBossStatus()
{
    if (orbs == 0)
    {
        bossDefeated = true;
    }
}

int BossLevel::GetOrbs()
{
    return orbs;
}

void BossLevel::SetOrbs(int orbsCount)
{
    orbs = orbsCount;
}

void BossLevel::OrbDestroyed()
{
    orbs--;
}

bool BossLevel::GetBossDefeated()
{
    return bossDefeated;
}

void BossLevel::SetBossDefeated(bool updateBoss)
{
    bossDefeated = updateBoss;
}
