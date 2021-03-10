#pragma once
#include "ECS.h"

class PlayerMechanics
{
public:
	//New mechanics\\
	//Shadow tracking
	void RunShadowTime();

	void SetShadowLoc(int loc) { shadowLoc = loc; };
	int GetShadowLoc() { return shadowLoc; };

	void SetShadowSequence(bool start) { shadowSequence = start; };

	void SetFiring(bool firing) { fire = firing; };
	bool GetFiring() { return fire; };


	//Attack mechanic
	void Attacking();

	void SetAttackSequence(bool attack) { attackSequence = attack; };
	
	bool GetAttacking() { return isAttacking; };


	//Knockback mechanic
	void RunKnockBackTime();

	void SetKnockbackSequence(bool start) { knockbackSequence = start; };

	bool GetCanMove() { return canMove; };	


	//Health and shielding
	void HealthLost(); //reduces player hearts by 1

	int GetHealth() { return hearts; };
	
	void SetShield(bool shielding) { shield = shielding; };
	bool GetShield() { return shield; };

protected:
	//vars for shadows and bullets
	double target = 4;
	float shadowStart = 0.f;
	int shadowLoc = 0;
	bool shadowSequence = false;
	bool fire = false;


	//vars for attacking
	float attackStart = 0.f;
	bool isAttacking = false;
	bool inRange = false;
	int shadow = 0;
	bool attackSequence = false;

	//vars for knockback
	float knockbackStart = 0.f;
	bool knockbackSequence = false;
	bool canMove = true;

	//vars for health and shielding
	int hearts = 3; //player's life points
	bool shield = false; //used by the bullet trigger
};

