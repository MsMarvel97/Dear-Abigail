#include "MovingTrigger.h"
#include "ECS.h"
void MovingTrigger::OnTrigger()
{
	Trigger::OnTrigger();
}

void MovingTrigger::OnEnter()
{
	Trigger::OnEnter();
    ECS::GetComponent<MovingClass>(m_targetEntities[0]).SetMoving(true);
}

void MovingTrigger::OnExit()
{
	Trigger::OnExit();
	ECS::GetComponent<MovingClass>(m_targetEntities[0]).SetMoving(false);
}