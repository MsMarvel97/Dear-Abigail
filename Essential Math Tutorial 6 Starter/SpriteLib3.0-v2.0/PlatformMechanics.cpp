#include "PlatformMechanics.h"
#include <string>

CrumblingSequence::CrumblingSequence()
{
}

void CrumblingSequence::InitPlatform(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller)
{
	//Store references to the components
	sprites = sprite;
	animator = controller;

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
	//Resting state
	animator->AddAnimation(animations["Solid"].get<Animation>());
	//Crumbling
	animator->AddAnimation(animations["Crumbling"].get<Animation>());
	//Intense crumbling
	animator->AddAnimation(animations["Cracking"].get<Animation>());
	//Disappearing
	animator->AddAnimation(animations["Gone"].get<Animation>());

	////Set Default Animation
	animator->SetActiveAnim(RESTING);
}

void CrumblingSequence::Crumble(int ent)
{
	if (sequenceStart == false)
	{
		startTime = Timer::time;
	}

	float currentTime = Timer::StopWatch(startTime);

	if (sequenceStart == true)
	{
		if (currentTime < 1)
		{
			ECS::GetComponent<AnimationController>(ent).SetActiveAnim(RESTING);
		}
		else if (currentTime >= 1 && currentTime < 2)
		{
			if (soundFinish == true)
			{
				crumbleOne.Play();
				crumbleOne.SetVolume(2.5f);
			}
			ECS::GetComponent<AnimationController>(ent).SetActiveAnim(CRUMBLING);
			soundFinish = false;
		}

		else if (currentTime >= 2 && currentTime < 3)
		{
			if (soundFinish == false)
			{
				crumbleTwo.Play();
				crumbleTwo.SetVolume(2.5f);
			}
			ECS::GetComponent<AnimationController>(ent).SetActiveAnim(CRACKING);
			soundFinish = true;
		}

		else if (currentTime >= 3 && currentTime < 5)
		{
			if (soundFinish == true)
			{
				crumbleThree.Play();
				crumbleThree.SetVolume(2.5f);
			}
			ECS::GetComponent<AnimationController>(ent).SetActiveAnim(GONE);
			operation = 1;
			disable = true;
			soundFinish = false;
		}
		else if (currentTime >= 5)
		{
			ECS::GetComponent<AnimationController>(ent).SetActiveAnim(RESTING);
			operation = 0;
			disable = true;
			startTime = 0;
			sequenceStart = false;
		}
	}
}

void CrumblingSequence::setSequenceStart(bool start)
{
	sequenceStart = start;
}

bool CrumblingSequence::getSequenceStart()
{
	return sequenceStart;
}

int CrumblingSequence::disablePlatform()
{
	if (disable == true)
	{
		return operation;
	}
	else
	{
		return -1;
	}
}

void MovingPlatform::MovePlatform(int entity)
{
	if (ECS::GetComponent<MovingPlatform>(entity).type == 0)
	{
		MovePlatformHorizontal(entity);
	}
	else
	{
		MovePlatformVertical(entity);
	}
}

void MovingPlatform::MovePlatformHorizontal(int entity)
{
	auto& moveTrig = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	auto& plat = ECS::GetComponent<PhysicsBody>(entity);

	if (plat.GetPosition().x > max)
	{
		reverse = true;
	}

	if (plat.GetPosition().x < min)
	{
		reverse = false;
	}

	if (reverse == false)
	{
		plat.SetVelocity(vec3(30.f, 0.f, 0.f));
		moveTrig.SetRight(true);
		moveTrig.SetLeft(false);
	}

	else if (reverse == true)
	{
		plat.SetVelocity(vec3(-30.f, 0.f, 0.f));
		moveTrig.SetLeft(true);
		moveTrig.SetRight(false);
	}
}

void MovingPlatform::MovePlatformVertical(int entity)
{
	auto& platform = ECS::GetComponent<PhysicsBody>(entity);
	float currentTime = Timer::StopWatch(verticalStart);

	if (platform.GetPosition().y >= max)
	{
		platform.SetVelocity(vec3(0.f, 0.f, 0.f));
		verticalSequence = false;
	}

	if (verticalSequence == true)
	{
		if (platform.GetPosition().y <= max)
		{
			platform.SetVelocity(vec3(0.f, 20.f, 0.f));
		}
	}

	if (platform.GetPosition().y >= max && verticalSequence == false)
	{
		if (resetTimer == 0.f)
		{
			resetTimer = Timer::time;
		}

		float currentTime = Timer::StopWatch(resetTimer);

		if (currentTime >= 5)
		{
			platform.SetPosition(b2Vec2(platform.GetPosition().x, min));
			resetTimer = 0;
			verticalSequence = false;
		}
	}
}
