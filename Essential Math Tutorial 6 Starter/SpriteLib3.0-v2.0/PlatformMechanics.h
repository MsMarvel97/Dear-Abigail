#pragma once
#include "ECS.h"
#include "Timer.h"

class CrumblingSequence
{
public:

	enum CrumbleAnimations
	{
		RESTING = 0,
		CRUMBLING = 1,
		CRACKING = 2,
		GONE = 3
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
		Horizontal,
		Vertical
	};

	//routes the platform to the correct movement function (0 for horizontal, 1 for vertical)
	void MovePlatform(int entity);
	void MovePlatformHorizontal(int entity);
	void MovePlatformVertical(int entity);
	
	//0 for horizontal, 1 for vertical
	void SetType(int platform) { type = platform; };
	void SetVertMovement(bool start) { verticalSequence = start; };
	void ResetTimer() { resetTimer = 0.f; };
	//sets the boundaries of movement for the platform
	void SetMovementBoundaries(float minimum, float maximum) { min = minimum; max = maximum; };

private:
	bool verticalSequence = false;
	float verticalStart = 0.f;
	float resetTimer = 0.f;
	bool reset = false;
	int type = 0;
	float min = 0.f;
	float max = 0.f;
	bool reverse = false;
};
