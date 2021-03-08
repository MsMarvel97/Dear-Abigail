#include "ShadowSense.h"
//attaches to the main player and helps the ActivateShadow function in DenialRough choose which shadow to activate(shoot bullets at the player)
void ShadowSense::setLoc(int newLoc)
{
	shadowLoc = newLoc;
}

int ShadowSense::getLoc()
{
	return shadowLoc;
}
