#include "FlaggedTrigger.h"
#include "ECS.h"


void FlaggedTrigger::OnEnter()
{
	Trigger::OnEnter();
	//setting collision flag to true for target entity on entering trigger
	ECS::GetComponent<CollisionFlag>(m_targetEntities[0]).SetCollisionTracker(true);
	//debug text
	if (ECS::GetComponent<CollisionFlag>(m_targetEntities[0]).GetCollisionTracker() == true)
	{
		std::cout << "it's flagged" << std::endl;
	}
}

void FlaggedTrigger::OnExit()
{
	Trigger::OnExit();
	//setting collision flag to true for target entity on entering trigger
	ECS::GetComponent<CollisionFlag>(m_targetEntities[0]).SetCollisionTracker(false);
	//debug text
	if (ECS::GetComponent<CollisionFlag>(m_targetEntities[0]).GetCollisionTracker() == false)
	{
		std::cout << "it's unflagged" << std::endl;
	}
}