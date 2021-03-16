//#include "AttackScene.h"
//#include "Utilities.h"
//#include <random>
//
//AttackScene::AttackScene(std::string name)
//	: Scene(name)
//{
//	//yes gravity, this is a platformer
//	m_gravity = b2Vec2(0.f, -98.f);
//	m_physicsWorld->SetGravity(m_gravity);
//
//	m_physicsWorld->SetContactListener(&listener);
//}
//
//void AttackScene::InitScene(float windowWidth, float windowHeight)
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
//		ECS::AttachComponent<CanJump>(entity);
//		ECS::AttachComponent<AttackMechanic>(entity);
//		ECS::AttachComponent<Health>(entity);
//		ECS::AttachComponent<Player>(entity);
//		ECS::AttachComponent<KnockBack>(entity);
//		ECS::AttachComponent<CoolDown>(entity);
//		ECS::AttachComponent<BossLevel>(entity);
//		ECS::AttachComponent<ShadowSense>(entity);
//		ECS::AttachComponent<ShadowTime>(entity);
//
//		//Set up components
//		std::string fileName = "testCube.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 20);
//		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 30.f, 2.f));
//		ECS::GetComponent<Health>(entity).SetHealth(3);
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
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()), vec2(0.f, 0.f), false, PLAYER, ENVIRONMENT | ENEMY | PICKUP | TRIGGER | HEXAGON | OBJECTS, 0.5f, 3.f);
//
//		tempPhsBody.SetRotationAngleDeg(0.f);
//		tempPhsBody.SetFixedRotation(true);
//		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
//		tempPhsBody.SetGravityScale(1.f);
//	}
//
//	//Set up shield
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//		shield = entity;
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		/*ECS::AttachComponent<PhysicsBody>(entity);*/
//		ECS::AttachComponent<Kinematics>(entity);
//		ECS::AttachComponent<ShieldMechanic>(entity);
//
//
//		double playerSpriteX = ECS::GetComponent<Sprite>(player).GetWidth();
//		double playerSpriteY = ECS::GetComponent<Sprite>(player).GetHeight();
//
//		//Sets up components
//		std::string fileName = "shield.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, playerSpriteX, playerSpriteY);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 4.f));
//		ECS::GetComponent<Kinematics>(entity).SetChild(entity);
//		ECS::GetComponent<Kinematics>(entity).SetParent(player);
//		ECS::GetComponent<Kinematics>(entity).SetOffset(0.f, 0.f);
//
//		/*auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(30.f), float32(-10.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetHeight() / 2.f), vec2(0.f, 0.f), false, SHIELD, BULLET);
//		tempPhsBody.SetColor(vec4(0.149f, 1.f, 0.f, 0.3f));*/
//		//shieldVisible = true;
//		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
//		/*ECS::GetComponent<PhysicsBody>(entity).GetBody()->SetActive(false);*/
//		//ECS::GetComponent<PhysicsBody>(entity).GetBody()->SetAwake(false);
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
//	//Set up enemy 1
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//		enemy1 = entity;
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//		ECS::AttachComponent<Trigger*>(entity);
//		ECS::AttachComponent<ShadowLoop>(entity);
//
//		//Sets up components
//		std::string fileName = "shadow2.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 30, 30);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-60.f, 30.f, 2.f));
//		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
//		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
//		ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(-60.f), float32(30.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER );
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}
//
//	//Set up attack trigger for enemy 1
//	/*{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//		enemy1Trigger = entity;
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//		ECS::AttachComponent<Trigger*>(entity);
//
//		//Sets up components
//		std::string fileName = "testCube.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 50);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-60.f, 30.f, 2.f));
//		ECS::GetComponent<Trigger*>(entity) = new AttackTrigger();
//		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
//		ECS::GetComponent<Trigger*>(entity)->SetShadowZone(1); //change this value for each enemy
//		ECS::GetComponent<Sprite>(entity).SetTransparency(0.5f);
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(-60.f), float32(30.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}*/
//
//	//Set up enemy 2
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//		enemy2 = entity;
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//		ECS::AttachComponent<Trigger*>(entity);
//		ECS::AttachComponent<ShadowLoop>(entity);
//
//		//Sets up components
//		std::string fileName = "shadow2.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 30, 30);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(120.f, 30.f, 2.f));
//		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
//		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
//		ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(120.f), float32(30.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}
//
//	//Set up attack trigger for enemy 2
//	/*{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//		enemy2Trigger = entity;
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//		ECS::AttachComponent<Trigger*>(entity);
//
//		//Sets up components
//		std::string fileName = "testCube.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 50);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(120.f, 30.f, 2.f));
//		ECS::GetComponent<Trigger*>(entity) = new AttackTrigger();
//		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
//		ECS::GetComponent<Trigger*>(entity)->SetShadowZone(2); //change this value for each enemy
//		ECS::GetComponent<Sprite>(entity).SetTransparency(0.5f);
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(120.f), float32(30.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}*/
//	
//	//setup orb 1
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//		ECS::AttachComponent<Trigger*>(entity);
//
//		//Sets up components
//		std::string fileName = "shadowOrb.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(160.f, 30.f, 2.f));
//		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
//		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
//		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(160.f), float32(30.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}
//
//	//setup orb 2
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//		ECS::AttachComponent<Trigger*>(entity);
//
//		//Sets up components
//		std::string fileName = "shadowOrb.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(190.f, 30.f, 2.f));
//		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
//		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
//		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(190.f), float32(30.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}
//
//	//setup orb 3
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//		ECS::AttachComponent<Trigger*>(entity);
//
//		//Sets up components
//		std::string fileName = "shadowOrb.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(220.f, 30.f, 2.f));
//		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
//		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
//		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(220.f), float32(30.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}
//
//	//setup orb 4
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//		ECS::AttachComponent<Trigger*>(entity);
//
//		//Sets up components
//		std::string fileName = "shadowOrb.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(250.f, 30.f, 2.f));
//		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
//		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
//		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(250.f), float32(30.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}
//
//	//setup orb 5
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//		ECS::AttachComponent<Trigger*>(entity);
//
//		//Sets up components
//		std::string fileName = "shadowOrb.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(280.f, 30.f, 2.f));
//		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
//		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
//		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(280.f), float32(30.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}
//
//	//set up boss
//	{
//
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//		boss = entity;
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//
//		//Set up components
//		std::string fileName = "bossTemp.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 30, 30);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(120.f, 80.f, 3.f));
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(120.f), float32(80.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, ENEMY, OBJECTS);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}
//
//	//Area Trigger for boss
//	{
//		//Creates entity
//		auto entity = ECS::CreateEntity();
//
//		//Add components
//		ECS::AttachComponent<Sprite>(entity);
//		ECS::AttachComponent<Transform>(entity);
//		ECS::AttachComponent<PhysicsBody>(entity);
//		ECS::AttachComponent<Trigger*>(entity);
//
//		//Sets up components
//		std::string fileName = "sandFloor.png";
//		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 200,110);
//		ECS::GetComponent<Transform>(entity).SetPosition(vec3(200.f, 60.f, 5.f));
//		ECS::GetComponent<Trigger*>(entity) = new ShadowAreaTrigger();
//		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
//		ECS::GetComponent<Trigger*>(entity)->SetShadowZone(1);
//		ECS::GetComponent<Sprite>(entity).SetTransparency(0.5f);
//
//		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//		float shrinkX = 0.f;
//		float shrinkY = 0.f;
//		b2Body* tempBody;
//		b2BodyDef tempDef;
//		tempDef.type = b2_staticBody;
//		tempDef.position.Set(float32(200.f), float32(30.f));
//
//		tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
//		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//	}
//	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//}
//
//void AttackScene::Update()
//{
//	auto& playerSprite = ECS::GetComponent<Sprite>(player);
//	auto& thePlayer = ECS::GetComponent<Player>(player);
//	auto& playerShield = ECS::GetComponent<Kinematics>(shield);
//	auto& shieldThing = ECS::GetComponent<ShieldMechanic>(shield);
//	auto& isKnocked = ECS::GetComponent<KnockBack>(player);
//	auto& attackComponent = ECS::GetComponent<AttackMechanic>(player);
//	auto& theCoolDown = ECS::GetComponent<CoolDown>(player);
//	auto& angerBoss = ECS::GetComponent<BossLevel>(player);
//	auto& shadowThing2 = ECS::GetComponent<ShadowTime>(player);
//	auto& bossSprite = ECS::GetComponent<Sprite>(boss);
//	auto& bossBody = ECS::GetComponent<PhysicsBody>(boss);
//	isKnocked.RunKnockBackTime();
//	playerShield.UpdatePosition();
//	AttackScene::CheckShield();
//	shieldThing.activateShield();
//	AttackScene::ReattachCamera();
//	if (isKnocked.GetCanMove()==true)
//	{
//		thePlayer.Update();
//	}	
//	attackComponent.Attacking();
//
//	if (ECS::GetComponent<ShadowLoop>(enemy1).isShadowAlive == true)
//	{
//		ECS::GetComponent<ShadowLoop>(enemy1).ShadowRoutine();
//		AttackScene::ChangeVisualState(enemy1);
//		
//	}
//	if (ECS::GetComponent<ShadowLoop>(enemy2).isShadowAlive == true)
//	{
//		ECS::GetComponent<ShadowLoop>(enemy2).ShadowRoutine();
//		AttackScene::ChangeVisualState(enemy2);
//	}
//	
//	if (ECS::GetComponent<ShadowLoop>(enemy1).isShadowAlive == false)
//	{
//		ECS::GetComponent<PhysicsBody>(enemy1).GetBody()->SetActive(false);
//		ECS::GetComponent<Sprite>(enemy1).SetTransparency(0.f);
//	}
//	if (ECS::GetComponent<ShadowLoop>(enemy2).isShadowAlive == false)
//	{
//		ECS::GetComponent<PhysicsBody>(enemy2).GetBody()->SetActive(false);
//		ECS::GetComponent<Sprite>(enemy2).SetTransparency(0.f);
//	}
//
//	if (attackComponent.isAttacking == true)
//	{
//		playerSprite.LoadSprite(attackPose, 20, 20);
//	}
//	else if (attackComponent.isAttacking == false)
//	{
//		playerSprite.LoadSprite(defaultPose, 20, 20);
//	}
//	theCoolDown.GlobalCoolDown();
//	angerBoss.CheckBossStatus();
//	shadowThing2.RunShadowTime();
//	if (angerBoss.GetBossDefeated() == false)
//	{
//		AttackScene::ActivateShadow();
//	}
//	else
//	{
//		bossSprite.SetTransparency(0.f);
//		bossBody.GetBody()->SetActive(false);
//	}
//	
//}
//
//void AttackScene::KeyboardHold()
//{
//	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
//	float speed = 1.f;
//	b2Vec2 vel = b2Vec2(0.f, 0.f);
//
//	//if (Input::GetKey(Key::Shift))
//	//{
//	//	speed *= 5.f;
//	//}
//
//	//if (Input::GetKey(Key::A))
//	//{
//	//	player.GetBody()->ApplyForceToCenter(b2Vec2(-120000.f * speed, 0.f), true);
//	//	//player.SetPosition(b2Vec2(player.GetPosition().x - 0.5, player.GetPosition().y));
//	//}
//	//if (Input::GetKey(Key::D))
//	//{
//	//	player.GetBody()->ApplyForceToCenter(b2Vec2(120000.f * speed, 0.f), true);
//	//	//player.SetPosition(b2Vec2(player.GetPosition().x + 0.5, player.GetPosition().y));
//	//}
//}
//
//void AttackScene::KeyboardDown()
//{
//	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
//	auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());
//	auto& attackComponent = ECS::GetComponent<AttackMechanic>(MainEntities::MainPlayer());
//	auto& shieldSprite = ECS::GetComponent<Sprite>(shield);
//	auto& shieldMech = ECS::GetComponent<ShieldMechanic>(shield);
//	auto& theCoolDown = ECS::GetComponent<CoolDown>(MainEntities::MainPlayer());
//	auto& angerBoss = ECS::GetComponent<BossLevel>(MainEntities::MainPlayer());
//
//	if (Input::GetKeyDown(Key::T))
//	{
//		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
//	}
//	/*if (canJump.m_canJump)
//	{
//		if (Input::GetKeyDown(Key::Space))
//		{
//			player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, 36000000.f), true);
//			canJump.m_canJump = false;
//		}
//	}*/
//	/*if (Input::GetKeyDown(Key::E))
//	{
//		if (attackComponent.GetRange() == true)
//		{
//			AttackScene::Defeated();
//		}
//	}*/
//
//	if (Input::GetKeyDown(Key::Enter) && shieldMech.restart == true && theCoolDown.isCoolDownActive == false) //checks to see if the shield cooldown if complete before reactivating shield
//	{
//		shieldMech.setSequenceStart(true);
//		theCoolDown.SetSequenceStart(true);
//	}
//
//	if (Input::GetKeyDown(Key::E) && attackComponent.getSequenceStart() == false && theCoolDown.isCoolDownActive == false)
//	{
//		attackComponent.setSequenceStart(true);
//		theCoolDown.SetSequenceStart(true);
//	}
//
//	if (Input::GetKeyDown(Key::B))
//	{
//		std::cout << "Orbs remaining: " << angerBoss.GetOrbs() << "\n";
//		std::cout << "Boss Defeated: " << angerBoss.GetBossDefeated() << "\n";
//	}
//}
//
//void AttackScene::KeyboardUp()
//{
//
//}
//
//void AttackScene::ReattachCamera()
//{
//	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//}
//
//void AttackScene::Defeated() //runs when the player destroys a Shadow
//{
//	auto& attackComponent = ECS::GetComponent<AttackMechanic>(MainEntities::MainPlayer());
//
//	if (attackComponent.GetShadow() == 1)
//	{
//		ECS::GetComponent<PhysicsBody>(enemy1).GetBody()->SetActive(false);
//		ECS::GetComponent<PhysicsBody>(enemy1Trigger).GetBody()->SetActive(false);
//		ECS::GetComponent<Sprite>(enemy1).SetTransparency(0.f);
//		ECS::GetComponent<Sprite>(enemy1Trigger).SetTransparency(0.f);
//	}
//	else if (attackComponent.GetShadow() == 2)
//	{
//		ECS::GetComponent<PhysicsBody>(enemy2).GetBody()->SetActive(false);
//		ECS::GetComponent<PhysicsBody>(enemy2Trigger).GetBody()->SetActive(false);
//		ECS::GetComponent<Sprite>(enemy2).SetTransparency(0.f);
//		ECS::GetComponent<Sprite>(enemy2Trigger).SetTransparency(0.f);
//	}
//	//add more as necessary
//
//}
//
//void AttackScene::CheckShield()
//{
//	//checks inputs from the ShieldMechanic and proceeds to turn the shield on or off
//	auto& playerHealth = ECS::GetComponent<Health>(player);
//	if (ECS::GetComponent<ShieldMechanic>(shield).shieldOn == true)
//	{
//		/*ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetActive(true);*/
//		//ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetAwake(true);
//		ECS::GetComponent<Sprite>(shield).SetTransparency(1.f);
//		//shieldActive = true; //currently useless
//		playerHealth.setShield(true); //Used by the BulletTrigger to check if the shield is on.
//	}
//	else if (ECS::GetComponent<ShieldMechanic>(shield).shieldOn == false)
//	{
//		/*ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetActive(false);*/
//		//ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetAwake(false);
//		ECS::GetComponent<Sprite>(shield).SetTransparency(0.f);
//		//shieldActive = false; //currently useless
//		playerHealth.setShield(false); //Used by the BulletTrigger to check if the shield is on.
//	}
//}
//
//void AttackScene::ChangeVisualState(int shadowEntity)
//{
//	auto& shadowState = ECS::GetComponent<ShadowLoop>(shadowEntity);
//	auto& shadowSprite = ECS::GetComponent<Sprite>(shadowEntity);
//	std::string restingSprite = "shadow2.png";
//	std::string chargingSprite = "shadow3.png";
//	std::string attackingSprite = "shadow4.png";
//	if (shadowState.s_resting == true)
//	{
//		shadowSprite.LoadSprite(restingSprite, 30, 30);
//	}
//	else if (shadowState.s_charging == true)
//	{
//		shadowSprite.LoadSprite(chargingSprite, 30, 30);
//	}
//	else if (shadowState.s_attacking == true)
//	{
//		shadowSprite.LoadSprite(attackingSprite, 30, 30);
//	}
//}
//
//void AttackScene::SpawnBullet(int shadowEntity)
//{
//	auto& shadowBody = ECS::GetComponent<PhysicsBody>(shadowEntity);
//	float tempX = shadowBody.GetBody()->GetPosition().x; //directly subbing in the GetBody line throws an error
//	float tempY = shadowBody.GetBody()->GetPosition().y;
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
//	//Set up components
//	std::string fileName = "bullet.png";
//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 5, 5);
//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(tempX, tempY, 4.f));
//	ECS::GetComponent<Trigger*>(entity) = new BulletTrigger();
//	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
//	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
//
//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
//
//	float shrinkX = 0.f;
//	float shrinkY = 0.f;
//	b2Body* tempBody;
//	b2BodyDef tempDef;
//	tempDef.type = b2_staticBody;
//	tempDef.position.Set(tempX, tempY);
//
//	tempBody = m_physicsWorld->CreateBody(&tempDef);
//
//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
//
//	tempPhsBody.SetGravityScale(0.f); //ensures no bullet drop and bullet reaches the player
//
//	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
//}
//
//void AttackScene::ShootBullet()
//{
//	auto& bulletBody = ECS::GetComponent<PhysicsBody>(bullet);
//	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
//	float deltaX = 0, deltaY = 0;
//	deltaX = player.GetBody()->GetPosition().x - bulletBody.GetBody()->GetPosition().x;
//	deltaY = player.GetBody()->GetPosition().y - bulletBody.GetBody()->GetPosition().y;
//	float n_deltaX = 0, n_deltaY = 0;
//	n_deltaX = deltaX / (deltaX * deltaX + deltaY * deltaY);
//	n_deltaY = deltaY / (deltaX * deltaX + deltaY * deltaY);
//	/*std::cout << deltaX << "," << deltaY << "\n";
//	std::cout << n_deltaX << "," << n_deltaY << "\n";
//	std::cout << "\n";*/
//	bulletBody.GetBody()->SetType(b2BodyType::b2_dynamicBody);
//	bulletBody.GetBody()->SetLinearVelocity(b2Vec2(deltaX * 100000000, deltaY * 100000000));
//}
//
//void AttackScene::ActivateShadow()
//{
//	//Checks to see if the appropriate amount of seconds of passed between now and the last shot. 
//	//If so, a bullet is fired from a shadow determined by the player's location.
//	auto& theTime = ECS::GetComponent<ShadowTime>(player);
//	auto& theLoc = ECS::GetComponent<ShadowSense>(player); 
//	if (theTime.fire == true)
//	{
//		if (theLoc.getLoc() == 1)
//		{
//			AttackScene::SpawnBullet(boss);
//			AttackScene::ShootBullet();
//		}
//		//add additional else if statements for additional shadows
//	}
//}
