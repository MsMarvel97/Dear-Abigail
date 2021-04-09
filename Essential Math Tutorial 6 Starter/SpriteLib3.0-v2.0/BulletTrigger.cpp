#include "BulletTrigger.h"
#include "ECS.h"

void BulletTrigger::OnTrigger()
{
	Trigger::OnTrigger();
}

void BulletTrigger::OnEnter()
{
	Trigger::OnEnter();
	if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetShield() == true) //checks to see if the player's shield is on
	{
		shieldSound.Play();
		shieldSound.SetVolume(3.5f);
	}

	else //runs if player shield isn't on when the bullet hits the player
	{
		ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).HealthLost();
	}

	PhysicsBody::m_bodiesToDelete.push_back(m_triggerEntity);
}

void BulletTrigger::OnExit()
{
	Trigger::OnExit();
}
