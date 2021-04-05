#include "PlayerMechanics.h"

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
