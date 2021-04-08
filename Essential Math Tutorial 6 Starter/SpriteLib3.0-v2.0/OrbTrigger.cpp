#include "OrbTrigger.h"
#include "ECS.h"

void OrbTrigger::OnEnter()
{
	Trigger::OnEnter();
	if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetAttacking() == true)
	{
		std::cout << "Orb destroyed\n";
		orbVanish.Play();
		orbVanish.SetVolume(2.5f);
		ECS::GetComponent<BossLevel>(m_targetEntities[0]).OrbDestroyed();
		PhysicsBody::m_bodiesToDelete.push_back(m_triggerEntity);
	}
}

void OrbTrigger::OnExit()
{
	Trigger::OnExit();
}

void SpecialOrbTrigger::OnEnter() //used for the tutorial orb
{
	if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetAttacking() == true)
	{
		//PhysicsBody::m_bodiesToDelete.push_back(m_triggerEntity);
		//PhysicsBody::m_bodiesToDelete.push_back((m_targetEntities[1]));
		//ECS::GetComponent<Sprite>(m_triggerEntity).SetTransparency(0.f);
		//ECS::GetComponent<PhysicsBody>(m_triggerEntity).GetBody()->SetActive(false);
		PhysicsBody::m_bodiesToDelete.push_back(m_triggerEntity);
		PhysicsBody::m_bodiesToDelete.push_back(m_targetEntities[1]);
	}
}
	

void SpecialOrbTrigger::OnExit()
{
	
}