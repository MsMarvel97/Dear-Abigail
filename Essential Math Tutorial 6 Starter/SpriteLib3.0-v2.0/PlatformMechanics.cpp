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
			ECS::GetComponent<AnimationController>(ent).SetActiveAnim(CRUMBLING);
		}

		else if (currentTime >= 2 && currentTime < 3)
		{
			ECS::GetComponent<AnimationController>(ent).SetActiveAnim(CRACKING);
		}

		else if (currentTime >= 3 && currentTime < 5)
		{
			ECS::GetComponent<AnimationController>(ent).SetActiveAnim(GONE);
			operation = 1;
			disable = true;
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
	auto& platform = ECS::GetComponent<PhysicsBody>(entity);
	float currentTime = Timer::StopWatch(verticalStart);

	if (verticalSequence == true)
	{
		if (platform.GetPosition().y <= maxY)
		{
			platform.SetVelocity(vec3(0.f, 20.f, 0.f));
		}
		else
		{
			platform.SetVelocity(vec3(0.f, 0.f, 0.f));
		}
	}

	if (platform.GetPosition().y >= maxY && verticalSequence == false)
	{
		if (resetTimer == 0.f)
		{
			resetTimer = Timer::time;
		}

		float currentTime = Timer::StopWatch(resetTimer);

		if (currentTime >= 5)
		{
			platform.SetPosition(b2Vec2(platform.GetPosition().x, minY));
			resetTimer = 0;
			verticalSequence = false;
		}
	}
}
