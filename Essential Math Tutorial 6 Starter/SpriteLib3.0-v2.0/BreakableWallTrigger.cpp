#include "BreakableWallTrigger.h"
#include "ECS.h"

void BreakableWallTrigger::OnEnter()
{
	Trigger::OnEnter();
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]);
	if (playerMech.GetAttacking() == true)
	{
		playerMech.ReduceWallHealth();
	}
	
}

void BreakableWallTrigger::OnExit()
{
	Trigger::OnExit();
}
