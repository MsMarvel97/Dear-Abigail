#include "OrbTrigger.h"
#include "ECS.h"
void OrbTrigger::OnEnter()
{
	Trigger::OnEnter();
	if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetAttacking() == true)
	{
		std::cout << "Orb destroyed\n";
		ECS::GetComponent<BossLevel>(m_targetEntities[0]).OrbDestroyed();
		PhysicsBody::m_bodiesToDelete.push_back(m_triggerEntity);
	}
}

void OrbTrigger::OnExit()
{
	Trigger::OnExit();
}
