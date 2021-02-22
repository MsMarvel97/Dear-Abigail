#include "BulletTrigger.h"
#include "ECS.h"

void BulletTrigger::OnTrigger()
{
	Trigger::OnTrigger();
}

void BulletTrigger::OnEnter()
{
	Trigger::OnEnter();
	if (ECS::GetComponent<Health>(m_targetEntities[0]).getShield() == true) //checks to see if the player's shield is on
	{
		std::cout << "Shield protected player. No health lost. \n";
	}
	else //runs if player shield isn't on when the bullet hits the player
	{
		std::cout << "Player hit by projectile. Health lost. \n";
		ECS::GetComponent<Health>(m_targetEntities[0]).HealthLost();
		std::cout << "Current Health: " << ECS::GetComponent<Health>(m_targetEntities[0]).GetHealth() << "\n";
	}
	PhysicsBody::m_bodiesToDelete.push_back(m_triggerEntity);
}

void BulletTrigger::OnExit()
{
	Trigger::OnExit();
}
