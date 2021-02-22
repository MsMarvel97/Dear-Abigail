#include "DenialRough.h"
#include "Utilities.h"
#include <random>

DenialRough::DenialRough(std::string name)
	: Scene(name)
{
	//yes gravity, this is a platformer
	m_gravity = b2Vec2(0.f, -98.f);
	m_physicsWorld->SetGravity(m_gravity);

	m_physicsWorld->SetContactListener(&listener);
}

void DenialRough::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register
	m_sceneReg = new entt::registry;

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;

	//Setup MainCamera Entity
	{
		//Creates Camera entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainCamera(entity, true);

		//Creates new orthographic camera
		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<VerticalScroll>(entity);

		vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		//Attaches the camera to vert and horiz scrolls
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	}

	//background
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up components
		std::string fileName = "background.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 627, 329);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 100.f, 1.f));
	}

	//main player entity
	{
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainPlayer(entity, true);
		player = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<CanJump>(entity);
		ECS::AttachComponent<Health>(entity);


		//Set up components
		std::string fileName = "testCube.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 20);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 30.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(0.f), float32(30.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetHeight() / 2.f), vec2(0.f, 0.f), false, PLAYER, ENVIRONMENT | ENEMY | PICKUP | TRIGGER | HEXAGON | OBJECTS, 0.5f, 3.f);

		tempPhsBody.SetRotationAngleDeg(0.f);
		tempPhsBody.SetFixedRotation(true);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
		tempPhsBody.SetGravityScale(1.f);
	}

	//Set up static platform
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 2000, 30);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(30.f), float32(-10.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | OBJECTS | HEXAGON);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Set up shield
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shield = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		/*ECS::AttachComponent<PhysicsBody>(entity);*/
		ECS::AttachComponent<Kinematics>(entity);
		ECS::AttachComponent<ShieldMechanic>(entity);


		double playerSpriteX = ECS::GetComponent<Sprite>(player).GetWidth();
		double playerSpriteY = ECS::GetComponent<Sprite>(player).GetHeight();

		//Sets up components
		std::string fileName = "shield.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, playerSpriteX, playerSpriteY);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 4.f));
		ECS::GetComponent<Kinematics>(entity).SetChild(entity);
		ECS::GetComponent<Kinematics>(entity).SetParent(player);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0.f, 0.f);

		/*auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(30.f), float32(-10.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetHeight() / 2.f), vec2(0.f, 0.f), false, SHIELD, BULLET);
		tempPhsBody.SetColor(vec4(0.149f, 1.f, 0.f, 0.3f));*/
		//shieldVisible = true;
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		/*ECS::GetComponent<PhysicsBody>(entity).GetBody()->SetActive(false);*/
		//ECS::GetComponent<PhysicsBody>(entity).GetBody()->SetAwake(false);
	}

	//Shadow
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shadow = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Set up components
		std::string fileName = "shadow.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 20);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(60.f, 80.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(60.f), float32(80.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, ENEMY, OBJECTS);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void DenialRough::Update()
{
	auto& playerShield = ECS::GetComponent<Kinematics>(shield);
	auto& shieldThing = ECS::GetComponent<ShieldMechanic>(shield);
	playerShield.SetPosition();
	DenialRough::CheckShield();
	shieldThing.activateShield();
	DenialRough::ReattachCamera();
}

void DenialRough::KeyboardHold()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());

	float speed = 1.f;
	b2Vec2 vel = b2Vec2(0.f, 0.f);

	if (Input::GetKey(Key::Shift))
	{
		speed *= 5.f;
	}

	if (Input::GetKey(Key::A))
	{
		player.GetBody()->ApplyForceToCenter(b2Vec2(-120000.f * speed, 0.f), true);
		//player.SetPosition(b2Vec2(player.GetPosition().x - 0.5, player.GetPosition().y));
	}
	if (Input::GetKey(Key::D))
	{
		player.GetBody()->ApplyForceToCenter(b2Vec2(120000.f * speed, 0.f), true);
		//player.SetPosition(b2Vec2(player.GetPosition().x + 0.5, player.GetPosition().y));

	}

	//Change physics body size for circle
	if (Input::GetKey(Key::O))
	{
		player.ScaleBody(1.3 * Timer::deltaTime, 0);
	}
	else if (Input::GetKey(Key::I))
	{
		player.ScaleBody(-1.3 * Timer::deltaTime, 0);
	}
}

