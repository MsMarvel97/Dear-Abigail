#include "ShadowLoop.h"

ShadowLoop::ShadowLoop()
{
}

void ShadowLoop::InitRangedShadow(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller, bool bossShadow)
{
	//Store references to the components
	sprites = sprite;
	animator = controller;
	shadowType = RANGED;
	boss = bossShadow;

	//Initialize UVs
	animator->InitUVs(fileName);

	//Loads the texture and sets width and height
	sprites->LoadSprite(fileName, width, height, true, animator);
	animator->SetVAO(sprites->GetVAO());
	animator->SetTextureSize(sprites->GetTextureSize());

	//Loads in the animations json file
	nlohmann::json animations = File::LoadJSON(animationJSON);

	//PLATFORM ANIMATIONS\\
	//
	//Idling left
	animator->AddAnimation(animations["FloatLeft"].get<Animation>());
	//Idling right
	animator->AddAnimation(animations["FloatRight"].get<Animation>());
	//Flying left
	animator->AddAnimation(animations["FlyLeft"].get<Animation>());
	//Flying right
	animator->AddAnimation(animations["FlyRight"].get<Animation>());
	//Shooting left
	animator->AddAnimation(animations["ShootLeft"].get<Animation>());
	//Shooting right
	animator->AddAnimation(animations["ShootRight"].get<Animation>());

	////Set Default Animation
	animator->SetActiveAnim(FLOATLEFT);
}

void ShadowLoop::InitMeleeShadow(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller)
{
	//Store references to the components
	sprites = sprite;
	animator = controller;
	shadowType = MELEE;

	//Initialize UVs
	animator->InitUVs(fileName);

	//Loads the texture and sets width and height
	sprites->LoadSprite(fileName, width, height, true, animator);
	animator->SetVAO(sprites->GetVAO());
	animator->SetTextureSize(sprites->GetTextureSize());

	//Loads in the animations json file
	nlohmann::json animations = File::LoadJSON(animationJSON);

	//PLATFORM ANIMATIONS\\
	//
	//Idling left
	animator->AddAnimation(animations["IdleLeft"].get<Animation>());
	//Idling right
	animator->AddAnimation(animations["IdleRight"].get<Animation>());
	//Charging left
	animator->AddAnimation(animations["IdleLeft"].get<Animation>()); //TBC to charging
	//Charging right
	animator->AddAnimation(animations["IdleRight"].get<Animation>()); //TBC to charging
	//Attacking left
	animator->AddAnimation(animations["AttackLeft"].get<Animation>());
	//Attacking right
	animator->AddAnimation(animations["AttackRight"].get<Animation>());
	//Attacking left
	animator->AddAnimation(animations["AttackLeft"].get<Animation>());
	//Attacking right
	animator->AddAnimation(animations["AttackRight"].get<Animation>());

	////Set Default Animation
	animator->SetActiveAnim(IDLELEFT);

}

void ShadowLoop::ShadowRoutine(int entity)
{
	if (shadowType == RANGED)
	{
		RangedRoutine(entity);
	}
	else
	{
		MeleeRoutine(entity);
	}

	//animation will be set based on the shadow's current state
	SetAnimation(facing, animType, entity);
}

void ShadowLoop::FiringLoop()
{
}

void ShadowLoop::SetAnimation(int facing, int animation, int entity)
{
	int choice = facing + animation;
	ECS::GetComponent<AnimationController>(entity).SetActiveAnim(choice);
}

void ShadowLoop::ShadowPause(int entity)
{
	auto& shadow = ECS::GetComponent<PhysicsBody>(entity);

	if (pauseSequenceStart == false)
	{
		pauseStartTime = Timer::time;
	}
	float currentTime = Timer::StopWatch(pauseStartTime);

	if (pauseSequenceStart == true)
	{

		if (currentTime >= 0 && currentTime <= 4)
		{
			shadow.SetVelocity(vec3(0.f, 0.f, 0.f));
			shadowCanMove = false;
		}
		else
		{
			shadowCanMove = true;
			pauseSequenceStart = false;
		}

	}
}

void ShadowLoop::ShadowMove(int entity)
{
	auto& shadow = ECS::GetComponent<PhysicsBody>(entity);

	if (facing == LEFT)
	{
		shadow.SetVelocity(vec3(-30, 0.f, 0.f));
		if (shadow.GetPosition().x <= minX)
		{
			facing = RIGHT;
		}
	}
	else
	{
		shadow.SetVelocity(vec3(30, 0.f, 0.f));
		if (shadow.GetPosition().x >= maxX)
		{
			facing = LEFT;
		}
	}
}

void ShadowLoop::ShadowFacing(int entity)
{
	if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x > ECS::GetComponent<PhysicsBody>(entity).GetPosition().x)
	{
		facing = RIGHT;
	}
	else
	{
		facing = LEFT;
	}
}

void ShadowLoop::RangedRoutine(int entity)
{
	auto& shadow = ECS::GetComponent<PhysicsBody>(entity);

	if (sequenceStart == false)
	{
		pauseStartTime = Timer::time;
	}

	float currentTime = Timer::StopWatch(pauseStartTime);

	if (sequenceStart == true)
	{
		ShadowFacing(entity);

		if (ECS::GetComponent<ShadowLoop>(entity).GetShadowType() == RANGED)
		{
			if (currentTime >= shootingTime)
			{
				fire = true;
				shootingTime += 1.5;
			}
			else
			{
				fire = false;
			}
		}

		if (currentTime >= 0 && currentTime < 3) //resting
		{
			animType = IDLE;
		}
		else if (currentTime > 3 && currentTime < 5) //charging 
		{
			animType = IDLE;
		}

		if (currentTime >= 0 && currentTime < 3) //resting
		{
			animType = IDLE;
		}
		else if (currentTime > 3 && currentTime < 5) //charging 
		{
			animType = IDLE;
		}
		else if (currentTime > 5 && currentTime < 7) //attacking
		{
			animType = IDLE;
		}
		else
		{
			currentTime = 0.f;
			startTime = Timer::time;
		}
	}

	//This will allow the shadow to move while it is not attacking the player
	else if (sequenceStart == false && !boss)
	{
		ShadowMove(entity);
	}
}

void ShadowLoop::MeleeRoutine(int entity)
{
	auto& shadow = ECS::GetComponent<PhysicsBody>(entity);
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	if (sequenceStart == false)
	{
		startTime = Timer::time;
	}
	float currentTime = Timer::StopWatch(startTime);

	if (sequenceStart == true) //this statement will run once the player has entered a ShadowAreaTrigger
	{
		if (player.GetPosition().x >= minX && player.GetPosition().x <= maxX)
		{
			ShadowFacing(entity);
		}

		if (currentTime >= 0 && currentTime < 3) //resting
		{
			animType = IDLE;
		}

		else if (currentTime > 3 && currentTime < 5) //charging 
		{
			animType = CHARGING;
		}
		else if (currentTime > 5 && currentTime < 7) //attacking
		{
			animType = ATTACKING;
		}
		else
		{
			currentTime = 0.f;
			startTime = Timer::time;
		}
	}

	ShadowMove(entity);

	//animation will be set based on the shadow's current state
	SetAnimation(facing, animType, entity);
}
