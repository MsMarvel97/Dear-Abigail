#include "ShadowTriggers.h"
#include "ECS.h"

void ShadowAreaTrigger::OnEnter()
{
	//each trigger has a specific integer value set in DenialRough.cpp
	Trigger::OnEnter();
	ECS::GetComponent<ShadowLoop>(m_targetEntities[0]).SetShadowSequence(true); //starts the timer in ShadowTime

}

void ShadowAreaTrigger::OnExit()
{
	Trigger::OnExit();
	ECS::GetComponent<ShadowLoop>(m_targetEntities[0]).SetShadowSequence(false); //starts the timer in ShadowTime
	ECS::GetComponent<ShadowLoop>(m_targetEntities[0]).SetShootingTime(0.5); //resets shooting interval
}

//
//void BossAreaTrigger::OnEnter()
//{
//	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetShadowLoc(Trigger::GetShadowZone());
//	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetShadowSequence(true); 
//}
//
//void BossAreaTrigger::OnExit()
//{
//	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetShadowLoc(0); 
//	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetShadowSequence(false); 
//}
