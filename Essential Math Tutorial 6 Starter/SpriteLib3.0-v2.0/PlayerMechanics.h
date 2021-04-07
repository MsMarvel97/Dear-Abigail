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

	bool GetAttackSequence(); //new one

	void SetAttackSequence(bool attack) { attackSequence = attack; };
	
	bool GetDamageDealt() { return damageDealt; };

	void SetDamageDealt(bool damaged) { damageDealt = damaged; };

	bool GetAttacking() { return isAttacking; };

	bool GetAttackCoolDown() { return attackCoolDown; };



	//Knockback mechanic
	void RunKnockBackTime();

	void SetKnockbackSequence(bool start) { knockbackSequence = start; }; //starts the knockback sequence

	bool GetCanMove() { return canMove; };	//checks if the player can move

	void SetCanMove(bool newMove) { canMove = newMove; }; //new one

	//Health and respawn
	void HealthLost(); //reduces player health by 1

	void SetHealth(int heal) { hearts = heal; }; //sets health
	int GetHealth() { return hearts; }; //checks player health

	void SetRespawn(bool respawn) { dead = respawn; }
	bool GetRespawn() { return dead; };

	//Checkpoint state
	void SetCheckpoint(bool check) { checkpoint = check; };
	bool GetCheckpoint() { return checkpoint; };

	//Level completion state
	void SetComplete(bool finish) { complete = finish; };
	bool GetComplete() { return complete; };

	//Postcard proximity
	void SetExamine(bool examine) { examinePostcard = examine; };
	bool GetExamine() { return examinePostcard; };

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

	//delay between hits
	void RunInvincibility();
	void SetInvincibilitySequence(bool hitDelay) { invincibilitySequence = hitDelay; };
	bool GetInvincibility() { return invincibility; };

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
	bool damageDealt = false;
	int shadow = 0;
	bool attackSequence = false;
	bool attackCoolDown = false;

	//vars for knockback
	float knockbackStart = 0.f;
	bool knockbackSequence = false;
	bool canMove = true;

	//vars for platform movement
	bool moving = false;
	bool left = false;
	bool right = false;
	bool up = false;

	//var for health and respawn
	int hearts = 3; //player's life points
	bool dead = false;


	//vars for scene state/progress
	bool checkpoint = false; //checks if player is in last half of the level
	bool complete = false; //checks if the player has reached the end of a level
	bool examinePostcard = false;

	//hit delay variables
	bool invincibility = false;
	bool invincibilitySequence = false;
	float invincibilityStart = 0.f;

	//Sound variables

	bool soundFinish = true;
	bool soundFinishAttack = true;
	int randomSound, randomSoundTwo;

	//shield sounds
	ToneFire::CoreSound shieldActivate{ "shieldActivate2.wav", false, false, true };
	ToneFire::CoreSound shieldDeactivate{ "shieldDeActivate.wav", false, false, true };
	ToneFire::CoreSound shieldSound{ "objectVanish.wav", false, false, true };

	//abigail hit sounds
	ToneFire::CoreSound abigailHitOne{ "abigailHitOne.wav", false, false, true };
	ToneFire::CoreSound abigailHitTwo{ "abigailHitTwo.wav", false, false, true };
	ToneFire::CoreSound abigailHitThree{ "abigailHitThree.wav", false, false, true };

	//abigail attack sounds
	ToneFire::CoreSound abigailAttackOne{ "abigailAttackOne.wav", false, false, true };
	ToneFire::CoreSound abigailAttackTwo{ "abigailAttackTwo.wav", false, false, true };
	ToneFire::CoreSound abigailAttackThree{ "abigailAttackThree.wav", false, false, true };

};

