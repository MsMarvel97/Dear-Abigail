#include "MovingTrigger.h"
#include "ECS.h"
void MovingTrigger::OnTrigger()
{
	Trigger::OnTrigger();
}

void MovingTrigger::OnEnter()
{
	Trigger::OnEnter();
<<<<<<< HEAD
    ECS::GetComponent<MovingClass>(m_targetEntities[0]).SetMoving(true);
=======
	ECS::GetComponent<MovingClass>(m_targetEntities[0]).SetMoving(true);
>>>>>>> AngerLevel
}

void MovingTrigger::OnExit()
{
	Trigger::OnExit();
	ECS::GetComponent<MovingClass>(m_targetEntities[0]).SetMoving(false);
	ECS::GetComponent<MovingClass>(m_targetEntities[0]).SetLeft(false);
	ECS::GetComponent<MovingClass>(m_targetEntities[0]).SetRight(false);
}