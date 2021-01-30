#include "RotationTrigger.h"
#include "ECS.h"

RotationTrigger::RotationTrigger()
{
}

void RotationTrigger::OnEnter()
{
	Trigger::OnEnter();
	//if not triggered
	if (!triggered)
	{
		//for each entity
		for (int i = 0; i < m_targetEntities.size(); i++)
		{
			//rotate based on set rotation value
			ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).TriggeredRotation(rotation, true);
			//set to triggered so it won't repeat
			triggered = true;
		}
	}
}

void RotationTrigger::OnExit()
{
}
