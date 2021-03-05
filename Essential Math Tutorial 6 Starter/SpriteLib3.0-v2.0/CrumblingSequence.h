#pragma once
#include "ECS.h"
#include "Timer.h"

class CrumblingSequence
{
public:

	enum CrumbleAnimations
	{
		RESTING,
		CRUMBLING,
		GONE
	};

	CrumblingSequence();
	CrumblingSequence(std::string& fileName, std::string& animationJSON, int width, int height,
		Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys = false, PhysicsBody* body = nullptr);

	void InitPlatform(std::string& fileName, std::string& animationJSON, int width, int height,
		Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys = false, PhysicsBody* body = nullptr);

	void Crumble();
	bool sequenceStart = false;
	int entity = 0;

	void setEntity(int newEntity);
	void setSequenceStart(bool start);
	bool getSequenceStart();

	int disablePlatform();
	bool disable = false;
	int operation = 0;

	float startTime = 0.f;

private:
	//A reference to our sprite
	Sprite* sprites = nullptr;
	//A reference to our animation controller
	AnimationController* animator = nullptr;
	//A reference to our player transform
	Transform* transformer = nullptr;

	//Physics importance
	//A reference to our physics body
	PhysicsBody* physicsBody = nullptr;
	//Does this player have physics?
	bool physics = false;
};

