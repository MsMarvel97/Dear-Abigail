#include "TestBulet.h"

bool TestBulet::getDestroyed()
{
    return isDestroyed;
}

void TestBulet::setDestroyed(bool newDestroyed)
{
    isDestroyed = newDestroyed;
}

/////////////////////////
void TestBulet::changeAnchor(float newX, float newY)
{
    anchorX = newX;
    anchorY = newY;
}

float TestBulet::getAnchorX()
{
    return anchorX;
}

float TestBulet::getAnchorY()
{
    return anchorY;
}

bool TestBulet::getResetPosition()
{
    return resetPosition;
}

void TestBulet::setResetPosition(bool newBool)
{
    resetPosition = newBool;
}
