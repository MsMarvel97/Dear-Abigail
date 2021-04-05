#pragma once
#include "ECS.h"
class MovingClass
{
public:
	bool GetMoving();
	void SetMoving(bool newBool);

	bool GetLeft();
	void SetLeft(bool newLeft);

	bool GetRight();
	void SetRight(bool newRight);

	bool GetUp();
	void SetUp(bool newUp);

private:
	bool moving = false;
	bool up = false;
	bool left = false;
	bool right = false;

};