#include "AngerLevel.h" 
#include "Utilities.h" 

#include <random> 

AngerLevel::AngerLevel(std::string name)
	: Scene(name)
{
	//No gravity this is a top down scene 
	m_gravity = b2Vec2(0.f, -98.f);
	m_physicsWorld->SetGravity(m_gravity);
	m_physicsWorld->SetContactListener(&listener);
}

void AngerLevel::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register 
	m_sceneReg = new entt::registry;

	//Attach the register 
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera 
	float aspectRatio = windowWidth / windowHeight;

	//Setup MainCamera Entity 
	SpawnMainCamera(windowWidth, windowHeight);

	//main player entity 
	SpawnMainPlayer();
	ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).SetPosition(b2Vec2(0.f, 80.f), true); //beginning
	//ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).SetPosition(b2Vec2(3216.f, 80.f), true); //boss platform

	//Set up shield
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shield = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<Kinematics>(entity);
		ECS::AttachComponent<ShieldMechanic>(entity);


		double playerSpriteX = ECS::GetComponent<Sprite>(MainEntities::MainPlayer()).GetWidth();
		double playerSpriteY = ECS::GetComponent<Sprite>(MainEntities::MainPlayer()).GetHeight();

		//Sets up components
		std::string fileName = "ShieldTemp.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, playerSpriteX, playerSpriteY);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 4.f));
		ECS::GetComponent<Kinematics>(entity).SetChild(entity);
		ECS::GetComponent<Kinematics>(entity).SetParent(MainEntities::MainPlayer());
		ECS::GetComponent<Kinematics>(entity).SetOffset(0.f, 0.f);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
	}

	//Platform Z //commented
	{
		////Creates entity
		//auto entity = ECS::CreateEntity();

		////Add components
		//ECS::AttachComponent<Sprite>(entity);
		//ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);

		////Sets up components
 
		//std::string fileName = "SamplePlatform.png";
		//ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 16);
 
		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//float shrinkX = 0.f;
		//float shrinkY = 0.f;
		//b2Body* tempBody;
		//b2BodyDef tempDef;
		//tempDef.type = b2_staticBody;
 
		//tempDef.position.Set(float32(3216.f), float32(40.f));
 

		//tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//	float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Boss wall
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		bossWall = entity;
 
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "SamplePlatform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 180, 16);
 
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
 
		tempDef.position.Set(float32(3790), float32(120)); //(3520,40)
 

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetRotationAngleDeg(90.f);
	}
	//Ending Door
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components 
		std::string fileName = "CaveExit.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 36);
 
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
 
		tempDef.position.Set(float32(3860.f), float32(96.f));
 

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}	
	
	//Shadow 7(Final Boss)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		boss = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);

		//Sets up components
		std::string fileName = "S1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 96, 96);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(3500.f), float32(250));//(3696.f,120.f)

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, ENEMY, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
	}
	//Final Boss Area Trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		//ECS::AttachComponent<ShadowLoop>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 480, 500);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(3510.f, 200.f, 5.f));
		ECS::GetComponent<Trigger*>(entity) = new BossAreaTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());
		ECS::GetComponent<Trigger*>(entity)->SetShadowZone(1);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(3520.f), float32(200.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Spike //commented
	{
		////Creates entity
		//auto entity = ECS::CreateEntity();

		////Add components
		//ECS::AttachComponent<Sprite>(entity);
		//ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);
		//ECS::AttachComponent<Trigger*>(entity);

		////Sets up components
		//std::string fileName = "Spike.png";
		//ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		//ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		//ECS::GetComponent<Trigger*>(entity) = new SpikeTrigger();
		//ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		//ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());

		//auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//float shrinkX = 0.f;
		//float shrinkY = 0.f;
		//b2Body* tempBody;
		//b2BodyDef tempDef;
		//tempDef.type = b2_staticBody;//change to dynamic
		//tempDef.position.Set(float32(1048.f), float32(24.f));

		//tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float((tempSpr.GetWidth() - shrinkY) / 2.f), vec2(0.f, 0.f), true, TRIGGER, PLAYER, 0.3f);
 
		//tempPhsBody.SetGravityScale(1.3f);
		//tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
	}

	
	//Boss Level Ground Platform(aka Platform ZA)
	int bossCoord = 3304;
	//Creating 10 crumbling platforms
	/*Commented*/for (int i = 0; i < 10; i++)
	{
		////Creates entity
		//auto entity = ECS::CreateEntity();
		//bigBossPlat[i] = entity;
		////Add components
		//ECS::AttachComponent<Sprite>(entity);
		//ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);
		//ECS::AttachComponent<CrumblingSequence>(entity);
		//ECS::AttachComponent<AnimationController>(entity);
		//
		////Sets up components 
		//std::string fileName = "spritesheets/crumblingPlatform.png";
		//std::string JSONFile = "crumble.json";

		//ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity), &ECS::GetComponent<AnimationController>(entity));
		//ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 32); 
		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//float shrinkX = 0.f;
		//float shrinkY = 0.f;
		//b2Body* tempBody;
		//b2BodyDef tempDef;
		//tempDef.type = b2_staticBody;

		//tempDef.position.Set(bossCoord,40);


		//tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//	float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		//bossCoord += 48;
	}
	bossCoord = 3304;
	//Creating 10 crumbling platfrom triggers
	/*Commented*/for (int i = 0; i < 10; i++)
	{
		////Creates entity
		//auto entity = ECS::CreateEntity();
		//bigBossPlatTrig[i] = entity;
		//auto& bossPlat = ECS::GetComponent<PhysicsBody>(bigBossPlat[i]);
		////Add components
		//ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);
		//ECS::AttachComponent<Trigger*>(entity);

		////Sets up components
		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		//ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		//ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		//ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(bigBossPlat[i]);


		//auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//float shrinkX = 0.f;
		//float shrinkY = 0.f;
		//b2Body* tempBody;
		//b2BodyDef tempDef;
		//tempDef.type = b2_staticBody;

		////tempDef.position.Set(bossPlat.GetBody()->GetPosition().x, bossPlat.GetBody()->GetPosition().y);

		//tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float(48),
		//	float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		//tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		//bossCoord += 48;
	}

	//old boss crumbling platform code
	{
		////Boss Platform 1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();
		//	bossPlatforms[0] = entity;
		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);
		//	ECS::AttachComponent<CrumblingSequence>(entity);
		//	ECS::AttachComponent<AnimationController>(entity);

		//	//Sets up components
		//	std::string fileName = "spritesheets/crumblingPlatform.png";
		//	std::string JSONFile = "crumble.json";

		//	ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity), &ECS::GetComponent<AnimationController>(entity));
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 32);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(3300), float32(150));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		//}
		////Boss Platform 1 Trigger
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();
		//	bossPlatformTriggers[0] = entity;
		//	auto& bossPlat = ECS::GetComponent<PhysicsBody>(bossPlatforms[0]);
		//	//Add components
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);
		//	ECS::AttachComponent<Trigger*>(entity);

		//	//Sets up components
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		//	ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		//	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		//	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(bossPlatforms[0]);


		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;

		//	//tempDef.position.Set(bossPlat.GetBody()->GetPosition().x, bossPlat.GetBody()->GetPosition().y);
		//	tempDef.position.Set(3300, 150);

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(48),
		//		float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Boss Platform 2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();
		//	bossPlatforms[1] = entity;
		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);
		//	ECS::AttachComponent<CrumblingSequence>(entity);
		//	ECS::AttachComponent<AnimationController>(entity);

		//	//Sets up components
		//	std::string fileName = "spritesheets/crumblingPlatform.png";
		//	std::string JSONFile = "crumble.json";

		//	ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity), &ECS::GetComponent<AnimationController>(entity));
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 32);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(3380), float32(110));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		//}
		////Boss Platform 2 Trigger
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();
		//	bossPlatformTriggers[1] = entity;
		//	auto& bossPlat = ECS::GetComponent<PhysicsBody>(bossPlatforms[1]);
		//	//Add components
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);
		//	ECS::AttachComponent<Trigger*>(entity);

		//	//Sets up components
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		//	ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		//	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		//	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(bossPlatforms[1]);


		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;

		//	tempDef.position.Set(bossPlat.GetBody()->GetPosition().x, bossPlat.GetBody()->GetPosition().y);

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(48),
		//		float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Boss Platform 3
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();
		//	bossPlatforms[2] = entity;
		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);
		//	ECS::AttachComponent<CrumblingSequence>(entity);
		//	ECS::AttachComponent<AnimationController>(entity);

		//	//Sets up components
		//	std::string fileName = "spritesheets/crumblingPlatform.png";
		//	std::string JSONFile = "crumble.json";

		//	ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity), &ECS::GetComponent<AnimationController>(entity));
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 32);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(3480), float32(74));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		//}
		////Boss Platform 3 Trigger
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();
		//	bossPlatformTriggers[2] = entity;
		//	auto& bossPlat = ECS::GetComponent<PhysicsBody>(bossPlatforms[2]);
		//	//Add components
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);
		//	ECS::AttachComponent<Trigger*>(entity);

		//	//Sets up components
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		//	ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		//	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		//	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(bossPlatforms[2]);


		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;

		//	tempDef.position.Set(bossPlat.GetBody()->GetPosition().x, bossPlat.GetBody()->GetPosition().y);

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(48),
		//		float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Boss Platform 4
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();
		//	bossPlatforms[3] = entity;
		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);
		//	ECS::AttachComponent<CrumblingSequence>(entity);
		//	ECS::AttachComponent<AnimationController>(entity);

		//	//Sets up components
		//	std::string fileName = "spritesheets/crumblingPlatform.png";
		//	std::string JSONFile = "crumble.json";

		//	ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity), &ECS::GetComponent<AnimationController>(entity));
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 32);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(3580), float32(110));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		//}
		////Boss Platform 4 Trigger
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();
		//	bossPlatformTriggers[3] = entity;
		//	auto& bossPlat = ECS::GetComponent<PhysicsBody>(bossPlatforms[3]);
		//	//Add components
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);
		//	ECS::AttachComponent<Trigger*>(entity);

		//	//Sets up components
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		//	ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		//	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		//	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(bossPlatforms[3]);


		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;

		//	tempDef.position.Set(bossPlat.GetBody()->GetPosition().x, bossPlat.GetBody()->GetPosition().y);

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(48),
		//		float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Boss Platform 5
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();
		//	bossPlatforms[4] = entity;
		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);
		//	ECS::AttachComponent<CrumblingSequence>(entity);
		//	ECS::AttachComponent<AnimationController>(entity);

		//	//Sets up components
		//	std::string fileName = "spritesheets/crumblingPlatform.png";
		//	std::string JSONFile = "crumble.json";

		//	ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity), &ECS::GetComponent<AnimationController>(entity));
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 32);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(3680), float32(144));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		//}
		////Boss Platform 5 Trigger
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();
		//	bossPlatformTriggers[4] = entity;
		//	auto& bossPlat = ECS::GetComponent<PhysicsBody>(bossPlatforms[4]);
		//	//Add components
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);
		//	ECS::AttachComponent<Trigger*>(entity);

		//	//Sets up components
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		//	ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		//	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		//	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(bossPlatforms[4]);


		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;

		//	tempDef.position.Set(bossPlat.GetBody()->GetPosition().x, bossPlat.GetBody()->GetPosition().y);

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(48),
		//		float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
	}
	{}
	//setup orb 1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "shadowOrb.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(160.f, 30.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(3300.f, 150.f + 30.f);

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//setup orb 2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "shadowOrb.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(160.f, 30.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(3380.f, 110.f + 30.f);

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//setup orb 3
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "shadowOrb.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(160.f, 30.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		
		tempDef.position.Set(3480.f, 74.f + 30.f);

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		//ECS::GetComponent<PhysicsBody>(entity).SetPosition(b2Vec2(bossPlat.GetPosition().x, bossPlat.GetPosition().y));
	}
	//setup orb 4
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "shadowOrb.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(160.f, 30.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(3580.f, 110.f + 30);

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//setup orb 5
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "shadowOrb.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(160.f, 30.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(3680.f, 144.f + 30.f);

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Set up respawn trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "testCube.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 4000, 20);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1900.f, -40.f, 0.f));
		ECS::GetComponent<Trigger*>(entity) = new RespawnTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1900.f),float32(-10.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Set up breakable wall
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		breakableWalls[0] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "maxHealth.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 30);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(80.f, 20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(80), float32(33));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Set up breakable wall trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		breakableWallTriggers[0] = entity;
		auto& breakableWall = ECS::GetComponent<PhysicsBody>(breakableWalls[0]);
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "testCube.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 30);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(50.f, 33.f, 3.f));
		ECS::GetComponent<Trigger*>(entity) = new BreakableWallTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(80, 33);

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Old Tile Code
	{
		//// STATIC BACKGROUND TILES \\
		
		//// TILE 0-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger0-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((-16 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 1-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger1-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3((0.f + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 2-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger2-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((16 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 3-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger3-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((32 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 4-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger4-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((48 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 5-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger5-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((64 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 6-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger6-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((80 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 7-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger7-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((96 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 8-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger8-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((112 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 9-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger9-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((128 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 10-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger10-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((144 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 11-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger11-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((160 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 12-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger12-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((176 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 13-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger13-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((192 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 14-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger14-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((208 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 15-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger15-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((224 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 16-1
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger16-1.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((240 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
		//}

		//// TILE 0-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger0-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((-16 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		////TILE 1-2?
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger1-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3((0.f + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 2-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger2-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((16 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 3-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger3-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((32 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 4-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger4-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((48 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 5-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger5-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((64 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 6-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger6-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((80 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 7-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger7-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((96 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 8-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger8-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((112 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 9-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger9-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((128 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 10-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger10-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((144 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 11-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger11-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((160 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 12-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger12-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((176 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 13-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger13-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((192 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 14-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger14-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((208 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 15-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger15-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((224 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}

		//// TILE 16-2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);

		//	//Sets up components
		//	std::string fileName = "backgrounds/anger/anger16-2.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(((240 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
		//}
	}

	{}
	// WATER //commented
	{
		for (int i = 0; i < 18; i++)
		{
			////Creates entity
			//auto entity = ECS::CreateEntity();

			////Add components
			//ECS::AttachComponent<Sprite>(entity);
			//ECS::AttachComponent<Transform>(entity);

			////Sets up components
			//std::string fileName = "backgrounds/anger/water.png";
			//ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
			//ECS::GetComponent<Transform>(entity).SetPosition(vec3((((-16 + 16*i) * 16.f) + (16 * 7)), ((-16 * 16.f) + (16 * 5)), 1.f));
		}
	}

	SpawnUI();
	SpawnPlatforms();
	SpawnCrumblingPlatforms();
	SpawnTiles();
	SpawnMovingPlatforms();
	SpawnShadows();
	SpawnSpikes();
	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void AngerLevel::SpawnPlatforms()
{
	//SpawnPlatform(float xPos, float yPos, float width, float height, std::string sprite, float transparency)
	SpawnPlatform(96.f, 8.f, 192.f, 16.f, "SamplePlatform.png", 1.f); //Platform A
	SpawnPlatform(336.f, 40.f, 224.f, 16.f, "SamplePlatform.png", 1.f); //Platform B
	SpawnPlatform(608.f, 8.f, 256.f, 16.f, "SamplePlatform.png", 1.f); //Platform C
	SpawnPlatform(840.f, 65.f, 240.f, 16.f, "SamplePlatform.png", 1.f); //Platform D
	SpawnPlatform(700.8f, 24.f, 48.f, 16.f, "SamplePlatform.png",1.f, 90.f); //Platform D_BridgeHelp_
	SpawnPlatform(732.f, 20.f, 8.f, 8.f, "SamplePlatform.png", 1.f);//Platform D_BridgeHelp_2
	SpawnPlatform(1056.f, 8.f, 224.f, 16.f, "SamplePlatform.png", 1.f);//Platform E
	SpawnPlatform(1296.f, 40.f, 196.f, 16.f, "SamplePlatform.png", 1.f);//Platform F
	SpawnPlatform(1616.f, 8.f, 384.f, 16.f, "SamplePlatform.png", 1.f);//Platform M
	SpawnPlatform(1888.f, 40.f, 64.f, 16.f, "SamplePlatform.png", 1.f);//Platform N
	SpawnPlatform(2064.f, 72.f, 192.f, 16.f, "SamplePlatform.png", 1.f);//Platform O
	SpawnPlatform(2224.f, 24.f, 64.f, 16.f, "SamplePlatform.png", 1.f);//Platform P
	SpawnPlatform(2336.f, 59.2f, 64.f, 16.f, "SamplePlatform.png", 1.f);//Platform Q
	SpawnPlatform(2448.f, 92.8f, 64.f, 16.f, "SamplePlatform.png", 1.f);//Platform R
	SpawnPlatform(2544.f, 131.2f, 64.f, 16.f, "SamplePlatform.png", 1.f);//Platform S
	SpawnPlatform(2528.f, 51.2f, 64.f, 16.f, "SamplePlatform.png", 1.f);//Platform T
	SpawnPlatform(3216.f, 40.f, 32.f, 16.f, "SamplePlatform.png", 1.f);//Platform Z
	SpawnPlatform(3848.f, 72.f, 80.f, 16.f, "SamplePlatform.png", 1.f);//Platform ZB
}

void AngerLevel::SpawnCrumblingPlatforms()
{
	//int Scene::SpawnCrumblingPlatform(float xPos, float yPos, float width, float height)
	masterCrumblingPlatforms[0] = SpawnCrumblingPlatform(2640.f, 72.f, 48.f, 32.f); // Crumbling Platform U
	masterCrumblingPlatforms[1] = SpawnCrumblingPlatform(2736.f, 60.f, 48.f, 32.f); // Crumbling Platform V
	masterCrumblingPlatforms[2] = SpawnCrumblingPlatform(2864.f, 88.f, 48.f, 32.f); // Crumbling Platform W
	masterCrumblingPlatforms[3] = SpawnCrumblingPlatform(2960.f, 40.f, 48.f, 32.f); // Crumbling Platform X

	masterCrumblingPlatforms[4] = SpawnCrumblingPlatform(3300.f, 150.f, 48.f, 32.f); // Boss Platform 1
	masterCrumblingPlatforms[5] = SpawnCrumblingPlatform(3380.f, 110.f, 48.f, 32.f); // Boss Platform 2
	masterCrumblingPlatforms[6] = SpawnCrumblingPlatform(3480.f, 74.f, 48.f, 32.f); // Boss Platform 3
	masterCrumblingPlatforms[7] = SpawnCrumblingPlatform(3580.f, 110.f, 48.f, 32.f); // Boss Platform 4
	masterCrumblingPlatforms[8] = SpawnCrumblingPlatform(3680.f, 144.f, 48.f, 32.f); // Boss Platform 5

	float bossCoord = 3304.f;
	for (int i = 9; i < 19; i++) //creates the ground floor of the boss battle
	{
		masterCrumblingPlatforms[i] = SpawnCrumblingPlatform(bossCoord, 40.f, 48.f, 32.f); 
		bossCoord += 48;

	}
}

void AngerLevel::SpawnTiles()
{
	//void Scene::SpawnTile(float xPos, float yPos, std::string sprite, float width, float height)
	SpawnTile(-144.f, 80.f, "backgrounds/anger/anger0-1.png");// TILE 0-1
	SpawnTile(112.f, 80.f, "backgrounds/anger/anger1-1.png");// TILE 1-1
	SpawnTile(368.f, 80.f, "backgrounds/anger/anger2-1.png");// TILE 2-1
	SpawnTile(624.f, 80.f, "backgrounds/anger/anger3-1.png");// TILE 3-1 ???
	SpawnTile(880.f, 80.f, "backgrounds/anger/anger4-1.png");// TILE 4-1
	SpawnTile(1136.f, 80.f, "backgrounds/anger/anger5-1.png");// TILE 5-1
	SpawnTile(1392.f, 80.f, "backgrounds/anger/anger6-1.png");// TILE 6-1
	SpawnTile(1648.f, 80.f, "backgrounds/anger/anger7-1.png");// TILE 7-1
	SpawnTile(1904.f, 80.f, "backgrounds/anger/anger8-1.png");// TILE 8-1
	SpawnTile(2160.f, 80.f, "backgrounds/anger/anger9-1.png");// TILE 9-1
	SpawnTile(2416.f, 80.f, "backgrounds/anger/anger10-1.png");// TILE 10-1
	SpawnTile(2672.f, 80.f, "backgrounds/anger/anger11-1.png");// TILE 11-1
	SpawnTile(2928.f, 80.f, "backgrounds/anger/anger12-1.png");// TILE 12-1
	SpawnTile(3184.f, 80.f, "backgrounds/anger/anger13-1.png");// TILE 13-1
	SpawnTile(3440.f, 80.f, "backgrounds/anger/anger14-1.png");// TILE 14-1
	SpawnTile(3696.f, 80.f, "backgrounds/anger/anger15-1.png");// TILE 15-1
	SpawnTile(3952.f, 80.f, "backgrounds/anger/anger16-1.png");// TILE 16-1

	SpawnTile(-144.f, 336.f, "backgrounds/anger/anger0-2.png");// TILE 0-2
	SpawnTile(112.f, 336.f, "backgrounds/anger/anger1-2.png");// TILE 1-2
	SpawnTile(368.f, 336.f, "backgrounds/anger/anger2-2.png");// TILE 2-2
	SpawnTile(624.f, 336.f, "backgrounds/anger/anger3-2.png");// TILE 3-2
	SpawnTile(880.f, 336.f, "backgrounds/anger/anger4-2.png");// TILE 4-2
	SpawnTile(1136.f, 336.f, "backgrounds/anger/anger5-2.png");// TILE 5-2
	SpawnTile(1392.f, 336.f, "backgrounds/anger/anger6-2.png");// TILE 6-2
	SpawnTile(1648.f, 336.f, "backgrounds/anger/anger7-2.png");// TILE 7-2
	SpawnTile(1904.f, 336.f, "backgrounds/anger/anger8-2.png");// TILE 8-2
	SpawnTile(2160.f, 336.f, "backgrounds/anger/anger9-2.png");// TILE 9-2
	SpawnTile(2416.f, 336.f, "backgrounds/anger/anger10-2.png");// TILE 10-2
	SpawnTile(2672.f, 336.f, "backgrounds/anger/anger11-2.png");// TILE 11-2
	SpawnTile(2928.f, 336.f, "backgrounds/anger/anger12-2.png");// TILE 12-2
	SpawnTile(3184.f, 336.f, "backgrounds/anger/anger13-2.png");// TILE 13-2
	SpawnTile(3440.f, 336.f, "backgrounds/anger/anger14-2.png");// TILE 14-2
	SpawnTile(3696.f, 336.f, "backgrounds/anger/anger15-2.png");// TILE 15-2
	SpawnTile(3952.f, 336.f, "backgrounds/anger/anger16-2.png");// TILE 16-2

	//water
	for (int i = 0; i < 18; i++)
	{
		SpawnTile(((-16 + 16 * i) * 16.f) + 112, -176.f, "backgrounds/anger/water.png");// TILE 16-2
	}


}

void AngerLevel::SpawnUI()
{
	uiElements[0] = Scene::SpawnUIElement(-110.f, 65.f, 20, 20, "heart.png");
	uiElements[1] = Scene::SpawnUIElement(-90.f, 65.f, 20, 20, "heart.png");
	uiElements[2] = Scene::SpawnUIElement(-70.f, 65.f, 20, 20, "heart.png");
	uiElements[3] = Scene::SpawnUIElement(80.f, -60.f, 30, 30, "shieldOff.png");
	uiElements[4] = Scene::SpawnUIElement(110.f, -60.f, 30, 30, "punchOff.png");
	uiElements[5] = Scene::SpawnUIElement(10.f, 30.f, 40, 20, "ouch.png");
	for (int i = 0; i < 3; i++)
	{
		hearts[i] = uiElements[i];
	}
	shieldUI = uiElements[3];
	attackUI = uiElements[4];
	ouchUI = uiElements[5];
}

void AngerLevel::SpawnShadows()
{
	//SpawnShadow(float xPos, float yPos, float min, float max, bool ranged, b2Vec2 patrolVel, float xOffset, float yOffset, float width, float height)

	//array for holding shadow b2Vec2s before they can be unpacked
	b2Vec2 newShadows[6];

	//spawning shadows with their associated triggers
	newShadows[0] = SpawnShadow(337.5f, 70.f, 226.f, 449.f, false, b2Vec2(30.f, 0.f),0.f,0.f);
	newShadows[1] = SpawnShadow(656.f, 30.f, 501.f, 664.f, false, b2Vec2(30.f, 0.f), 0.f, 0.f);
	newShadows[2] = SpawnShadow(1344.f, 77.f, 1220.f, 1368.f, false, b2Vec2(30.f, 0.f), 0.f, 0.f); //1220, 1368
	newShadows[3] = SpawnShadow(2096.f, 112.f, 1991.f, 2149.f, false, b2Vec2(30.f, 0.f), 0.f, 0.f); //1991, 2149
	newShadows[4] = SpawnShadow(1613.f, 40.f, 1438.f, 1789.f, false, b2Vec2(30.f, 0.f), 0.f, 0.f); //1438, 1789
	newShadows[5] = SpawnShadow(1070.f, 40.f, 960.f, 1147.f, false, b2Vec2(30.f, 0.f), 0.f, 0.f); //960, 1147

	//separating all the entities from their triggers and placing them in their respective arrays
	for (int i = 0; i < 6; i++)
	{
		Separate(newShadows[i], 0);
	}

	

	/*bulletWalls[0] = SpawnBulletWall(-260.f, 80.f);
	bulletWalls[1] = SpawnBulletWall(512.f, 87.f);
	bulletWalls[2] = SpawnBulletWall(1286.f, 650.f);
	bulletWalls[3] = SpawnBulletWall(950.f, 650.f);*/
}

void AngerLevel::SpawnMovingPlatforms()
{
	
	//b2Vec2 Scene::SpawnMovingPlatform(float xPos, float yPos, float min, float max, int type, float width, float height)

	b2Vec2 movingPlatforms[1];

	movingPlatforms[0] = SpawnMovingPlatform(3056.f, 80.f, 3030.f, 3170.f, 0, 80.f, 8.f, "samplePlatform.png");

	for (int i = 0; i < 1; i++)
	{
		Separate(movingPlatforms[i], 1);
	}
}

void AngerLevel::SpawnSpikes()
{
	//tempDef.position.Set(float32(1048.f), float32(24.f));
	SpawnSpike(1048.f, 24.f);
	int spikeXLoc = 818;
	for (int i = 0; i < 4; i++)
	{
		SpawnSpike(spikeXLoc, 80.f);
		spikeXLoc += 16;
	}
}

void AngerLevel::Update()
{
	auto& player = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& playerSprite = ECS::GetComponent<Sprite>(MainEntities::MainPlayer());
	auto& thePlayer = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& playerShield = ECS::GetComponent<Kinematics>(shield);
	auto& shieldThing = ECS::GetComponent<ShieldMechanic>(shield);
	auto& theCoolDown = ECS::GetComponent<CoolDown>(MainEntities::MainPlayer());
	auto& angerBoss = ECS::GetComponent<BossLevel>(MainEntities::MainPlayer());
	auto& bossSprite = ECS::GetComponent<Sprite>(boss);
	auto& bossBody = ECS::GetComponent<PhysicsBody>(boss);
	//auto& kinTrig = ECS::GetComponent<Kinematics>(kinTrigger);
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	
	if (playerMech.GetCanMove() == true)
	{
		player.Update();
	}

	for (int i = 0; i < 1; i++)
	{
		ECS::GetComponent<Kinematics>(movingTriggers[i]).UpdatePosition();
		ECS::GetComponent<MovingPlatform>(movingPlatforms[i]).MovePlatform(movingPlatforms[i]);
	}
	
	//kinTrig.UpdatePosition();
	playerMech.RunKnockBackTime();
	playerShield.UpdateTransform();
	AngerLevel::CheckShield();
	shieldThing.activateShield();
	AngerLevel::ReattachCamera();
	if (playerMech.GetCanMove() == true)
	{
		thePlayer.Update();
	}
	playerMech.Attacking();

	for (int i = 0; i < 6; i++) //shadows
	{
		if (ECS::GetComponent<ShadowLoop>(shadows[i]).isShadowAlive == false)
		{
			ECS::GetComponent<PhysicsBody>(shadows[i]).GetBody()->SetActive(false);
			ECS::GetComponent<Sprite>(shadows[i]).SetTransparency(0.f);
		}
	}

	theCoolDown.GlobalCoolDown();
	angerBoss.CheckBossStatus();
	playerMech.RunShadowTime();
	if (angerBoss.GetBossDefeated() == false)
	{
		AngerLevel::ActivateShadow();
	}
	else
	{
		bossSprite.SetTransparency(0.f);
		bossBody.GetBody()->SetActive(false);
	}


	//AngerLevel::MovePlatform();
	AngerLevel::PlayerDeath();

	//win condition(kill boss to open platform)
	if (angerBoss.GetBossDefeated() == true)
	{
		if (bossWallDestroyed == false)
		{
			PhysicsBody::m_bodiesToDelete.push_back(bossWall);
			bossWallDestroyed = true;
		}
	}

	for (int i = 0; i < 18; i++) //for platforms u,v,w,x,b1,b2,b3,b4,b5, and the 10 crumbling platforms that make up the ground of the boss level
	{
		ECS::GetComponent<CrumblingSequence>(masterCrumblingPlatforms[i]).Crumble(masterCrumblingPlatforms[i]);
		CrumblingPlatforms(masterCrumblingPlatforms[i]);
	}

	playerMech.CheckWallStatus(breakableWalls[0],breakableWallTriggers[0]);
	
	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).Update();
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).Update();
	for (int i = 0; i < 6; i++)
	{
		ECS::GetComponent<Kinematics>(uiElements[i]).UpdateUI();
	}
	AngerLevel::UpdateUI(); 

	for (int i = 0; i < 6; i++) //shadow contact/pause
	{
		ECS::GetComponent<ShadowLoop>(shadows[i]).ShadowRoutine(shadows[i]);
		ECS::GetComponent<Kinematics>(sZones[i]).UpdatePosition();
		ECS::GetComponent<ShadowLoop>(shadows[i]).ShadowPause(shadows[i]);
	}
}

void AngerLevel::KeyboardHold()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	float speed = 3.f;
	b2Vec2 vel = b2Vec2(0.f, 0.f);
	vec3 velocity = vec3(0.f, 0.f, 0.f);
}

void AngerLevel::KeyboardUp()
{
}

void AngerLevel::KeyboardDown()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	//auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());
 
 
	//auto& attackComponent = ECS::GetComponent<AttackMechanic>(MainEntities::MainPlayer());
	auto& shieldSprite = ECS::GetComponent<Sprite>(shield);
	auto& shieldMech = ECS::GetComponent<ShieldMechanic>(shield);
	auto& theCoolDown = ECS::GetComponent<CoolDown>(MainEntities::MainPlayer());
	auto& angerBoss = ECS::GetComponent<BossLevel>(MainEntities::MainPlayer());
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());

 
	float speed = 1.f;
	b2Vec2 vel = b2Vec2(0.f, 0.f);

	playerVel = player.GetVelocity();
	playerPos = player.GetPosition();

 
	
		if (Input::GetKeyDown(Key::Q) && shieldMech.restart == true && theCoolDown.isCoolDownActive == false) //checks to see if the shield cooldown if complete before reactivating shield
		{
			shieldMech.setSequenceStart(true);
			theCoolDown.SetSequenceStart(true);
		}

		if (Input::GetKeyDown(Key::E) && playerMech.GetAttackSequence() == false && theCoolDown.isCoolDownActive == false)
		{
			playerMech.SetAttackSequence(true);
			theCoolDown.SetSequenceStart(true);
		}
	
	

 
	if (Input::GetKeyDown(Key::M)) {
		std::cout << "X Pos: " << playerPos.x << std::endl;
		std::cout << "Y Pos: " << playerPos.y << std::endl << std::endl;
	}
	if (Input::GetKeyDown(Key::T))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}
 
}

void AngerLevel::ReattachCamera()
{
	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void AngerLevel::CheckShield()
{
	//checks inputs from the ShieldMechanic and proceeds to turn the shield on or off
	//auto& playerHealth = ECS::GetComponent<Health>(player);
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	if (ECS::GetComponent<ShieldMechanic>(shield).shieldOn == true)
	{
		/*ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetActive(true);*/
		//ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetAwake(true);
		ECS::GetComponent<Sprite>(shield).SetTransparency(1.f);
		//shieldActive = true; //currently useless
		playerMech.SetShield(true); //Used by the BulletTrigger to check if the shield is on.
	}
	else if (ECS::GetComponent<ShieldMechanic>(shield).shieldOn == false)
	{
		/*ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetActive(false);*/
		//ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetAwake(false);
		ECS::GetComponent<Sprite>(shield).SetTransparency(0.f);
		//shieldActive = false; //currently useless
		playerMech.SetShield(false); //Used by the BulletTrigger to check if the shield is on.
	}
}

void AngerLevel::ChangeVisualState(int shadowEntity)
{
	auto& shadowState = ECS::GetComponent<ShadowLoop>(shadowEntity);
	auto& shadowSprite = ECS::GetComponent<Sprite>(shadowEntity);
	std::string restingSprite = "shadow2.png";
	std::string chargingSprite = "shadow3.png";
	std::string attackingSprite = "shadow4.png";
	/*if (shadowState.s_resting == true)
	{
		shadowSprite.LoadSprite(restingSprite, 30, 30);
	}
	else if (shadowState.s_charging == true)
	{
		shadowSprite.LoadSprite(chargingSprite, 30, 30);
	}
	else if (shadowState.s_attacking == true)
	{
		shadowSprite.LoadSprite(attackingSprite, 30, 30);
	}*/
}

void AngerLevel::SpawnBullet(int shadowEntity)
{
	auto& shadowBody = ECS::GetComponent<PhysicsBody>(shadowEntity);
	float tempX = shadowBody.GetBody()->GetPosition().x; //directly subbing in the GetBody line throws an error
	float tempY = shadowBody.GetBody()->GetPosition().y;
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
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(tempX, tempY, 4.f));
	ECS::GetComponent<Trigger*>(entity) = new BulletTrigger();
	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_staticBody;
	tempDef.position.Set(tempX, tempY);

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	tempPhsBody.SetGravityScale(0.f); //ensures no bullet drop and bullet reaches the player

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void AngerLevel::ShootBullet()
{
	auto& bulletBody = ECS::GetComponent<PhysicsBody>(bullet);
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	float deltaX = 0, deltaY = 0;
	deltaX = player.GetBody()->GetPosition().x - bulletBody.GetBody()->GetPosition().x;
	deltaY = player.GetBody()->GetPosition().y - bulletBody.GetBody()->GetPosition().y;
	float n_deltaX = 0, n_deltaY = 0;
	n_deltaX = deltaX / (deltaX * deltaX + deltaY * deltaY);
	n_deltaY = deltaY / (deltaX * deltaX + deltaY * deltaY);
	bulletBody.GetBody()->SetType(b2BodyType::b2_dynamicBody);

	b2Vec2 angle = CalculateAngle(MainEntities::MainPlayer(), bullet);
	float dirAngle = atan(angle.x / angle.y) * (180 / PI);
	ECS::GetComponent<PhysicsBody>(bullet).SetRotationAngleDeg(dirAngle * -1);

	bulletBody.GetBody()->SetLinearVelocity(b2Vec2(deltaX * 100000000, deltaY * 100000000));


}

void AngerLevel::ActivateShadow()
{
	//Checks to see if the appropriate amount of seconds of passed between now and the last shot. 
	//If so, a bullet is fired from a shadow determined by the player's location.
	/*auto& theTime = ECS::GetComponent<ShadowTime>(player);
	auto& theLoc = ECS::GetComponent<ShadowSense>(player);*/
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	if (playerMech.GetFiring() == true)
	{
		if (playerMech.GetShadowLoc() == 1)
		{
			AngerLevel::SpawnBullet(boss);
			AngerLevel::ShootBullet();
		}
	}

	
}

void AngerLevel::Separate(b2Vec2(newPair), int type)
{
	if (type == 0)
	{
		int static shadowID = 0;
		shadows[shadowID] = newPair.x;
		sZones[shadowID] = newPair.y;
		shadowID++;
	}
	else
	{
		int static movingID = 0;
		movingPlatforms[movingID] = newPair.x;
		movingTriggers[movingID] = newPair.y;
		movingID++;
	}
}

void AngerLevel::MoveShadow(int shadow)
{
	//for moving shadows
	/*auto& shade = ECS::GetComponent<ShadowLoop>(shadow);

	shade.ShadowRoutine(shadow);*/
}

void AngerLevel::MovePlatform()
{
	//auto& moveTrig = ECS::GetComponent<MovingClass>(MainEntities::MainPlayer());
	//auto& playerBody = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	//auto& plat = ECS::GetComponent<PhysicsBody>(movingPlat);
	////auto& vert = ECS::GetComponent<PhysicsBody>(vertMovingPlat);
	//float platX = plat.GetPosition().x;
	//float platY = plat.GetPosition().y;
	//int playerX = playerBody.GetPosition().x;
	//int playerY = playerBody.GetPosition().y;

	//static bool vertSwitch = false;

	//if (platX > 3170)
	//{
	//	switchDir = true;

	//}
	//if (platX < 3030)
	//{
	//	switchDir = false;

	//}
	//if (switchDir == false)
	//{
	//	platX += 0.5;
	//	//plat.SetPosition(b2Vec2(platX, platY));
	//	plat.SetVelocity(vec3(30.f, 0.f, 0.f));
	//	moveTrig.SetRight(true);
	//	moveTrig.SetLeft(false);

	//	//plat.SetVelocity(vec3(1250 * Timer::deltaTime, 0, 0));
	//	//if (moveTrig.GetMoving() == true)
	//	//{
	//	//	playerX += 1;
	//	//	if (!Input::GetKey(Key::A))
	//	//	{
	//	//		playerBody.SetVelocity(vec3(5000, 0, 0));
	//	//	}
	//	//	//playerBody.SetPosition(b2Vec2(playerX, playerY));
	//	//}
	//}
	//else if (switchDir == true)
	//{
	//	platX -= 0.5;
	//	//plat.SetPosition(b2Vec2(platX, platY));
	//	plat.SetVelocity(vec3(-30.f, 0.f, 0.f));
	//	moveTrig.SetLeft(true);
	//	moveTrig.SetRight(false);
	//}
}

void AngerLevel::PlayerDeath()
{
	//auto& playerHealth = ECS::GetComponent<Health>(player);
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	auto& playerBody = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	if (playerMech.GetRespawn() == true) //if palyer falls off map
	{
		playerBody.SetPosition(b2Vec2(50, 50));
		playerMech.SetHealth(3);
		playerMech.SetRespawn(false);
		for (int i = 0; i < 3; i++)
		{
			ECS::GetComponent<Sprite>(hearts[i]).SetTransparency(1.f);
		}
	}
	else if (playerMech.GetHealth() <= 0) //if player dies from shadow attack
	{
		playerBody.SetPosition(b2Vec2(50, 50));
		playerMech.SetHealth(3);
		for (int i = 0; i < 3; i++)
		{
			ECS::GetComponent<Sprite>(hearts[i]).SetTransparency(1.f);
		}
	}
}

void AngerLevel::MouseClick(SDL_MouseButtonEvent evnt)
{
	/*auto& playerBody = ECS::GetComponent<PhysicsBody>(player);
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		std::cout << "(" << evnt.x << "," << evnt.y << ")\n";
	}*/
}

void AngerLevel::UpdatePositionWithCamera(int cameraEntity, int spriteEntity, int tempOffsetX, int tempOffsetY)
{
	auto& cameraBody = ECS::GetComponent<Camera>(cameraEntity);
	auto& spriteBody = ECS::GetComponent<Transform>(spriteEntity);
	int offsetX = tempOffsetX;
	int offsetY = tempOffsetY;

	spriteBody.SetPosition(vec3(cameraBody.GetPosition().x + offsetX, cameraBody.GetPosition().y + offsetY, 4));
}
void AngerLevel::UpdateUI()
{
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	auto& shieldMech = ECS::GetComponent<ShieldMechanic>(shield);
	auto& gameCoolDown = ECS::GetComponent<CoolDown>(MainEntities::MainPlayer());
	if (shieldMech.shieldOn == true)
	{
		ECS::GetComponent<Sprite>(shieldUI).LoadSprite(shieldOn,30, 30); 
		ECS::GetComponent<Sprite>(shieldUI).SetTransparency(1.f);
	}
	else if (shieldMech.shieldOn == false && shieldMech.restart==false)
	{
		ECS::GetComponent<Sprite>(shieldUI).SetTransparency(0.f);
	}
	else if (shieldMech.shieldOn == false && shieldMech.restart == true)
	{
		ECS::GetComponent<Sprite>(shieldUI).LoadSprite(shieldOff, 30, 30);
		ECS::GetComponent<Sprite>(shieldUI).SetTransparency(1.f);
	}

	if (playerMech.GetAttackSequence() == false) //ability is available
	{ 
		ECS::GetComponent<Sprite>(attackUI).LoadSprite(punchOff, 30, 30);
		ECS::GetComponent<Sprite>(attackUI).SetTransparency(1.f);
	}
	else if (playerMech.GetAttackSequence() == true) 
	{
		if (playerMech.GetAttacking() == true && playerMech.GetAttackCoolDown() == true)
		{
			ECS::GetComponent<Sprite>(attackUI).LoadSprite(punchOn, 30, 30);
		}
		else if (playerMech.GetAttacking() == false && playerMech.GetAttackCoolDown() == true)
		{
			ECS::GetComponent<Sprite>(attackUI).SetTransparency(0.f);
		}		
	}
	else if (playerMech.GetAttacking() == false && playerMech.GetAttackCoolDown() == true) //ability has been used and now the ability's cooldown is active
	{
		ECS::GetComponent<Sprite>(attackUI).SetTransparency(0.f);
	}

	if (playerMech.GetHealth() == 2) { ECS::GetComponent<Sprite>(hearts[2]).SetTransparency(0.f); }
	else if (playerMech.GetHealth() == 1) { ECS::GetComponent<Sprite>(hearts[1]).SetTransparency(0.f); }
	else if (playerMech.GetHealth() == 0) { ECS::GetComponent<Sprite>(hearts[0]).SetTransparency(0.f); }
	if (playerMech.GetCanMove() == false)
	{
		ECS::GetComponent<Sprite>(ouchUI).SetTransparency(1.0);
	}
	else
	{
		ECS::GetComponent<Sprite>(ouchUI).SetTransparency(0);

	}
}

b2Vec2 AngerLevel::CalculateAngle(int entityOne, int entityTwo)
{
	float deltaX = 0, deltaY = 0;
	deltaX = ECS::GetComponent<PhysicsBody>(entityOne).GetBody()->GetPosition().x - ECS::GetComponent<PhysicsBody>(entityTwo).GetBody()->GetPosition().x;
	deltaY = ECS::GetComponent<PhysicsBody>(entityOne).GetBody()->GetPosition().y - ECS::GetComponent<PhysicsBody>(entityTwo).GetBody()->GetPosition().y;

	return b2Vec2(deltaX, deltaY);
}

void AngerLevel::CrumblingPlatforms(int entity)
{
	if (ECS::GetComponent<CrumblingSequence>(entity).disablePlatform() != -1)
	{
		if (ECS::GetComponent<CrumblingSequence>(entity).disablePlatform() == 0)
		{
			ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
			ECS::GetComponent<PhysicsBody>(entity).GetBody()->SetActive(true);
			ECS::GetComponent<CrumblingSequence>(entity).disable = false;
		}
		else if (ECS::GetComponent<CrumblingSequence>(entity).disablePlatform() == 1)
		{
			//ECS::GetComponent<Sprite>(entity).SetTransparency(0.4f);
			ECS::GetComponent<PhysicsBody>(entity).GetBody()->SetActive(false);
			ECS::GetComponent<CrumblingSequence>(entity).disable = false;
		}
	}
}

void AngerLevel::TestUpdatePosition(int cameraEntity, int bodyEntity, int tempOffsetX, int tempOffsetY)
{
	auto& cameraBody = ECS::GetComponent<Camera>(cameraEntity);
	auto& shieldBody = ECS::GetComponent<PhysicsBody>(bodyEntity);
	int offsetX = tempOffsetX;
	int offsetY = tempOffsetY;

	//shieldBody.SetPosition(vec3(cameraBody.GetPosition().x + offsetX, cameraBody.GetPosition().y + offsetY, 4));
	shieldBody.SetPosition(b2Vec2(cameraBody.GetPosition().x + offsetX, cameraBody.GetPosition().y + offsetY));
}


 
