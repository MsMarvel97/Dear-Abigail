#include "Player.h"

Player::Player()
{
}

Player::Player(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite,
	AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	InitPlayer(fileName, animationJSON, width, height, sprite, controller, transform, hasPhys, body);
}

void Player::InitPlayer(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite,
	AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	//Store references to the components
	m_sprite = sprite;
	m_animController = controller;
	m_transform = transform;
	m_hasPhysics = hasPhys;
	if (hasPhys)
	{
		m_physBody = body;
	}

	//Initialize UVs
	m_animController->InitUVs(fileName);

	//Loads the texture and sets width and height
	m_sprite->LoadSprite(fileName, width, height, true, m_animController);
	m_animController->SetVAO(m_sprite->GetVAO());
	m_animController->SetTextureSize(m_sprite->GetTextureSize());

	//Loads in the animations json file
	nlohmann::json animations = File::LoadJSON(animationJSON);

	//RUN ANIMATIONS\\
	
	//Run Right
	m_animController->AddAnimation(animations["RunRight"].get<Animation>());
	//Run Left
	m_animController->AddAnimation(animations["RunLeft"].get<Animation>());

	//JUMP ANIMATIONS\\

	//Jump Right
	m_animController->AddAnimation(animations["JumpRight"].get<Animation>());
	//Jump Left
	m_animController->AddAnimation(animations["JumpLeft"].get<Animation>());

	//IDLE ANIMATIONS\\

	//Idle Right
	m_animController->AddAnimation(animations["IdleRight"].get<Animation>());
	//Idle Left
	m_animController->AddAnimation(animations["IdleLeft"].get<Animation>());

	//RUN ATTACK ANIMATIONS\\
	
	//Run Right
	m_animController->AddAnimation(animations["RunRightAttack"].get<Animation>());
	//Run Left
	m_animController->AddAnimation(animations["RunLeftAttack"].get<Animation>());

	//JUMP ATTACK ANIMATIONS\\

	//Jump Right
	m_animController->AddAnimation(animations["JumpRightAttack"].get<Animation>());
	//Jump Left
	m_animController->AddAnimation(animations["JumpLeftAttack"].get<Animation>());

	//IDLE ATTACK ANIMATIONS\\

	//Idle Right
	m_animController->AddAnimation(animations["IdleRightAttack"].get<Animation>());
	//Idle Left
	m_animController->AddAnimation(animations["IdleLeftAttack"].get<Animation>());

	//RUN BLOCK ANIMATIONS\\
	
	//Run Right
	m_animController->AddAnimation(animations["RunRightBlock"].get<Animation>());
	//Run Left
	m_animController->AddAnimation(animations["RunLeftBlock"].get<Animation>());

	//JUMP BLOCK ANIMATIONS\\

	//Jump Right
	m_animController->AddAnimation(animations["JumpRightBlock"].get<Animation>());
	//Jump Left
	m_animController->AddAnimation(animations["JumpLeftBlock"].get<Animation>());

	//IDLE BLOCK ANIMATIONS\\

	//Idle Right
	m_animController->AddAnimation(animations["IdleRightBlock"].get<Animation>());
	//Idle Left
	m_animController->AddAnimation(animations["IdleLeftBlock"].get<Animation>());

	//Set Default Animation
	m_animController->SetActiveAnim(IDLERIGHT);

}

void Player::Update()
{

	FrictionUpdate();

	if (!m_locked)
	{
		MovementUpdate();
	}

	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).ActivateShield();
	AnimationUpdate();
}

