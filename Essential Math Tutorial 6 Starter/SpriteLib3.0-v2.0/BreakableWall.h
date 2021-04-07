#pragma once
#include "ECS.h"
#include "Timer.h"
class BreakableWall
{
public:
	enum WallAnimation
	{
		PUNCHZERO,
		PUNCHONE,
		PUNCHTWO,
		PUNCHTHREE
	};
	void InitBreakableWall(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller);
	void WallRoutine(int entity);
	void SetAnimation(int animation, int entity);
	void SetHit(int attack) { hit = attack; };


private:
	bool hit = false;
	bool wallDestroyed = false;
	int health = 3;
	int animType = 0;
	Sprite* sprites;
	AnimationController* animator;
};

