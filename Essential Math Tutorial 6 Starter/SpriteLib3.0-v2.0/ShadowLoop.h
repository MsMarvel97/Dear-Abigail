#pragma once
#include "ECS.h"
#include "Timer.h"
class ShadowLoop
{
public:
	enum ShadowType
	{
		RANGED,
		MELEE,
	};

	enum ShadowFacing
	{
		LEFT,
		RIGHT
	};

	enum ShadowAnimationType
	{
		IDLE = 0,
		MOVING = 2,
		ATTACKING = 4,
		CHARGING = 6
	};

	enum RangedShadowAnimations
	{
		FLOATLEFT,
		FLOATRIGHT,
		FLYLEFT,
		FLYRIGHT,
		SHOOTLEFT,
		SHOOTRIGHT
	};

	enum MeleeShadowAnimations
	{
		IDLELEFT,
		IDLERIGHT,
		WALKLEFT,
		WALKRIGHT,
		ATTACKLEFT,
		ATTACKRIGHT,
		CHARGELEFT,
		CHARGERIGHT
	};

	ShadowLoop();

	void InitRangedShadow(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller);
	void InitMeleeShadow(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller);

	//handles move and attack sequences depending on current state
	void ShadowRoutine(int entity);

	void SetAnimation(int facing, int animation, int entity);

	void SetMovementBoundaries(float max, float min) { maxX = max; minX = min; };
	void SetShadowSequence(bool start) { sequenceStart = start; };
	
	bool GetShadowSequence() { return sequenceStart; };

	int GetShadowType() { return shadowType; };
	
	int GetShadowAnim() { return animType; };

	float startTime = 0.f;

private:
	float maxX = 0;
	float minX = 0;
	int facing = 0;
	int animType = 0;
	int shadowType = 0;
	bool sequenceStart = false;
	Sprite* sprites;
	AnimationController* animator;
};

