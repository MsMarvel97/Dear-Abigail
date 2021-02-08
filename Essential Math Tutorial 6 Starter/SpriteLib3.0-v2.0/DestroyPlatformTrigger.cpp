#include "DestroyPlatformTrigger.h"
#include "ECS.h"

void DestroyPlatformTrigger::OnEnter()
{
	Trigger::OnEnter();
	if (ECS::GetComponent<CrumblingSequence>(m_targetEntities[0]).getSequenceStart() == false)
	{
		ECS::GetComponent<CrumblingSequence>(m_targetEntities[0]).setEntity(m_targetEntities[0]);
		ECS::GetComponent<CrumblingSequence>(m_targetEntities[0]).setSequenceStart(true);
	}
}

void DestroyPlatformTrigger::OnExit()
{
	Trigger::OnExit();
}