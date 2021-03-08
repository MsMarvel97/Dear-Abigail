#include "ShadowAreaTrigger.h"
#include "ECS.h"

void ShadowAreaTrigger::OnEnter()
{
	//each trigger has a specific integer value set in DenialRough.cpp
	Trigger::OnEnter();
	ECS::GetComponent<ShadowSense>(m_targetEntities[0]).setLoc(Trigger::GetShadowZone()); 
	//^^^changes the value of shadowLoc(found in ShadowSense) to equal the integer value of the trigger
	ECS::GetComponent<ShadowTime>(m_targetEntities[0]).setSequenceStart(true); //starts the timer in ShadowTime
}

void ShadowAreaTrigger::OnExit()
{
	Trigger::OnExit();
	ECS::GetComponent<ShadowSense>(m_targetEntities[0]).setLoc(0); //sets the shadowLoc back to 0. 0 indicates that the player is not within range of a shadow.
	ECS::GetComponent<ShadowTime>(m_targetEntities[0]).setSequenceStart(false); //ends the timer in ShadowTime
}
