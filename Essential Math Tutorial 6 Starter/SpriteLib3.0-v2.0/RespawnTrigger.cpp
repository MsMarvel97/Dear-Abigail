#include "RespawnTrigger.h"
#include "ECS.h"

void RespawnTrigger::OnEnter()
{//resets the player's position to the beginning of the level if they fall out of the map.
	Trigger::OnEnter();
	ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetRespawn(true);
}
void RespawnTrigger::OnExit()
{
	Trigger::OnExit();
}
