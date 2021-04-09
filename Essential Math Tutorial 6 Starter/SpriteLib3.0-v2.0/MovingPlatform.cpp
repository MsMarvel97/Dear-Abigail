//#include "MovingPlatform.h"
//#include "Utilities.h"
//#include <random>
//
//MovingPlatform::MovingPlatform(std::string name)
//	: Scene(name)
//{
//	//yes gravity, this is a platformer
//	m_gravity = b2Vec2(0.f, -98.f);
//	m_physicsWorld->SetGravity(m_gravity);
//
//	m_physicsWorld->SetContactListener(&listener);
//}
//
//void MovingPlatform::InitScene(float windowWidth, float windowHeight)
//{
//	//Dynamically allocates the register
//	m_sceneReg = new entt::registry;
//
//	//Attach the register
//	ECS::AttachRegister(m_sceneReg);
//
//	//Sets up aspect ratio for the camera
//	float aspectRatio = windowWidth / windowHeight;
//
//	//Setup MainCamera Entity
//	{
//		//Creates Camera entity
//		auto entity = ECS::CreateEntity();
//		ECS::SetIsMainCamera(entity, true);
//
//		//Creates new orthographic camera
//		ECS::AttachComponent<Camera>(entity);
//		ECS::AttachComponent<HorizontalScroll>(entity);
//		ECS::AttachComponent<VerticalScroll>(entity);
//
//		vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f);
//		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
//		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
//		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
//
//		//Attaches the camera to vert and horiz scrolls
//		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
//		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
//	}
//
//	//main player entity
//	{
//		auto entity = ECS::CreateEntity();
//		ECS::SetIsMainPlayer(entity, true);
//		player = entity;
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//		ECS::AttachComponent<CanJump>(entity);
//		ECS::AttachComponent<MovingClass>(entity);
//
//		//Set up components
//		std::string fileName = "testCube.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 20);
//		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 30.f, 2.f));
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_dynamicBody;
//		tempDef.position.Set(float32(0.f), float32(30.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float((tempSpr.GetHeight() - shrinkY) / 2.f), vec2(0.f, 0.f), false, PLAYER, ENVIRONMENT | ENEMY | OBJECTS | PICKUP | TRIGGER | HEXAGON, 0.5f, 3.f);
//
//		tempPhsBody.SetRotationAngleDeg(0.f);
//		tempPhsBody.SetFixedRotation(true);
//		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
//		tempPhsBody.SetGravityScale(1.f);
//		tempPhsBody.SetMass(float(100.f));
//	}
//
//	//background
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//
//		//Set up components
//		std::string fileName = "background.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 627, 329);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 100.f, 1.f));
//	}
//
//	//moving platform trigger
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//		mTrigger = entity;
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//		ECS::AttachComponent<Trigger*>(entity);
//
//		//Sets up components
//		std::string fileName = "testCube.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 20);
//		ECS::GetComponent<Sprite>(entity).SetTransparency(0.5f);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 2.f));
//		ECS::GetComponent<Trigger*>(entity) = new MovingTrigger();
//		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(30.f), float32(50.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}
//
//	//Set up static platform
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//
//		//Sets up components
//		std::string fileName = "platform.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 2000, 30);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 2.f));
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(30.f), float32(-10.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | OBJECTS | HEXAGON);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}
//
//	//Set up moving platform
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//		movingPlat = entity;
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//		ECS::AttachComponent<Kinematics>(entity);
//
//		//Sets up components
//		std::string fileName = "platform.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 20);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 2.f));
//		ECS::GetComponent<Kinematics>(entity).SetChild(mTrigger);
//		ECS::GetComponent<Kinematics>(entity).SetParent(entity);
//		ECS::GetComponent<Kinematics>(entity).SetOffset(0.f, 10.f);
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_dynamicBody;
//		tempDef.position.Set(float32(30.f), float32(50.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, OBJECTS| PLAYER | ENEMY | HEXAGON);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//		tempBody->SetGravityScale(0.f);
//		tempBody->SetFixedRotation(true);
//	}
//
//	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//}
//
//void MovingPlatform::Update()
//{
//	ECS::GetComponent<Kinematics>(movingPlat).SetPosition();
//	MovingPlatform::MovePlatform();
//	MovingPlatform::ReattachCamera();
//}
//
//void MovingPlatform::KeyboardHold()
//{
//	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
//
//	float speed = 1.f;
//	b2Vec2 vel = b2Vec2(0.f, 0.f);
//
//	if (Input::GetKey(Key::Shift))
//	{
//		speed *= 5.f;
//	}
//
//	if (Input::GetKey(Key::A))
//	{
//		player.GetBody()->ApplyForceToCenter(b2Vec2(-10000.f * speed, 0.f), true);
//		//player.SetPosition(b2Vec2(player.GetPosition().x - 0.5, player.GetPosition().y));
//	}
//	if (Input::GetKey(Key::D))
//	{
//		player.GetBody()->ApplyForceToCenter(b2Vec2(10000.f * speed, 0.f), true);
//		//player.SetPosition(b2Vec2(player.GetPosition().x + 0.5, player.GetPosition().y));
//
//	}
//	if (Input::GetKey(Key::S))
//	{
//		player.GetBody()->ApplyForceToCenter(b2Vec2(0.f, -10000.f), true);
//	}
//
//	//Change physics body size for circle
//	if (Input::GetKey(Key::O))
//	{
//		player.ScaleBody(1.3 * Timer::deltaTime, 0);
//	}
//	else if (Input::GetKey(Key::I))
//	{
//		player.ScaleBody(-1.3 * Timer::deltaTime, 0);
//	}
//
//}
//
//void MovingPlatform::KeyboardDown()
//{
//	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
//	auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());
//
//	if (Input::GetKeyDown(Key::T))
//	{
//		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
//	}
//	if (canJump.m_canJump)
//	{
//		if (Input::GetKeyDown(Key::Space))
//		{
//			player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, 30000.f), true);
//			canJump.m_canJump = false;
//		}
//	}
//
//	if (Input::GetKeyDown(Key::Enter))
//	{
//		MovePlatform();
//	}
//}
//
//void MovingPlatform::KeyboardUp()
//{
//
//}
//
//void MovingPlatform::ReattachCamera()
//{
//	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//}
//
//void MovingPlatform::MovePlatform()
//{
//	auto& moveTrig = ECS::GetComponent<MovingClass>(player);
//	auto& playerBody = ECS::GetComponent<PhysicsBody>(player);
//	auto& plat = ECS::GetComponent<PhysicsBody>(movingPlat);
//	int platX = plat.GetPosition().x;
//	int platY = plat.GetPosition().y;
//	int playerX = playerBody.GetPosition().x;
//	int playerY = playerBody.GetPosition().y;
//	
//	if (platX > 500)
//	{
//		switchDir = true;
//	}
//	if (platX < 0)
//	{
//		switchDir = false;
//	}
//	if (switchDir == false)
//	{
//		platX += 1;
//		//plat.SetPosition(b2Vec2(platX, platY)); 
//		plat.SetVelocity(vec3(2000, 0, 0));
//		if (moveTrig.GetMoving() == true)
//		{
//			playerX += 1;
//			if (!Input::GetKey(Key::A))
//			{
//				playerBody.SetVelocity(vec3(5000, 0, 0));
//			}
//			//playerBody.SetPosition(b2Vec2(playerX, playerY));
//		}
//	}
//	else if (switchDir == true)
//	{
//		platX -= 1;
//		//plat.SetPosition(b2Vec2(platX, platY));
//		plat.SetVelocity(vec3(-2000, 0, 0));
//		if (moveTrig.GetMoving() == true)
//		{
//			if (!Input::GetKey(Key::D)) 
//			{
//				playerBody.SetVelocity(vec3(-5000, 0, 0));
//			}
//			playerX -= 1;
//			
//			//playerBody.SetPosition(b2Vec2(playerX, playerY));
//		}
//	}
//	
//}