void DenialRough::KeyboardDown()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());
	auto& shieldSprite = ECS::GetComponent<Sprite>(shield);
	/*auto& shieldBody = ECS::GetComponent<PhysicsBody>(shield);*/
	auto& shieldMech = ECS::GetComponent<ShieldMechanic>(shield);

	if (Input::GetKeyDown(Key::T))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}
	if (canJump.m_canJump)
	{
		if (Input::GetKeyDown(Key::Space))
		{
			player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, 16000000000.f), true);
			canJump.m_canJump = false;
		}
	}

	if (Input::GetKeyDown(Key::Enter) && shieldMech.restart == true) //checks to see if the shield cooldown is complete before reactivating shield
	{
		shieldMech.setSequenceStart(true);
	}

	if (Input::GetKeyDown(Key::Y))
	{
		DenialRough::SpawnBullet();
		DenialRough::ShootBullet();
	}
}

void DenialRough::KeyboardUp()
{

}

void DenialRough::ReattachCamera()
{
	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void DenialRough::SpawnBullet()
{
	//Creates entity
	auto entity = ECS::CreateEntity();
	bullet = entity;

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Trigger*>(entity);

	//Set up components
	std::string fileName = "bullet.png";
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 5, 5);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(60.f, 80.f, 4.f));
	ECS::GetComponent<Trigger*>(entity) = new BulletTrigger();
	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_staticBody;
	tempDef.position.Set(float32(60.f), float32(80.f));

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | GROUND);
	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	tempPhsBody.SetGravityScale(0.f);

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void DenialRough::ShootBullet()
{
	auto& bulletBody = ECS::GetComponent<PhysicsBody>(bullet);
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	float deltaX = 0, deltaY = 0;
	deltaX = player.GetBody()->GetPosition().x - bulletBody.GetBody()->GetPosition().x;
	deltaY = player.GetBody()->GetPosition().y - bulletBody.GetBody()->GetPosition().y;
	float n_deltaX = 0, n_deltaY = 0;
	n_deltaX = deltaX / (deltaX * deltaX + deltaY * deltaY);
	n_deltaY = deltaY / (deltaX * deltaX + deltaY * deltaY);
	std::cout << deltaX << "," << deltaY << "\n";
	/*std::cout << n_deltaX << "," << n_deltaY << "\n";*/
	std::cout << "\n";
	bulletBody.GetBody()->SetType(b2BodyType::b2_dynamicBody);
	bulletBody.GetBody()->SetLinearVelocity(b2Vec2(deltaX * 100000000, deltaY * 100000000));
}

void DenialRough::CheckShield()
{
	//checks inputs from the ShieldMechanic and proceeds to turn the shield on or off
	auto& playerHealth = ECS::GetComponent<Health>(player);
	if (ECS::GetComponent<ShieldMechanic>(shield).shieldOn == true)
	{
		/*ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetActive(true);*/
		//ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetAwake(true);
		ECS::GetComponent<Sprite>(shield).SetTransparency(1.f);
		shieldActive = true; //currently useless
		playerHealth.setShield(true); //Used by the BulletTrigger to check if the shield is on.
	}
	else if (ECS::GetComponent<ShieldMechanic>(shield).shieldOn == false)
	{
		/*ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetActive(false);*/
		//ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetAwake(false);
		ECS::GetComponent<Sprite>(shield).SetTransparency(0.f);
		shieldActive = false; //currently useless
		playerHealth.setShield(false); //Used by the BulletTrigger to check if the shield is on.
	}
}
