#pragma once
#include "ECS.h"
class Health
{
public:
	int GetHealth(); //returns player's health

	void SetHealth(int newHealth); //sets the player's health

	void HealthLost(); //reduces player hearts by 1

	bool getShield();

	void setShield(bool newShield);

	bool GetRespawn();
	void SetRespawn(bool newRespawn);

private:
	int hearts = 3; //player's life points
	bool isShieldOn = false; //used by the bullet trigger
	bool respawn = false;
};

