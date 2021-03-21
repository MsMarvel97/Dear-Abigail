#include "MovingTrigger.h"
#include "ECS.h"
void MovingTrigger::OnTrigger()
{
	Trigger::OnTrigger();
}

void MovingTrigger::OnEnter()
{
	Trigger::OnEnter();
    ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetMoving(true);
}	

void MovingTrigger::OnExit()
{
	Trigger::OnExit();
	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetMoving(false);
	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetLeft(false);
	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetRight(false);
}