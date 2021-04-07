#include "BossLevel.h"

void BossLevel::CheckBossStatus()
{
    if (orbs == 0)
    {
        bossDefeated = true;
    }
}

void BossLevel::OrbDestroyed()
{
    orbs--;
}

bool BossLevel::GetBossDefeated()
{
    return bossDefeated;
}