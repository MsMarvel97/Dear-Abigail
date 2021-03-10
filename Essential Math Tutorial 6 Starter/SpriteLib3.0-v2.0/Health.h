#pragma once
#include "ECS.h"
class Health
{
public:


	void HealthLost(); //reduces player hearts by 1

	bool getShield();

	void setShield(bool newShield);

	int GetHealth(); //returns player's health

	void SetHealth(int newHealth); //sets the player's health

private:
	int hearts = 3; //player's life points
	bool isShieldOn = false; //used by the bullet trigger
};

