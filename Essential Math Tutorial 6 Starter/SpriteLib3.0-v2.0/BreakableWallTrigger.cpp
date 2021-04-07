#include "BreakableWallTrigger.h"
#include "ECS.h"

void BreakableWallTrigger::OnEnter()
{
	Trigger::OnEnter();
	ECS::GetComponent<BreakableWall>(m_targetEntities[1]).SetHit(true);
}

void BreakableWallTrigger::OnExit()
{
	Trigger::OnExit();
	ECS::GetComponent<BreakableWall>(m_targetEntities[1]).SetHit(false);
}
