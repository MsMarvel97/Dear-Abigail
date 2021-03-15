#pragma once
#include "ECS.h"
class Health
{
public:
<<<<<<< HEAD

=======
	int GetHealth(); //returns player's health

	void SetHealth(int newHealth); //sets the player's health
>>>>>>> AngerLevel

	void HealthLost(); //reduces player hearts by 1

	bool getShield();

	void setShield(bool newShield);

<<<<<<< HEAD
	int GetHealth(); //returns player's health

	void SetHealth(int newHealth); //sets the player's health
=======
	bool GetRespawn();
	void SetRespawn(bool newRespawn);
>>>>>>> AngerLevel

private:
	int hearts = 3; //player's life points
	bool isShieldOn = false; //used by the bullet trigger
<<<<<<< HEAD
=======
	bool respawn = false;
>>>>>>> AngerLevel
};

