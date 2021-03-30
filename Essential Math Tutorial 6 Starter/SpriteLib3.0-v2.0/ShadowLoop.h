#pragma once
#include "ECS.h"
#include "Timer.h"
class ShadowLoop
{
public:
	enum ShadowType
	{
		RANGED = 0,
		MELEE = 1
	};

	enum ShadowFacing
	{
		LEFT = 0,
		RIGHT = 1
	};

	enum ShadowAnimationType
	{
		IDLE = 0,
		MOVING = 2,
		ATTACKING = 4,
		CHARGING = 6
	};

	enum RangedShadowAnimations //FACING + ANIMATION
	{
		FLOATLEFT = 0,
		FLOATRIGHT = 1,
		FLYLEFT = 2,
		FLYRIGHT = 3,
		SHOOTLEFT = 4,
		SHOOTRIGHT = 5
	};

	enum MeleeShadowAnimations //FACING + ANIMATION
	{
		IDLELEFT = 0,
		IDLERIGHT = 1,
		WALKLEFT = 2,
		WALKRIGHT = 3,
		ATTACKLEFT = 4,
		ATTACKRIGHT = 5,
		CHARGELEFT = 6,
		CHARGERIGHT = 7
	};

	ShadowLoop();

	void InitRangedShadow(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller);
	void InitMeleeShadow(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller);

	//handles move and attack sequences depending on current state
	void ShadowRoutine(int entity);

	void RunShadowTime();

	void SetAnimation(int facing, int animation, int entity);

	void SetMovementBoundaries(float min, float max) { minX = min; maxX = max; };

	void SetPatrolVelocity(b2Vec2 vel) { patrolVelocity.x = vel.x; patrolVelocity.y = vel.y; }; //shadow speed - ALWAYS PASS POSITIVE VALUES

	void SetShadowSequence(bool start) { sequenceStart = start; };

	bool GetShadowSequence() { return sequenceStart; };

	int GetShadowType() { return shadowType; };

	int GetShadowAnim() { return animType; };

	void ShadowMove(int entity);

	float startTime = 0.f;
	bool isShadowAlive = true;

private:
	//velocity vectors
	b2Vec2 patrolVelocity = { 0.f, 0.f };

	//boundaries of patrol
	float maxX = 0;
	float minX = 0;

	int facing = 0;
	int animType = 0;
	int shadowType = 0;
	bool sequenceStart = false;
	Sprite* sprites;
	AnimationController* animator;
};

