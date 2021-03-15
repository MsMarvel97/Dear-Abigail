#include "Health.h"

int Health::GetHealth()
{
    return hearts;
}

void Health::SetHealth(int newHealth)
{
    hearts = newHealth;
}

void Health::HealthLost()
{
    hearts--;
}

bool Health::getShield()
{
    return isShieldOn;
}

void Health::setShield(bool newShield)
{
    isShieldOn = newShield;
}

bool Health::GetRespawn()
{
    return respawn;
}

void Health::SetRespawn(bool newRespawn)
{
    respawn = newRespawn;
}
