#include "AttackTrigger.h"
#include "ECS.h"

void AttackTrigger::OnTrigger()
{
	Trigger::OnTrigger();
}

void AttackTrigger::OnEnter()
{
	Trigger::OnEnter();
	ECS::GetComponent<AttackMechanic>(m_targetEntities[0]).SetRange(true);
	ECS::GetComponent<AttackMechanic>(m_targetEntities[0]).SetShadow(Trigger::shadowZone);
}

void AttackTrigger::OnExit()
{
	Trigger::OnExit();
	ECS::GetComponent<AttackMechanic>(m_targetEntities[0]).SetRange(false);
	ECS::GetComponent<AttackMechanic>(m_targetEntities[0]).SetShadow(0);



}
