#include "CrumblingSequence.h"
#include <string>

CrumblingSequence::CrumblingSequence()
{
}

CrumblingSequence::CrumblingSequence(std::string& fileName, std::string& animationJSON, int width, int height, int entityNum, Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	InitPlatform(fileName, animationJSON, width, height, entityNum, sprite, controller, transform, hasPhys, body);
}

void CrumblingSequence::InitPlatform(std::string& fileName, std::string& animationJSON, int width, int height, int entityNum, Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	//Store references to the components
	sprites = sprite;
	animator = controller;
	transformer = transform;
	physics = hasPhys;
	entity = entityNum;

	if (hasPhys)
	{
		physicsBody = body;
	}

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
	animator->AddAnimation(animations["Crumble"].get<Animation>());
	//Disappearing
	animator->AddAnimation(animations["Gone"].get<Animation>());

	////Set Default Animation
	animator->SetActiveAnim(RESTING);
}

void CrumblingSequence::Crumble()
{
	if (sequenceStart == false)
	{
		startTime = Timer::time;
	}

	float currentTime = Timer::StopWatch(startTime);

	if (sequenceStart == true)
	{
		if (currentTime < 2)
		{
			ECS::GetComponent<AnimationController>(entity).SetActiveAnim(RESTING);
		}
		else if (currentTime >= 2 && currentTime <= 4)
		{
			//ECS::GetComponent<AnimationController>(entity).GetAnimations()[CRUMBLING].Reset();
			ECS::GetComponent<AnimationController>(entity).SetActiveAnim(CRUMBLING);
			operation = 1;
			disable = true;
		}
		else if (currentTime > 4 && currentTime < 6)
		{
			ECS::GetComponent<AnimationController>(entity).SetActiveAnim(GONE);
		}
		else if (currentTime >= 6)
		{
			ECS::GetComponent<AnimationController>(entity).SetActiveAnim(RESTING);
			operation = 0;
			disable = true;
			startTime = 0;
			sequenceStart = false;
		}
	}
}

void CrumblingSequence::setEntity(int newEntity)
{
	entity = newEntity;
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

