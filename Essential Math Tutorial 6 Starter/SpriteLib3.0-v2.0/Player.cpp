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

<<<<<<< HEAD
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& transformer = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());
	auto& moving = ECS::GetComponent<MovingClass>(MainEntities::MainPlayer());

	static float sprint = 0.f;
	static float vel = -2000;
	static float vel2 = 2000;
	float time = Timer::deltaTime;
	static float jumping = 1000000.f;
	float platform = 0.f;

	if (moving.GetMoving())
=======
<<<<<<< Updated upstream
	if (m_hasPhysics)
>>>>>>> AngerLevel
	{
		platform = 2000.f;

		if (!Input::GetKey(Key::D) && !Input::GetKey(Key::A))
		{
			float passiveMovement = 57000.f; //57000.f

			if (moving.GetLeft() == true)
			{
				passiveMovement *= -1;
			}
			player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(passiveMovement * Timer::deltaTime, 0.f), true);
		}
	}

	if (Input::GetKey(Key::Shift) && player.GetVelocity().y < 0.0001 && player.GetVelocity().y > -0.0001)
	{
		if (sprint <= 3000.f)
		{
<<<<<<< HEAD
			float sprinting = 5;
			sprint += sprinting;
=======
			speed *= 7.f;
=======
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& transformer = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());
	auto& moving = ECS::GetComponent<MovingClass>(MainEntities::MainPlayer());

	static float sprint = 0.f;
	static float vel = -2000;
	static float vel2 = 2000;
	float time = Timer::deltaTime;
	static float jumping = 1000000.f;
	float platform = 0.f;

	if (moving.GetMoving())
	{
		platform = 2000.f;

		if (!Input::GetKey(Key::D) && !Input::GetKey(Key::A))
		{
			float passiveMovement = 57000.f; //57000.f

			if (moving.GetLeft() == true)
			{
				passiveMovement *= -1;
			}
			player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(passiveMovement * Timer::deltaTime, 0.f), true);
		}
	}

	if (Input::GetKey(Key::Shift) && player.GetVelocity().y < 0.0001 && player.GetVelocity().y > -0.0001)
	{
		if (sprint <= 3000.f)
		{
			float sprinting = 1000 * Timer::deltaTime;
			sprint += sprinting;
>>>>>>> Stashed changes
>>>>>>> AngerLevel
		}
	}

	if (!Input::GetKey(Key::Shift) || !(player.GetVelocity().y < 0.0001 && player.GetVelocity().y > -0.0001) || moving.GetMoving())
	{
		if (sprint > 0.f)
		{
			float slowing = 20;
			sprint -= slowing;
		}

<<<<<<< Updated upstream
		if (Input::GetKey(Key::A))
=======
	if (Input::GetKey(Key::A))
	{
		m_facing = LEFT;
		m_moving = true;

		player.SetVelocity(vec3((vel - sprint - platform) * Timer::deltaTime, player.GetVelocity().y, 0.f));

		if (vel >= -5000)
>>>>>>> Stashed changes
		{
			sprint = 0.f;
		}
	}

	if (Input::GetKey(Key::A))
	{
		m_facing = LEFT;
		m_moving = true;

<<<<<<< HEAD
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
=======
<<<<<<< Updated upstream
		if (Input::GetKey(Key::A))
=======
	if (Input::GetKey(Key::A))
	{
		m_facing = LEFT;
		m_moving = true;

		player.SetVelocity(vec3((vel - sprint - platform) * Timer::deltaTime, player.GetVelocity().y, 0.f));

		if (vel >= -5000)
>>>>>>> Stashed changes
>>>>>>> AngerLevel
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

<<<<<<< HEAD
	if (!Input::GetKey(Key::D))
	{
		if (vel2 > 20.f)
=======
<<<<<<< Updated upstream
		if (Input::GetKey(Key::A))
=======
	if (Input::GetKey(Key::D))
	{
		m_facing = RIGHT;
		m_moving = true;

		player.SetVelocity(vec3((vel2 + sprint + platform) * Timer::deltaTime, player.GetVelocity().y, 0.f));

		if (vel2 <= 5000)
>>>>>>> Stashed changes
>>>>>>> AngerLevel
		{
			float slowingVel2 = 5;
			vel2 -= slowingVel2;
		}

		if (vel2 < 20.f)
		{
			vel2 = 20.f;
		}
	}

	/*if (Input::GetKey(Key::C) && (player.GetVelocity().y < 0.0001 && player.GetVelocity().y > -0.0001))
	{
		if (jumping <= 180000)
		{
			float building = 150000.f;
			jumping += building;
		}
		else
		{
			jumping = 180000;
		}
	}*/

	if (Input::GetKeyDown(Key::Space) && (player.GetVelocity().y < 0.0001 && player.GetVelocity().y > -0.0001))
	{
		float jump = 16000;
		float jumpCharged = 30000;

		if (Input::GetKey(Key::Shift))
		{
			player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0, jumpCharged), true);
		}

<<<<<<< HEAD
		else
		{
			jumping = 1800000;
		}
=======
<<<<<<< Updated upstream
		m_attacking = true;
		m_locked = true;*/
>>>>>>> AngerLevel
	}
=======
	if (Input::GetKey(Key::C) && (player.GetVelocity().y < 0.0001 && player.GetVelocity().y > -0.0001))
	{
		if (jumping <= 1800000)
		{
			float building = 1500000.f * Timer::deltaTime;
			jumping += building;
		}
		else
		{
			jumping = 1800000;
		}
	}

	if (Input::GetKeyDown(Key::Space) && (player.GetVelocity().y < 0.0001 && player.GetVelocity().y > -0.0001))
	{
		float jump = 1000000 * Timer::deltaTime;
		float jumpCharged = 1800000 * Timer::deltaTime;

		if (Input::GetKey(Key::Shift))
		{
			player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, jumpCharged), true);
		}

		else
		{
			player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, jump), true);
		}
		jumping = 1000000.f;
	}

	if (Input::GetKey(Key::W))
	{
		player.SetVelocity(vec3(0.f, 100.f, 0.f));
	}

	// Old Movement Code \\

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
>>>>>>> Stashed changes
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
<<<<<<< HEAD
	
=======

>>>>>>> AngerLevel
	if (player.GetVelocity().y < 0.0001 && player.GetVelocity().y > -0.0001)
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

<<<<<<< HEAD


=======
>>>>>>> AngerLevel
void Player::SetActiveAnimation(int anim)
{
	ECS::GetComponent<AnimationController>(MainEntities::MainPlayer()).SetActiveAnim(anim);
}
