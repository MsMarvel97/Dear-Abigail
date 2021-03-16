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

