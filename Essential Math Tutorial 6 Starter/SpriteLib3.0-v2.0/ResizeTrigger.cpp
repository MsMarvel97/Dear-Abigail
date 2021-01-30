#include "ResizeTrigger.h"
#include "ECS.h"

void ResizeTrigger::OnEnter()
{
	Trigger::OnEnter();
	
	//if not triggered
	if (!triggered)
	{
		//for each targeted entity
		for (int i = 0; i < m_targetEntities.size(); i++)
		{
			//setting local vars to hold scaling x and y
			float x;
			float y;
			const auto body = ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).GetBodyType();

			//if it's a circle do this
			if (body == BodyType::CIRCLE)
			{
				//set scaled radius
				float scaledRadius = (ECS::GetComponent<Sprite>(m_targetEntities[i]).GetWidth() / 2.f) * scalar;
				//set x to width of object plus scaled radius
				x = ECS::GetComponent<Sprite>(m_targetEntities[i]).GetWidth() + scaledRadius;
				//set y to width of object plus scaled radius
				y = ECS::GetComponent<Sprite>(m_targetEntities[i]).GetHeight() + scaledRadius;
			}
			//deprecated code for scaling rectangles
			else
			{
				x = ECS::GetComponent<Sprite>(m_targetEntities[i]).GetWidth() * scalar;
				y = ECS::GetComponent<Sprite>(m_targetEntities[i]).GetHeight() * scalar;
			}

			//scaling physics body with scalar and fixtures of entity
			ECS::GetComponent<PhysicsBody>(m_targetEntities[i]).ScaleBody(scalar, fixtures);
			//scaling sprite with x and y and setting sprite to set value
			ECS::GetComponent<Sprite>(m_targetEntities[i]).LoadSprite(spriteScale, x, y);
			triggered = true;
		}
	}
}

void ResizeTrigger::OnExit()
{
	Trigger::OnExit();
}
