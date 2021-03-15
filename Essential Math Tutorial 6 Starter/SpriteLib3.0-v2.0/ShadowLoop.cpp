#include "ShadowLoop.h"

<<<<<<< HEAD
ShadowLoop::ShadowLoop()
{
}

void ShadowLoop::InitRangedShadow(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller)
{
	//Store references to the components
	sprites = sprite;
	animator = controller;
	shadowType = RANGED;

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

void ShadowLoop::ShadowRoutine(int entity)
{
	auto& shadow = ECS::GetComponent<PhysicsBody>(entity);
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());

=======
void ShadowLoop::ShadowRoutine()
{
>>>>>>> AngerLevel
	if (sequenceStart == false)
	{
		startTime = Timer::time;
	}
	float currentTime = Timer::StopWatch(startTime);

	if (sequenceStart == true) //this statement will run once the player has entered a ShadowAreaTrigger
	{
<<<<<<< HEAD
		shadow.SetVelocity(vec3(0.f, 0.f, 0.f));

		if (player.GetPosition().x > shadow.GetPosition().x)
		{
			facing = RIGHT;
		}
		else
		{
			facing = LEFT;
		}
=======
>>>>>>> AngerLevel

		if (currentTime >= 0 && currentTime < 3) //resting
		{
			//std::cout << "Resting" << "\n";
<<<<<<< HEAD
			animType = IDLE;

=======
			s_resting = true;
			s_charging = false;
			s_attacking = false;
	
>>>>>>> AngerLevel
		}
		else if (currentTime > 3 && currentTime < 5) //charging 
		{
			//std::cout << "Charging" << "\n";
<<<<<<< HEAD
			if (ECS::GetComponent<ShadowLoop>(entity).GetShadowType() == RANGED)
			{
				animType = IDLE;
			}
			else
			{
				animType = CHARGING;
			}
=======
			s_resting = false;
			s_charging = true;
			s_attacking = false;
>>>>>>> AngerLevel
		}
		else if (currentTime > 5 && currentTime < 7) //attacking
		{
			//std::cout << "Attacking" << "\n";
<<<<<<< HEAD
			animType = ATTACKING;
=======
			s_resting = false;
			s_charging = false;
			s_attacking = true;
>>>>>>> AngerLevel
		}
		else
		{
			currentTime = 0.f;
			startTime = Timer::time;
		}
	}
<<<<<<< HEAD

	//This will allow the shadow to move while it is not attacking the player
	else if (sequenceStart == false)
	{
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

	//animation will be set based on the shadow's current state
	SetAnimation(facing, animType, entity);
}
void ShadowLoop::setSequenceStart(bool start)
{
    sequenceStart = start;
}

bool ShadowLoop::getSequenceStart()
{
	int choice = facing + animation;
	ECS::GetComponent<AnimationController>(entity).SetActiveAnim(choice);
=======
}
void ShadowLoop::setSequenceStart(bool start)
{
    sequenceStart = start;
}

bool ShadowLoop::getSequenceStart()
{
    return sequenceStart;
>>>>>>> AngerLevel
}