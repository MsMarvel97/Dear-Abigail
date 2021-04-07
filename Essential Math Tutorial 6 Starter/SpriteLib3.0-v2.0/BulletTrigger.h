#pragma once
#include "Trigger.h"
class BulletTrigger : public Trigger
{
	//Used for the bullets shot by enemies. If the bullet hits the player while the shield is off, the player loses a heart. 
	//If the bullet hits the player while the shield is active, no hearts are lost
public:
	void OnTrigger() override;

	void OnEnter() override;
	void OnExit() override;
protected:
	/*ToneFire::CoreSound abigailHit{ "abigailHitOne.wav", false, false, true };*/
	bool triggered = false;

	//Sound Library and variables
	ToneFire::CoreSound shieldSound{ "objectVanish.wav", false, false, true };

};

