#pragma once
#include "ECS.h"
class TestBulet
{
public:
	bool getDestroyed();
	void setDestroyed(bool newDestroyed);

	void changeAnchor(float newX, float newY);
	
	float getAnchorX();
	float getAnchorY();

	bool getResetPosition();
	void setResetPosition(bool newBool);

private:
	bool isDestroyed = false;

	float anchorX = 0.f;
	float anchorY = 0.f;
	bool resetPosition = false;
};

