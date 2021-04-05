#include "SceneTriggers.h"
#include "ECS.h"

void SceneSwapTrigger::OnEnter()
{
	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetComplete(true);
}

void SceneSwapTrigger::OnExit()
{

}

void PostcardTrigger::OnEnter()
{
	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetExamine(true);
}

void PostcardTrigger::OnExit()
{
	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetExamine(false);
}
