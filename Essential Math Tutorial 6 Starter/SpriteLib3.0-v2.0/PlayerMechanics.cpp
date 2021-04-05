#include "PlayerMechanics.h"
void PlayerMechanics::RunShadowTime()
{
		if (shadowSequence == false)
		{
			target = 2;
			shadowStart = Timer::time;
		}
		float currentTime = Timer::StopWatch(shadowStart);

		if (shadowSequence == true) //this statement will run once the player has entered a ShadowAreaTrigger
		{

			if (currentTime > target)
			{
				fire = true;
				target += 2;
			}
			else
			{
				fire = false;
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
		}
		else if (currentTime >= 1)
		{
			isAttacking = false;
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
}

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
		}
		else if (currentTime >= 3 && currentTime < 5)
		{
			shieldActive = false; //turn shield off, this is the cool down period, player can't use the shield during the cool down period
			//std::cout << "Shield Off\n";
		}
		else if (currentTime >= 5)
		{
			shieldAvailable = true; //shield can be activated again.
			shieldSequence = false;
			std::cout << "Shield cool down finished.\n";
		}
	}
}


void PlayerMechanics::CheckWallStatus(int wallEntity, int trigEntity)
{
	if (wallHealth > 0) { ECS::GetComponent<Sprite>(wallEntity).LoadSprite(wallSprites[wallHealth - 1], 10, 30); }
	else
	{
		ECS::GetComponent<PhysicsBody>(wallEntity).GetBody()->SetActive(false);
		ECS::GetComponent<PhysicsBody>(trigEntity).GetBody()->SetActive(false);
		ECS::GetComponent<Sprite>(wallEntity).SetTransparency(0.f);
	}
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

