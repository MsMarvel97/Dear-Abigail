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
		CRACKING,
		GONE
	};

	CrumblingSequence();

	void InitPlatform(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller);

	void Crumble(int ent);
	bool sequenceStart = false;

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

class MovingPlatform
{
public:
	enum PlatformType
	{
		Vertical,
		Horizontal
	};

	void MovePlatform(int entity);
	
	void SetVertMovement(bool start) { verticalSequence = start; };
	void ResetTimer() { resetTimer = 0.f; };
	void SetMovementBoundaries(float min, float max) { minY = min; maxY = max; };

private:
	bool verticalSequence = false;
	float verticalStart = 0.f;
	float resetTimer = 0.f;
	bool reset = false;
	float minY = 0.f;
	float maxY = 0.f;
};
