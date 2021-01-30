#include "MoveTrigger.h"
#include "ECS.h"

MoveTrigger::MoveTrigger()
{
}

void MoveTrigger::OnEnter()
{
	Trigger::OnEnter();
	
	//for each targeted entity
	for (int i = 0; i < m_targetEntities.size(); i++)
	{
		//get current position of entity and increases position vector by set movement vector
		ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).SetPosition((ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).GetPosition() + movement), true);
		
	}
}

void MoveTrigger::OnExit()
{
	Trigger::OnExit();

	//for each targeted entity
	for (int i = 0; i < m_targetEntities.size(); i++)
	{
		//get current position of entity and decreases position vector by set movement vector
		ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).SetPosition((ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).GetPosition() - movement), true);
	
	}
}
