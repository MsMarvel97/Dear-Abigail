#include "KnockBackTrigger.h"


void KnockBackTrigger::OnTrigger()
{
	Trigger::OnTrigger();

}
void KnockBackTrigger::OnEnter()
{
	Trigger::OnEnter();
	double tempPlayerX = 0;
	double tempPlayerY = 0;

	double tempTriggerX = 0;
	double tempTriggerY = 0;

	double vectorX = 0;
	double vectorY = 0;

	tempPlayerX = ECS::GetComponent<PhysicsBody>(m_targetEntities[0]).GetBody()->GetPosition().x;
	tempPlayerY = ECS::GetComponent<PhysicsBody>(m_targetEntities[0]).GetBody()->GetPosition().y;

	tempTriggerX = ECS::GetComponent<PhysicsBody>(m_triggerEntity).GetBody()->GetPosition().x;
	tempTriggerY = ECS::GetComponent<PhysicsBody>(m_triggerEntity).GetBody()->GetPosition().y;

	vectorX = tempPlayerX - tempTriggerX;
	vectorY = tempPlayerY - tempTriggerY;

	double vectorMagnitude = sqrt((vectorX * vectorX) + (vectorY * vectorY));
	double normalX = vectorX / vectorMagnitude;
	double normalY = vectorY / vectorMagnitude;

	if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetAttacking() == true)
	{
		if (ECS::GetComponent<ShadowLoop>(m_triggerEntity).GetShadowAnim() == 0 || ECS::GetComponent<ShadowLoop>(m_triggerEntity).GetShadowAnim() == 6)
		{
			ECS::GetComponent<ShadowLoop>(m_triggerEntity).isShadowAlive = false;
			std::cout << "Shadow attacked\n";
		}
		else //player is attacking when the shadow is attacking and shadow deals damage to player
		{
			//ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).canMove = false;
			if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetDamaged() == false)
			{
				ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetKnockbackSequence(true);
				ECS::GetComponent<PhysicsBody>(m_targetEntities[0]).GetBody()->SetLinearVelocity(b2Vec2(1000000000 * normalX, 1000000000 * normalY));
				ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).HealthLost();
				ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetCanMove(false);
				ECS::GetComponent<ShadowLoop>(m_triggerEntity).SetShadowPauseSequence(true);
				ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetDamaged(true); //temporary invincibility
			}

		}
	}
	else if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetShield() == false)
	{
		if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetDamaged() == false)
		{
			//ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).canMove = false;
			ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetKnockbackSequence(true);
			ECS::GetComponent<PhysicsBody>(m_targetEntities[0]).GetBody()->SetLinearVelocity(b2Vec2(1000000000 * normalX, 1000000000 * normalY));
			ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).HealthLost();
			ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetCanMove(false);
			ECS::GetComponent<ShadowLoop>(m_triggerEntity).SetShadowPauseSequence(true);
			ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetDamaged(true); //temporary invincibility
		}		
	}
	else if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetShield() == true)
	{
		if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetDamaged() == false)
		{
			ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetKnockbackSequence(true);
			ECS::GetComponent<PhysicsBody>(m_targetEntities[0]).GetBody()->SetLinearVelocity(b2Vec2(1000000000 * normalX, 1000000000 * normalY));
			ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetCanMove(false);
			ECS::GetComponent<ShadowLoop>(m_triggerEntity).SetShadowPauseSequence(true);
			ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetDamaged(true); //temporary invincibility
		}		
	}	
	std::cout << "Current Health: " << ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetHealth() << "\n";
}

void KnockBackTrigger::OnExit()
{
	Trigger::OnExit();
}

void SpikeTrigger::OnEnter()
{
	double tempPlayerX = 0;
	double tempPlayerY = 0;

	double tempTriggerX = 0;
	double tempTriggerY = 0;

	double vectorX = 0;
	double vectorY = 0;

	tempPlayerX = ECS::GetComponent<PhysicsBody>(m_targetEntities[0]).GetBody()->GetPosition().x;
	tempPlayerY = ECS::GetComponent<PhysicsBody>(m_targetEntities[0]).GetBody()->GetPosition().y;

	tempTriggerX = ECS::GetComponent<PhysicsBody>(m_triggerEntity).GetBody()->GetPosition().x;
	tempTriggerY = ECS::GetComponent<PhysicsBody>(m_triggerEntity).GetBody()->GetPosition().y;

	vectorX = tempPlayerX - tempTriggerX;
	vectorY = tempPlayerY - tempTriggerY;

	double vectorMagnitude = sqrt((vectorX * vectorX) + (vectorY * vectorY));
	double normalX = vectorX / vectorMagnitude;
	double normalY = vectorY / vectorMagnitude;

	if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetShield() == false)
	{
		if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetDamaged() == false)
		{
			//ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).canMove = false;
			ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetKnockbackSequence(true);
			ECS::GetComponent<PhysicsBody>(m_targetEntities[0]).GetBody()->SetLinearVelocity(b2Vec2(1000000000 * normalX, 1000000000 * normalY));
			ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).HealthLost();
			ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetCanMove(false);
		}		
	}
	else if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetShield() == true)
	{
		if (ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).GetDamaged() == false)
		{
			ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetKnockbackSequence(true);
			ECS::GetComponent<PhysicsBody>(m_targetEntities[0]).GetBody()->SetLinearVelocity(b2Vec2(1000000000 * normalX, 1000000000 * normalY));
			ECS::GetComponent<PlayerMechanics>(m_targetEntities[0]).SetCanMove(false);
		}		
	}
}

void SpikeTrigger::OnExit()
{

}