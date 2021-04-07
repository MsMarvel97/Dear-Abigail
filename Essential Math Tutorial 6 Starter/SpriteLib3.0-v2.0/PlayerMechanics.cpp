#include "PlayerMechanics.h"
#include <stdlib.h>

void PlayerMechanics::ActivateShield()
{
	if (shieldSequence == false)
	{
		shieldStart = Timer::time;
	}

	float currentTime = Timer::StopWatch(shieldStart);

	if (shieldSequence == true)
	{
		if (currentTime < 2)
		{
			shieldActive = true; //turn on shield
			shieldAvailable = false; //player can't spam shield
			if (soundFinish == true)
			{
				shieldActivate.Play();
				shieldActivate.SetVolume(5.0f);
				std::cout << "shield activated\n";
			}
			soundFinish = false;
		}
		else if (currentTime >= 3 && currentTime < 5)
		{
			shieldActive = false; //turn shield off, this is the cool down period, player can't use the shield during the cool down period
			//std::cout << "Shield Off\n";
			if (soundFinish == false)
			{
				shieldDeactivate.Play();
				shieldDeactivate.SetVolume(5.0f);
			}
			soundFinish = true;
		}
		else if (currentTime >= 5)
		{
			shieldAvailable = true; //shield can be activated again.
			shieldSequence = false;
			std::cout << "Shield cool down finished.\n";
		}
	}
}

void PlayerMechanics::Attacking()
{
	if (attackSequence == false)
	{
		attackStart = Timer::time;
	}
	float currentTime = Timer::StopWatch(attackStart);

	if (attackSequence == true) 
	{
		if (currentTime < 1)
		{
			isAttacking = true;
			attackCoolDown = true;

			srand(time(NULL));

			randomSoundTwo = rand() % 3 + 1;
			std::cout << randomSoundTwo;
			if (soundFinishAttack == true)
			{ 
			if (randomSound == 1)
			{
				abigailAttackOne.Play();
				abigailAttackOne.SetVolume(6.0f);
			}
			else if (randomSound == 2)
			{
				abigailAttackTwo.Play();
				abigailAttackTwo.SetVolume(6.0f);
			}
			else if (randomSound == 3)
			{
				abigailAttackThree.Play();
				abigailAttackThree.SetVolume(6.0f);
			}
			}
		}
		else if (currentTime >= 1)
		{
			isAttacking = false;
			soundFinishAttack = false;
		}

		if (currentTime >= 1.5)
		{
			attackCoolDown = false;
			attackSequence = false;
		}
	}
}


bool PlayerMechanics::GetAttackSequence()
{
	return attackSequence;
}


void PlayerMechanics::RunKnockBackTime()
{
	if (knockbackSequence == false)
	{
		knockbackStart = Timer::time;
	}

	float currentTime = Timer::StopWatch(knockbackStart);

	if (knockbackSequence == true) 
	{

		if (currentTime < 0.5)
		{
			canMove = false;
		}
		else
		{
			canMove = true;
			knockbackSequence = false;
		}
	}
}

void PlayerMechanics::HealthLost()
{
		hearts--;
		srand(time(NULL));

		randomSound = rand() % 3 + 1;
		std::cout << randomSound;
		if (randomSound == 1)
		{
			abigailHitOne.Play();
			abigailHitOne.SetVolume(6.0f);
		}
		else if (randomSound == 2)
		{
			abigailHitTwo.Play();
			abigailHitTwo.SetVolume(6.0f);
		}
		else if (randomSound == 3)
		{
			abigailHitThree.Play();
			abigailHitThree.SetVolume(6.0f);
		}

		if (hearts <= 0)
		{
			dead = true;
		}
}

bool PlayerMechanics::GetJumping()
{
	bool jumping = false;
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());

	if (player.GetVelocity().y > 0.0001 || player.GetVelocity().y < -0.0001)
	{
		jumping = true;
	}

	return jumping;
}

void PlayerMechanics::RunInvincibility()
{
	if (invincibilitySequence == false)
	{
		invincibilityStart = Timer::time;
	}

	float currentTime = Timer::StopWatch(invincibilityStart);

	if (invincibilitySequence == true)
	{

		if (currentTime < 2)
		{
			invincibility = true; //turns on player invincibility for t second(s)
			std::cout << "I am titaninum!!!\n";
		}
		else
		{
			invincibility = false; //disables player invincibility
			invincibilitySequence = false;
			std::cout << "Invincibility off\n";
		}
	}
}
