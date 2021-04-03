#include "SceneSwapTrigger.h"
#include "ECS.h"

void SceneSwapTrigger::OnEnter()
{
	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetComplete(true);
}

void SceneSwapTrigger::OnExit()
{

}
