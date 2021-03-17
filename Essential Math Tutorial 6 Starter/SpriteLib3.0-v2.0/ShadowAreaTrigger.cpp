#include "ShadowAreaTrigger.h"
#include "ECS.h"

void ShadowAreaTrigger::OnEnter()
{
	//each trigger has a specific integer value set in DenialRough.cpp
	Trigger::OnEnter();
	//^^^changes the value of shadowLoc(found in ShadowSense) to equal the integer value of the trigger
	ECS::GetComponent<ShadowLoop>(m_targetEntities[0]).SetShadowSequence(true); //starts the timer in ShadowTime

}

void ShadowAreaTrigger::OnExit()
{
	Trigger::OnExit();
	//ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetShadowSequence(false); //ends the timer in ShadowTime
	ECS::GetComponent<ShadowLoop>(m_targetEntities[0]).SetShadowSequence(false); //starts the timer in ShadowTime
	ECS::GetComponent<ShadowLoop>(m_targetEntities[0]).SetShootingTime(0.5); //resets shooting interval
}
