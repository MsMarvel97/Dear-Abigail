#include "PlatformTrigger.h"

void VerticalPlatformTrigger::OnEnter()
{
	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetMoving(true);
	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetUp(true);
	ECS::GetComponent<MovingPlatform>(m_targetEntities[0]).SetVertMovement(true);
	ECS::GetComponent<MovingPlatform>(m_targetEntities[0]).ResetTimer();
}

void VerticalPlatformTrigger::OnExit()
{
	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetMoving(false);
	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetUp(false);
	ECS::GetComponent<MovingPlatform>(m_targetEntities[0]).SetVertMovement(false);
}