void Player::MovementUpdate()
{
	m_moving = false;

	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& transformer = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& moving = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());

	static float sprint = 0.f;
	static float vel = -20;
	static float vel2 = 20;
	float time = Timer::deltaTime;
	static float jumping = 1000000.f;
	float platform = 0.f;

	if (moving.GetMoving() && !moving.GetUp())
	{
		if (!Input::GetKey(Key::D) && !Input::GetKey(Key::A))
		{
			float passiveMovement = 32.5;

			if (moving.GetLeft() == true)
			{
				passiveMovement *= -1;
			}
			player.SetVelocity(vec3(passiveMovement, player.GetVelocity().y, 0.f));
		}
	}

	if (Input::GetKey(Key::Shift) && !(moving.GetJumping()) && !moving.GetMoving())
	{
		if (sprint < 15.f)
		{
			float sprinting = 5;
			sprint += sprinting;
		}
	}

	if (!Input::GetKey(Key::Shift) || moving.GetJumping() || moving.GetMoving())
	{
		if (sprint > 0.f)
		{
			float slowing = 7.5;
			sprint -= slowing;
		}

		if (sprint < 0.f)
		{
			sprint = 0.f;
		}
	}

	if (Input::GetKey(Key::A))
	{
		m_facing = LEFT;
		m_moving = true;

		player.SetVelocity(vec3((vel - sprint), player.GetVelocity().y, 0.f));

		if (!moving.GetMoving())
		{
			if (vel >= -50)
			{
				float subtractiveVel = 5;
				vel -= subtractiveVel;
			}
		}
		else
		{
			vel = -60;
		}
	}

	if (!Input::GetKey(Key::A))
	{
		if (vel < -20.f)
		{
			float slowingVel = 5;
			vel += slowingVel;
		}

		if (vel > -20.f)
		{
			vel = -20.f;
		}
	}

	if (Input::GetKey(Key::D))
	{
		m_facing = RIGHT;
		m_moving = true;

		player.SetVelocity(vec3((vel2 + sprint), player.GetVelocity().y, 0.f));

		if (!moving.GetMoving())
		{
			if (vel2 <= 50)
			{
				float addVel = 5;
				vel2 += addVel;
			}
		}
		else
		{
			vel2 = 60;
		}
	}

	if (!Input::GetKey(Key::D))
	{
		if (vel2 > 20.f)
		{
			float slowingVel2 = 5;
			vel2 -= slowingVel2;
		}

		if (vel2 < 20.f)
		{
			vel2 = 20.f;
		}
	}

	if (Input::GetKeyDown(Key::Space) && (moving.GetUp() || !moving.GetJumping()))
	{
		float jump = 50.f;
		float jumpCharged = 82.f;

		if (Input::GetKey(Key::Shift))
		{
			player.SetVelocity(vec3(player.GetVelocity().x, jumpCharged, 0.f));
		}

		else
		{
			player.SetVelocity(vec3(player.GetVelocity().x, jump, 0.f));
		}
	}

	if (Input::GetKeyDown(Key::Q))
	{
		ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetShieldSequence(true);
	}

}

void Player::AnimationUpdate()
{
	int activeAnimation = 0;
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& pMechanics = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());

	if (pMechanics.GetJumping() && !(pMechanics.GetUp()))
	{
		if (ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).GetShield())
		{

			activeAnimation = JUMPBLOCK;
		}
		else if (ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).GetAttacking())
		{
			activeAnimation = JUMPATTACK;
		}
		else
		{
			activeAnimation = JUMP;
		}
	}
	else if (m_moving)
	{
		if (ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).GetShield())
		{
			activeAnimation = RUNBLOCK;
		}
		else if (ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).GetAttacking())
		{
			activeAnimation = RUNATTACK;
		}
		else
		{
			activeAnimation = RUN;
		}
	}
	else
	{
		if (ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).GetShield())
		{
			activeAnimation = IDLEBLOCK;
		}
		else if (ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).GetAttacking())
		{
			activeAnimation = IDLEATTACK;
		}
		else
		{
			activeAnimation = IDLE;
		}
	}

	SetActiveAnimation(activeAnimation + (int)m_facing);
}

void Player::FrictionUpdate()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& pMechanics = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	
	if (pMechanics.GetUp() || !(pMechanics.GetJumping()))
	{
		player.GetBody()->SetLinearDamping(5.f);
	}
	else
	{
		player.GetBody()->SetLinearDamping(0.f);
	}
}

void Player::UpdateAninControllerRef(AnimationController* ref)
{
	m_animController = ref;
}

void Player::SetActiveAnimation(int anim)
{
	ECS::GetComponent<AnimationController>(MainEntities::MainPlayer()).SetActiveAnim(anim);
}
