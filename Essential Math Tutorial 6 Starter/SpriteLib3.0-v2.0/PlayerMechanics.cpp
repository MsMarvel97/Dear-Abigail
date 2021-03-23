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

	if (attackSequence == true) //this statement will run once the player has entered a ShadowAreaTrigger
	{

		if (currentTime > 3)
		{
			isAttacking = false;
			std::cout << "Attack end\n";
			attackSequence = false;
		}
		else
		{
			isAttacking = true;
		}
	}
}

void PlayerMechanics::RunKnockBackTime()
{
	if (knockbackSequence == false)
	{
		knockbackStart = Timer::time;
	}
	float currentTime = Timer::StopWatch(knockbackStart);

	if (knockbackSequence == true) //this statement will run once the player has entered a ShadowAreaTrigger
	{

		if (currentTime < 2)
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
