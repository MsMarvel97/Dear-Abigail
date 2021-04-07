#include "BreakableWall.h"

void BreakableWall::InitBreakableWall(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller)
{
	//Store references to the components
	sprites = sprite;
	animator = controller;

	//Initialize UVs
	animator->InitUVs(fileName);

	//Loads the texture and sets width and height
	sprites->LoadSprite(fileName, width, height, true, animator);
	animator->SetVAO(sprites->GetVAO());
	animator->SetTextureSize(sprites->GetTextureSize());

	//Loads in the animations json file
	nlohmann::json animations = File::LoadJSON(animationJSON);

	//PLATFORM ANIMATIONS\\
	//
	animator->AddAnimation(animations["PunchZero"].get<Animation>());
	//Idling left
	animator->AddAnimation(animations["PunchOne"].get<Animation>());
	//Idling right
	animator->AddAnimation(animations["PunchTwo"].get<Animation>());
	//Flying left
	animator->AddAnimation(animations["PunchThree"].get<Animation>());

	////Set Default Animation
	animator->SetActiveAnim(PUNCHZERO);
}

void BreakableWall::WallRoutine(int entity)
{
	if (ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).GetAttackSequence() && hit == true)
	{
		if (ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).GetDamageDealt() == false)
		{
			health--;
			ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetDamageDealt(true);
		}
	}

	if (wallDestroyed == false)
	{
		if (health == 3)
		{
			SetAnimation(0, entity);
		}
		else if (health == 2)
		{
			SetAnimation(1, entity);
		}
		else if (health == 1)
		{
			SetAnimation(2, entity);
		}
		else if (health == 0)
		{
			SetAnimation(3, entity);
			wallDestroyed = true;
		}
	}
	else
	{
		ECS::GetComponent<PhysicsBody>(entity).GetBody()->SetActive(false);
	}
	
}

void BreakableWall::SetAnimation(int animation, int entity)
{
	int choice = animation;
	ECS::GetComponent<AnimationController>(entity).SetActiveAnim(choice);
}
