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

	//JUMP Animations\\

	//Jump Right
	m_animController->AddAnimation(animations["JumpRight"].get<Animation>());
	//Jump Left
	m_animController->AddAnimation(animations["JumpLeft"].get<Animation>());

	//IDLE Animations\\

	//Idle Right
	m_animController->AddAnimation(animations["IdleRight"].get<Animation>());
	//Idle Left
	m_animController->AddAnimation(animations["IdleLeft"].get<Animation>());

	//Set Default Animation
	m_animController->SetActiveAnim(IDLELEFT);

}

void Player::Update()
{

	FrictionUpdate();

	if (!m_locked)
	{
		MovementUpdate();
	}

	AnimationUpdate();
}

void Player::MovementUpdate()
{
	m_moving = false;

	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& transformer = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());

	static float sprint = 0.f;
	static float vel = -2000;
	static float vel2 = 2000;

	if (Input::GetKey(Key::Shift) && player.GetVelocity().y < 0.0001 && player.GetVelocity().y > -0.0001)
	{
		if (sprint <= 3000.f)
		{
			float sprinting = 1000 * Timer::deltaTime;

			sprint += sprinting;
		}
	}

	if (!Input::GetKey(Key::Shift) || !(player.GetVelocity().y < 0.0001 && player.GetVelocity().y > -0.0001))
	{
		if (sprint > 0.f)
		{
			float slowing = 2000 * Timer::deltaTime;
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
		player.SetVelocity(vec3((vel - sprint) * Timer::deltaTime, player.GetVelocity().y, 0.f));
		if (vel >= -5000)
		{
			float subtractVel = 1000 * Timer::deltaTime;
			vel -= subtractVel;
		}
	}

	if (!Input::GetKey(Key::A))
	{
		if (vel < -2000.f)
		{
			float slowingVel = 2000 * Timer::deltaTime;
			vel += slowingVel;
		}

		if (vel > -2000.f)
		{
			vel = -2000.f;
		}
	}

	if (Input::GetKey(Key::D))
	{
		m_facing = RIGHT;
		m_moving = true;
		player.SetVelocity(vec3((vel2 + sprint) * Timer::deltaTime, player.GetVelocity().y, 0.f));
		if (vel2 <= 5000)
		{
			float addVel = 1000 * Timer::deltaTime;
			vel2 += addVel;
		}
	}
	if (!Input::GetKey(Key::D))
	{
		if (vel2 > 2000.f)
		{
			float slowingVel2 = 2000 * Timer::deltaTime;
			vel2 -= slowingVel2;
		}

		if (vel2 < 2000.f)
		{
			vel2 = 2000.f;
		}
	}

	if (Input::GetKeyDown(Key::Space) && (player.GetVelocity().y < 0.0001 && player.GetVelocity().y > -0.0001))
	{
		float jump = 30000.f;
		player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, jump), true);
	}

	// Old Movement Code \\

	//	if (m_hasPhysics)
	//	{
	//		float speed = 10.f;
	//		vec3 vel = vec3(0.f, 0.f, 0.f);
	//
	//		if (Input::GetKey(Key::Shift))
	//		{
	//			speed *= 7.f;
	//		}
	//
	//#ifdef TOPDOWN
	//		if (Input::GetKey(Key::W))
	//		{
	//			vel = vel + vec3(0.f, 1.f, 0.f);
	//			m_facing = UP;
	//			m_moving = true;
	//		}
	//		if (Input::GetKey(Key::S))
	//		{
	//			vel = vel + vec3(0.f, -1.f, 0.f);
	//			m_facing = DOWN;
	//			m_moving = true;
	//		}
	//#endif
	//
	//		if (Input::GetKey(Key::A))
	//		{
	//			vel = vel + vec3(-1.f, 0.f, 0.f);
	//
	//		}
	//		if (Input::GetKey(Key::D))
	//		{
	//			vel = vel + vec3(1.f, 0.f, 0.f);
	//
	//		}
	//
	//		m_physBody->SetVelocity(vel * speed);
	//	}
	//	else
	//	{
	//		//Regular Movement
	//		float speed = 15.f;
	//
	//#ifdef TOPDOWN
	//		if (Input::GetKey(Key::W))
	//		{
	//			m_transform->SetPositionY(m_transform->GetPositionY() + (speed * Timer::deltaTime));
	//			m_facing = UP;
	//			m_moving = true;
	//		}
	//		if (Input::GetKey(Key::S))
	//		{
	//			m_transform->SetPositionY(m_transform->GetPositionY() - (speed * Timer::deltaTime));
	//			m_facing = DOWN;
	//			m_moving = true;
	//		}
	//#endif
	//
	//		if (Input::GetKey(Key::A))
	//		{
	//			m_transform->SetPositionX(m_transform->GetPositionX() - (speed * Timer::deltaTime));
	//			m_facing = LEFT;
	//			m_moving = true;
	//		}
	//		if (Input::GetKey(Key::D))
	//		{
	//			m_transform->SetPositionX(m_transform->GetPositionX() + (speed * Timer::deltaTime));
	//			m_facing = RIGHT;
	//			m_moving = true;
	//		}
	//	}
	//
	//	if (Input::GetKeyDown(Key::Space))
	//	{
	//		/*m_moving = false;
	//
	//		if (m_hasPhysics)
	//		{
	//			m_physBody->SetVelocity(vec3());
	//		}
	//
	//		m_attacking = true;
	//		m_locked = true;*/
	//	} 
}

void Player::AnimationUpdate()
{
	int activeAnimation = 0;
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());

	if (!(player.GetVelocity().y < 0.0001 && player.GetVelocity().y > -0.0001))
	{
		activeAnimation = JUMP;
	}
	else if (m_moving)
	{
		activeAnimation = RUN;
	}
	else
	{
		activeAnimation = IDLE;
	}

	SetActiveAnimation(activeAnimation + (int)m_facing);
}

void Player::FrictionUpdate()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	
	if (player.GetVelocity().y < 0.0001 && player.GetVelocity().y > -0.0001)
	{
		player.GetBody()->SetLinearDamping(5.f);
	}
	else
	{
		player.GetBody()->SetLinearDamping(0.f);
	}
}

void Player::SetActiveAnimation(int anim)
{
	m_animController->SetActiveAnim(anim);
}
