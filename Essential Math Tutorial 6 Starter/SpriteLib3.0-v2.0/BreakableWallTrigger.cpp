#include "BreakableWallTrigger.h"
#include "ECS.h"

void BreakableWallTrigger::OnEnter()
{
	Trigger::OnEnter();
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]);
	auto& wall = ECS::GetComponent<BreakableWall>(m_targetEntities[1]);
	if (playerMech.GetAttacking() == true)
	{
		wall.SubtractHealth();
	}
	
}

void BreakableWallTrigger::OnExit()
{
	Trigger::OnExit();
}
