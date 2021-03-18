#include "PlatformTrigger.h"

void VerticalPlatformTrigger::OnEnter()
{
	ECS::GetComponent<MovingPlatform>(m_targetEntities[0]).SetVertMovement(true);
	ECS::GetComponent<MovingPlatform>(m_targetEntities[0]).ResetTimer();
}

void VerticalPlatformTrigger::OnExit()
{
	ECS::GetComponent<MovingPlatform>(m_targetEntities[0]).SetVertMovement(false);
}
