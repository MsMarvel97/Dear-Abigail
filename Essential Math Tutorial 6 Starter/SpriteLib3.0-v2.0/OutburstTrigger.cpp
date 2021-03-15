#include "OutburstTrigger.h"
#include "ECS.h"

void OutburstTrigger::OnEnter()
{
	Trigger::OnEnter();
	if (!triggered)
	{
		srand(time(0));
		for (int i = 0; i < m_targetEntities.size(); i++)
		{
			ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).GetBody()->SetLinearVelocity(b2Vec2(100000000000*rand(), 100000000000*rand()));
			ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).GetBody()->ApplyAngularImpulse(float32(80), true);
			std::cout << rand() << "\n";
		}

		triggered = true;
	}
}

void OutburstTrigger::OnExit()
{
	Trigger::OnExit();
}
