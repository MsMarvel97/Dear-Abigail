#pragma once
#include "ECS.h"

class PlayerMechanics
{
public:
	//shield mechanic
	void ActivateShield();

	void SetShieldSequence(bool start) { shieldSequence = start; };

	bool GetShield() { return shieldActive; }; //checks whether the shield is active

	//Attack mechanic
	void Attacking();

	void SetAttackSequence(bool attack) { attackSequence = attack; };
	
	bool GetAttacking() { return isAttacking; };


	//Knockback mechanic
	void RunKnockBackTime();

	void SetKnockbackSequence(bool start) { knockbackSequence = start; }; //starts the knockback sequence

	bool GetCanMove() { return canMove; };	//checks if the player can move


	//Health and shielding
	void HealthLost(); //reduces player health by 1

	void SetHealth(int heal) { hearts = heal; }; //sets health
	int GetHealth() { return hearts; }; //checks player health

	void SetCheckpoint(bool check) { checkpoint = check; };
	bool GetCheckpoint() { return checkpoint; };



	//functions for platform movement
	bool GetMoving() { return moving; };
	void SetMoving(bool newBool) { moving = newBool; };

	bool GetLeft() { return left; };
	void SetLeft(bool newLeft) { left = newLeft; };

	bool GetRight() { return right; };
	void SetRight(bool newRight) { right = newRight; };

	bool GetUp() { return up; };
	void SetUp(bool newUp) { up = newUp; };

	//function to check if player is in the air
	bool GetJumping();


protected:
	//vars for shielding
	float shieldStart = 0.f;
	bool shieldSequence = false;
	bool shieldActive = false;
	bool shieldAvailable = false;

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

	//vars for platform movement
	bool moving = false;
	bool left = false;
	bool right = false;
	bool up = false;

	//var for health
	int hearts = 3; //player's life points
	bool checkpoint = false; //checks if player is in last half of the level
};

