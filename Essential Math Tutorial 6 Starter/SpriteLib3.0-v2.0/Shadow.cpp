//#include "Shadow.h"
//#include "Utilities.h"
//#include <random>
//
//Shadow::Shadow(std::string name)
//	: Scene(name)
//{
//	//yes gravity, this is a platformer
//	m_gravity = b2Vec2(0.f, -98.f);
//	m_physicsWorld->SetGravity(m_gravity);
//
//	m_physicsWorld->SetContactListener(&listener);
//}
//
//void Shadow::InitScene(float windowWidth, float windowHeight)
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
//		vec4 temp = vec4(-100.f, 100.f, -100.f, 100.f);
//		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
//		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
//		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
//
//		//Attaches the camera to vert and horiz scrolls
//		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
//		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
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
//	//main player entity
//	{
//		auto entity = ECS::CreateEntity();
//		ECS::SetIsMainPlayer(entity, true);
//		player = entity;
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
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
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_dynamicBody;
//		tempDef.position.Set(float32(0.f), float32(30.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetHeight() / 2.f), vec2(0.f, 0.f), false, PLAYER, ENVIRONMENT | ENEMY | PICKUP | TRIGGER | HEXAGON | OBJECTS, 0.5f, 3.f);
//
//		tempPhsBody.SetRotationAngleDeg(0.f);
//		tempPhsBody.SetFixedRotation(true);
//		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
//		tempPhsBody.SetGravityScale(1.f);
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
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | OBJECTS | HEXAGON | TRIGGER);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}
//
//	//Set up shadow
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//		shadow = entity;
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//
//		//Sets up components
//		std::string fileName = "shadow2.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 20);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(90.f, 80.f, 2.f));
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(90.f), float32(120.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, ENEMY, OBJECTS | HEXAGON);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}
//
//	//Set up bullet
//	//{
//	//	//Creates entity
//	//	auto entity = ECS::CreateEntity();
//	//	bullet = entity;
//
//	//	//Add components
//	//	ECS::AttachComponent<Sprite>(entity);
//	//	ECS::AttachComponent<Transform>(entity);
//	//	ECS::AttachComponent<PhysicsBody>(entity);
//	//	ECS::AttachComponent<Trigger*>(entity);
//
//	//	//Sets up components
//	//	std::string fileName = "bullet.png";
//	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 5);
//	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 4.f));
//	//	ECS::GetComponent<Trigger*>(entity) = new Boomerang();
//	//	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//	//	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
//	//	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(shadow);
//
//	//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//	//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//	//	float shrinkX = 0.f;
//	//	float shrinkY = 0.f;
//	//	b2Body* tempBody;
//	//	b2BodyDef tempDef;
//	//	tempDef.type = b2_dynamicBody;
//	//	tempDef.position.Set(float32(70.f), float32(130.f));
//
//	//	tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//	//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//	//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, GROUND | PLAYER);
//	//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	//}
//
//
//
//	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//}
//
//void Shadow::Update()
//{
//	/*Shadow::MoveBullet();*/
//	/*if (testVariable == true)
//	{
//		Shadow::TestFunction();
//	}*/
//	Shadow::ReattachCamera();
//}
//
//void Shadow::KeyboardHold()
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
//		player.GetBody()->ApplyForceToCenter(b2Vec2(-120000.f * speed, 0.f), true);
//		//player.SetPosition(b2Vec2(player.GetPosition().x - 0.5, player.GetPosition().y));
//	}
//	if (Input::GetKey(Key::D))
//	{
//		player.GetBody()->ApplyForceToCenter(b2Vec2(120000.f * speed, 0.f), true);
//		//player.SetPosition(b2Vec2(player.GetPosition().x + 0.5, player.GetPosition().y));
//
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
//void Shadow::KeyboardDown()
//{
//	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
//	auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());
//	auto& shadowLoc = ECS::GetComponent<PhysicsBody>(shadow);
//
//	if (Input::GetKeyDown(Key::T))
//	{
//		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
//	}
//	if (canJump.m_canJump)
//	{
//		if (Input::GetKeyDown(Key::Space))
//		{
//			player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, 16000000000.f), true);
//			canJump.m_canJump = false;
//		}
//	}
//	if (Input::GetKeyDown(Key::Enter))
//	{
//		Shadow::MakeBullet();
//		auto& bulletBody = ECS::GetComponent<PhysicsBody>(bullet);
//
//		//float diffX = player.GetPosition().x - bulletBody.GetBody()->GetPosition().x;
//		//float diffY = player.GetPosition().y - bulletBody.GetBody()->GetPosition().y;
//
//		///*float diffX = bulletBody.GetBody()->GetPosition().x - player.GetPosition().x;
//		//float diffY = bulletBody.GetBody()->GetPosition().y - player.GetPosition().y;*/
//
//		//float lengthOfVector = sqrt((diffX * diffX) + (diffY * diffY));
//		//float diffXNormal = diffX / lengthOfVector;
//		//float diffYNormal = diffY / lengthOfVector;
//		//float tanX = diffYNormal / diffXNormal;
//		//float bulletAngle = (atan(tanX) * 180 / PI);
//		//b2Body* tempBody;
//		//b2BodyDef tempDef;
//		//tempDef.type = b2_dynamicBody;
//		//tempBody = m_physicsWorld->CreateBody(&tempDef);
//		//tempDef.position.Set(float32(70.f), float32(100.f));
//
//		//bulletBody.GetBody()->SetType(b2BodyType::b2_dynamicBody);
//		//bulletBody.SetRotationAngleDeg(bulletAngle);
//		//bulletBody.GetBody()->ApplyLinearImpulse(b2Vec2(-100, 0), b2Vec2(bulletBody.GetPosition().x, bulletBody.GetPosition().y), true);
//		//bulletBody.GetBody()->SetLinearVelocity(b2Vec2((diffXNormal * 10000), (diffYNormal * 10000)));
//
//		///*bulletBody.GetBody()->SetAngularVelocity(7.f);*/ //makes the object spin
//
//		//std::cout << "Player: " << "(" << player.GetPosition().x << "," << player.GetPosition().y << ")\n";
//		//std::cout << "Bullet: " << "(" << bulletBody.GetBody()->GetPosition().x << "," << bulletBody.GetBody()->GetPosition().y << ")\n";
//		//std::cout << "diffX: " << diffX << "\n";
//		//std::cout << "diffY: " << diffY << "\n";
//		//std::cout << "Bullet Angle: " << bulletAngle << "\n";
//		//std::cout << "Normalized X: " << diffXNormal << "\n";
//		//std::cout << "Normalized Y: " << diffYNormal << "\n";
//	}
//}
//
//void Shadow::KeyboardUp()
//{
//
//}
//
//void Shadow::ReattachCamera()
//{
//	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//}
//
////void Shadow::MoveBullet()
////{
////	auto& playerThing = ECS::GetComponent<TestBulet>(player);
////	auto& bulletBody =	ECS::GetComponent<PhysicsBody>(bullet);
////	
////	if (playerThing.getResetPosition() == true)
////	{
////		bulletBody.SetPosition(b2Vec2(playerThing.getAnchorX(), playerThing.getAnchorY()));
////		playerThing.setResetPosition(false);
////	}	
////}
//
//void Shadow::MakeBullet()
////setup bullet 2
//{
//	auto& shadowBody = ECS::GetComponent<PhysicsBody>(shadow);
//	//Creates entity
//	auto entity = ECS::CreateEntity();
//	bullet = entity;
//
//	//Add components
//	ECS::AttachComponent<Sprite>(entity);
//	ECS::AttachComponent<Transform>(entity);
//	ECS::AttachComponent<PhysicsBody>(entity);
//	ECS::AttachComponent<Trigger*>(entity);
//
//	//Sets up components
//	std::string fileName = "bullet.png";
//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(shadowBody.GetPosition().x, shadowBody.GetPosition().y, 4.f));
//	ECS::GetComponent<Trigger*>(entity) = new DestroyTrigger();
//	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(entity);
//
//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//	float shrinkX = 0.f;
//	float shrinkY = 0.f;
//	b2Body* tempBody;
//	b2BodyDef tempDef;
//	tempDef.type = b2_staticBody;
//	tempDef.position.Set(shadowBody.GetPosition().x, shadowBody.GetPosition().y);
//	tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, GROUND | PLAYER);
//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//}
//
//void Shadow::TestFunction()
//{
//	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
//	player.GetBody()->SetLinearVelocity(b2Vec2(100.f, 10.f));
//}
