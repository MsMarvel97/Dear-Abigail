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
	m_physicsWorld = new b2World(m_gravity);
	m_physicsWorld->SetContactListener(&listener);
	SetSceneChange(false, -1);

	//Attach the register 
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera 
	float aspectRatio = windowWidth / windowHeight;

	//Setup MainCamera Entity 
	SpawnMainCamera(windowWidth, windowHeight);
	//main player entity 
	SpawnMainPlayer(0.f, 80.f);
	//ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).SetPosition(b2Vec2(0.f, 80.f), true); //beginning
	//ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).SetPosition(b2Vec2(3216.f, 80.f), true); //boss platform
	//ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).SetPosition(b2Vec2(916.f, 90.f), true); //platform D
	//ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).SetPosition(b2Vec2(1844.f, 200.f), true); //random

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



	////Shadow 7(Final Boss)
	//{
	//	//Creates entity
	//	auto entity = ECS::CreateEntity();
	//	boss = entity;
	//	//Add components
	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);
	//	ECS::AttachComponent<PhysicsBody>(entity);
	//	ECS::AttachComponent<ShadowLoop>(entity);

	//	//Sets up components
	//	std::string fileName = "S1.png";
	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 96, 96);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));


	//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	//	float shrinkX = 0.f;
	//	float shrinkY = 0.f;
	//	b2Body* tempBody;
	//	b2BodyDef tempDef;
	//	tempDef.type = b2_staticBody;
	//	tempDef.position.Set(float32(3500.f), float32(250));//(3696.f,120.f)

	//	tempBody = m_physicsWorld->CreateBody(&tempDef);

	//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
	//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, ENEMY, PLAYER);
	//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	//	ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
	//}
	////Final Boss Area Trigger
	//{
	//	//Creates entity
	//	auto entity = ECS::CreateEntity();

	//	//Add components
	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);
	//	ECS::AttachComponent<PhysicsBody>(entity);
	//	ECS::AttachComponent<Trigger*>(entity);
	//	//ECS::AttachComponent<ShadowLoop>(entity);

	//	//Sets up components
	//	std::string fileName = "sandFloor.png";
	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 480, 500);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(3510.f, 200.f, 5.f));
	//	ECS::GetComponent<Trigger*>(entity) = new BossAreaTrigger();
	//	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
	//	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());
	//	ECS::GetComponent<Trigger*>(entity)->SetShadowZone(1);
	//	ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
	//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	//	float shrinkX = 0.f;
	//	float shrinkY = 0.f;
	//	b2Body* tempBody;
	//	b2BodyDef tempDef;
	//	tempDef.type = b2_staticBody;
	//	tempDef.position.Set(float32(3520.f), float32(200.f));

	//	tempBody = m_physicsWorld->CreateBody(&tempDef);

	//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
	//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
	//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	//}
	
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
		tempDef.position.Set(float32(1900.f),float32(-15.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Set up breakable wall
	{
		auto entity = ECS::CreateEntity();
		breakableWalls[0] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<BreakableWall>(entity);

		std::string fileName = "spritesheets/Wall.png";
		std::string JSONfile = "BreakWall.json";

		ECS::GetComponent<BreakableWall>(entity).InitBreakableWall(fileName, JSONfile, 20, 60, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(80.f, 33.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(80.f), float32(45.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
	}
	//Set up breakable wall trigger
	{
		//create entity
		auto entity = ECS::CreateEntity();
		breakableWallTriggers[0];

		//attach components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		
		//set up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new BreakableWallTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(breakableWalls[0]);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(80.f), float32(50.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(10 + 10),
			float(30), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	

	SpawnUI();
	SpawnPlatforms();
	SpawnCrumblingPlatforms();
	SpawnTiles();
	SpawnMovingPlatforms();
	SpawnShadows();
	SpawnSpikes();
	SpawnOrbs();
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
	SpawnPlatform(2224.f, 34.f, 64.f, 16.f, "SamplePlatform.png", 1.f);//Platform P
	SpawnPlatform(2336.f, 59.2f, 64.f, 16.f, "SamplePlatform.png", 1.f);//Platform Q
	SpawnPlatform(2448.f, 92.8f, 64.f, 16.f, "SamplePlatform.png", 1.f);//Platform R
	SpawnPlatform(2544.f, 131.2f, 64.f, 16.f, "SamplePlatform.png", 1.f);//Platform S
	SpawnPlatform(2528.f, 51.2f, 64.f, 16.f, "SamplePlatform.png", 1.f);//Platform T
	SpawnPlatform(3216.f, 40.f, 32.f, 16.f, "SamplePlatform.png", 1.f);//Platform Z

	SpawnPlatform(3256.f, 40.f, 48.f, 16.f, "SamplePlatform.png", 1.f);//Platform ZC (connects Z to ZA)
	orbWall = SpawnPlatform(3268.f, 96.f, 98.f, 8.f, "SamplePlatform.png", 1.f,90.f); //Platform ZD (wall that disappears by destroying an orb)

	SpawnPlatform(3848.f, 72.f, 80.f, 16.f, "SamplePlatform.png", 1.f);//Platform ZB

	SpawnPlatform(1844.f, -50.f, 50.f, 16.f, "SamplePlatform.png", 0.f);//hidden platform that catches bullets and stops them from falling into infinity

}

void AngerLevel::SpawnCrumblingPlatforms()
{
	//int Scene::SpawnCrumblingPlatform(float xPos, float yPos, float width, float height)
	masterCrumblingPlatforms[0] = SpawnCrumblingPlatform(2640.f, 72.f, 48.f, 32.f, false); // Crumbling Platform U
	masterCrumblingPlatforms[1] = SpawnCrumblingPlatform(2736.f, 60.f, 48.f, 32.f, false); // Crumbling Platform V
	masterCrumblingPlatforms[2] = SpawnCrumblingPlatform(2864.f, 78.f, 48.f, 32.f, false); // Crumbling Platform W
	masterCrumblingPlatforms[3] = SpawnCrumblingPlatform(2960.f, 40.f, 48.f, 32.f, false); // Crumbling Platform X

	masterCrumblingPlatforms[4] = SpawnCrumblingPlatform(3300.f, 150.f, 48.f, 32.f, false); // Boss Platform 1
	masterCrumblingPlatforms[5] = SpawnCrumblingPlatform(3380.f, 110.f, 48.f, 32.f, false); // Boss Platform 2
	masterCrumblingPlatforms[6] = SpawnCrumblingPlatform(3480.f, 74.f, 48.f, 32.f, false); // Boss Platform 3
	masterCrumblingPlatforms[7] = SpawnCrumblingPlatform(3580.f, 110.f, 48.f, 32.f, false); // Boss Platform 4
	masterCrumblingPlatforms[8] = SpawnCrumblingPlatform(3680.f, 144.f, 48.f, 32.f, false); // Boss Platform 5

	float bossCoord = 3304.f;
	for (int i = 9; i < 19; i++) //creates the ground floor of the boss battle (Platform ZA)
	{
		masterCrumblingPlatforms[i] = SpawnCrumblingPlatform(bossCoord, 32.f, 48.f, 32.f, false);
		bossCoord += 48;

	}
}

void AngerLevel::SpawnTiles()
{
	//void Scene::SpawnTile(float xPos, float yPos, std::string sprite, float width, float height)
	SpawnTile(-144.f, 80.f, "backgrounds/anger/anger0-1.png", false, -1.f);// TILE 0-1
	SpawnTile(112.f, 80.f, "backgrounds/anger/anger1-1.png", false, -1.f);// TILE 1-1
	SpawnTile(368.f, 80.f, "backgrounds/anger/anger2-1.png", false, -1.f);// TILE 2-1
	SpawnTile(624.f, 80.f, "backgrounds/anger/anger3-1.png", false, -1.f);// TILE 3-1 ???
	SpawnTile(880.f, 80.f, "backgrounds/anger/anger4-1.png", false, -1.f);// TILE 4-1
	SpawnTile(1136.f, 80.f, "backgrounds/anger/anger5-1.png", false, -1.f);// TILE 5-1
	SpawnTile(1392.f, 80.f, "backgrounds/anger/anger6-1.png", false, -1.f);// TILE 6-1
	SpawnTile(1648.f, 80.f, "backgrounds/anger/anger7-1.png", false, -1.f);// TILE 7-1
	SpawnTile(1904.f, 80.f, "backgrounds/anger/anger8-1.png", false, -1.f);// TILE 8-1
	SpawnTile(2160.f, 80.f, "backgrounds/anger/anger9-1.png", false, -1.f);// TILE 9-1
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
		SpawnTile(((-16 + 16 * i) * 16.f) + 112, -200.f, "backgrounds/anger/water.png",256.f,64.f);// TILE 16-2 //-80
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
	b2Vec2 newShadows[7];

	//spawning shadows with their associated triggers
	newShadows[0] = SpawnShadow(337.5f, 70.f, 226.f, 449.f, false, b2Vec2(30.f, 0.f),0.f,0.f);
	newShadows[1] = SpawnShadow(656.f, 30.f, 501.f, 664.f, false, b2Vec2(30.f, 0.f), 0.f, 0.f);
	newShadows[2] = SpawnShadow(1344.f, 77.f, 1220.f, 1368.f, false, b2Vec2(30.f, 0.f), 0.f, 0.f); //1220, 1368
	newShadows[3] = SpawnShadow(2096.f, 112.f, 1991.f, 2149.f, false, b2Vec2(30.f, 0.f), 0.f, 0.f); //1991, 2149
	newShadows[4] = SpawnShadow(1613.f, 40.f, 1438.f, 1789.f, false, b2Vec2(30.f, 0.f), 0.f, 0.f); //1438, 1789
	newShadows[5] = SpawnShadow(1070.f, 40.f, 960.f, 1147.f, false, b2Vec2(30.f, 0.f), 0.f, 0.f); //960, 1147
	newShadows[6] = SpawnShadow(3500.f, 250.f, 0.f, 0.f, true, b2Vec2(0.f, 0.f), 20.f, -50.f, 480.f, 500.f);

	//separating all the entities from their triggers and placing them in their respective arrays
	for (int i = 0; i <= 6; i++)
	{
		Separate(newShadows[i], 0);
	}


	bulletWalls[0] = SpawnBulletWall(1011.f, 150.f);
	bulletWalls[1] = SpawnBulletWall(1111.f, 150.f);
	bulletWalls[2] = SpawnBulletWall(1831.f, 120.f);
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
	SpawnSpike(554.f, 15.f); //mini spike
	SpawnSpike(633.f, 15.f); //mini spike
	//SpawnSpike(1048.f, 24.f);
	int spikeXLoc = 818;
	for (int i = 0; i < 4; i++)
	{
		SpawnSpike(spikeXLoc, 80.f);
		spikeXLoc += 16;
	}
	SpawnSpike(1254.f, 55.f);
	SpawnSpike(1350.f, 55.f);
}

void AngerLevel::SpawnOrbs()
{
	SpawnOrb(3300, 180);
	SpawnOrb(3380, 140);
	SpawnOrb(3480, 104);
	SpawnOrb(3580, 140);
	SpawnOrb(3680, 174);

	tutorialOrb = SpawnOrb(3240, 60); //destroying this orb destroys Platform ZD
	ECS::GetComponent<Trigger*>(tutorialOrb) = new SpecialOrbTrigger();
	ECS::GetComponent<Trigger*>(tutorialOrb)->SetTriggerEntity(tutorialOrb);
	ECS::GetComponent<Trigger*>(tutorialOrb)->AddTargetEntity(MainEntities::MainPlayer());
	ECS::GetComponent<Trigger*>(tutorialOrb)->AddTargetEntity(orbWall);
	std::cout << ECS::GetComponent<Trigger*>(tutorialOrb)->GetTargetEntities().size() << "\n";
}

void AngerLevel::Update()
{
	auto& player = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& playerSprite = ECS::GetComponent<Sprite>(MainEntities::MainPlayer());
	auto& thePlayer = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& playerShield = ECS::GetComponent<Kinematics>(shield);
	//auto& shieldThing = ECS::GetComponent<ShieldMechanic>(shield);
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

	for (int i = 0; i < 1; i++) //moving platform related
	{
		ECS::GetComponent<Kinematics>(movingTriggers[i]).UpdatePosition();
		ECS::GetComponent<MovingPlatform>(movingPlatforms[i]).MovePlatform(movingPlatforms[i]);
	}
	
	//kinTrig.UpdatePosition();
	playerMech.RunKnockBackTime();
	playerMech.ActivateShield(); //runs timer for shield
	ECS::GetComponent<Kinematics>(shield).UpdateTransform(); //shield follows player

	if (playerMech.GetShield())
	{
		ECS::GetComponent<Sprite>(shield).SetTransparency(1.f);
	}
	else
	{
		ECS::GetComponent<Sprite>(shield).SetTransparency(0.f);
	}

	//AngerLevel::CheckShield();
	ReattachCamera();

	if (playerMech.GetCanMove() == true) //checks to see if the player can move
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
	//playerMech.RunShadowTime();

	//checks to see if the boss is alive and can therefore shoot
	if (angerBoss.GetBossDefeated() == false) 
	{
		ActivateShadow(boss);
	}
	else
	{
		bossSprite.SetTransparency(0.f);
		bossBody.GetBody()->SetActive(false);
	}


	//AngerLevel::MovePlatform();
	PlayerDeath();

	//win condition(kill boss to open platform)
	//checks to see if the boss has been defeated and therefore the boss and wall can be destroyed
	if (angerBoss.GetBossDefeated() == true) 
	{
		if (bossWallDestroyed == false)
		{
			PhysicsBody::m_bodiesToDelete.push_back(bossWall);
			bossWallDestroyed = true;
		}
	}

	//for platforms u,v,w,x,b1,b2,b3,b4,b5, and the 10 crumbling platforms that make up the ground of the boss level
	for (int i = 0; i < 18; i++) 
	{
		ECS::GetComponent<CrumblingSequence>(masterCrumblingPlatforms[i]).Crumble(masterCrumblingPlatforms[i]);
		CrumblingPlatforms(masterCrumblingPlatforms[i]);
	}

	//playerMech.CheckWallStatus(breakableWalls[0],breakableWallTriggers[0]);
	
	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).Update();
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).Update();

	//For UI Elements
	for (int i = 0; i < 6; i++)
	{
		ECS::GetComponent<Kinematics>(uiElements[i]).UpdateUI();
	}

	UpdateUI(); 

	//shadow contact/pause and shadow animation stuff
	for (int i = 0; i < 6; i++) 
	{
		ECS::GetComponent<ShadowLoop>(shadows[i]).ShadowRoutine(shadows[i]);
		ECS::GetComponent<Kinematics>(sZones[i]).UpdatePosition();
		ECS::GetComponent<ShadowLoop>(shadows[i]).ShadowPause(shadows[i]);
	}

	//for the breakable wall at the beginning of the level
	ECS::GetComponent<BreakableWall>(breakableWalls[0]).WallRoutine(breakableWalls[0]);

	//bullet walls
	for (int i = 0; i < 3; i++)
	{
		SpawnBullet(bulletWalls[i], 0, -13);
	}

	playerMech.RunInvincibility(); //invincibility timer
}

void AngerLevel::KeyboardHold()
{
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

 
	
		if (Input::GetKeyDown(Key::Q) && playerMech.GetAttackSequence() == false) 
		{
			playerMech.SetShieldSequence(true);
		}

		if (Input::GetKeyDown(Key::E) && playerMech.GetAttackSequence() == false && playerMech.GetShield() == false)
		{
			playerMech.SetAttackSequence(true);
		}
	
	

 
	if (Input::GetKeyDown(Key::M)) {
		std::cout << "X Pos: " << playerPos.x << std::endl;
		std::cout << "Y Pos: " << playerPos.y << std::endl << std::endl;
	}
	if (Input::GetKeyDown(Key::T))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}
	
	if (Input::GetKeyDown(Key::C))
	{
		float size = ECS::GetComponent<Camera>(MainEntities::MainCamera()).GetOrthoSize().x;
		vec4 temp = vec4(0.f, 0.f, 0.f, 0.f);
		if (size == -75.f)
		{
			vec4 temp = vec4(-300.f, 300.f, -300.f, 300.f);
			ECS::GetComponent<Camera>(MainEntities::MainCamera()).SetOrthoSize(temp);
		}
		else
		{
			temp = vec4(-75.f, 75.f, -75.f, 75.f);
			ECS::GetComponent<Camera>(MainEntities::MainCamera()).SetOrthoSize(temp);
		}
	}
 
}

void AngerLevel::ReattachCamera()
{
	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

//outdated(needs to be fixed or scrapped)
void AngerLevel::CheckShield() 
{
	////checks inputs from the ShieldMechanic and proceeds to turn the shield on or off
	////auto& playerHealth = ECS::GetComponent<Health>(player);
	//auto& playerMech = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	//if (ECS::GetComponent<ShieldMechanic>(shield).shieldOn == true)
	//{
	//	/*ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetActive(true);*/
	//	//ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetAwake(true);
	//	ECS::GetComponent<Sprite>(shield).SetTransparency(1.f);
	//	//shieldActive = true; //currently useless
	//	playerMech.SetShield(true); //Used by the BulletTrigger to check if the shield is on.
	//}
	//else if (ECS::GetComponent<ShieldMechanic>(shield).shieldOn == false)
	//{
	//	/*ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetActive(false);*/
	//	//ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetAwake(false);
	//	ECS::GetComponent<Sprite>(shield).SetTransparency(0.f);
	//	//shieldActive = false; //currently useless
	//	playerMech.SetShield(false); //Used by the BulletTrigger to check if the shield is on.
	//}
}

//boos shadow
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
		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | GROUND | ENVIRONMENT);
	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	tempPhsBody.SetGravityScale(0.f); //ensures no bullet drop and bullet reaches the player

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ShootBullet(entity);
}

void AngerLevel::ShootBullet(int bullet)
{
	//shootBulletSound.Play();
	//shootBulletSound.SetVolume(5.0f);
	b2Vec2 angle = CalculateAngle(MainEntities::MainPlayer(), bullet);

	float dirAngle = atan(angle.x / angle.y) * (180 / PI);

	ECS::GetComponent<PhysicsBody>(bullet).SetRotationAngleDeg(dirAngle * -1);
	ECS::GetComponent<PhysicsBody>(bullet).GetBody()->SetLinearVelocity(b2Vec2(angle.x * 100, angle.y * 100));

	float x = ECS::GetComponent<PhysicsBody>(bullet).GetVelocity().x;
	float y = ECS::GetComponent<PhysicsBody>(bullet).GetVelocity().y;
}


//bullet wall
void AngerLevel::SpawnBullet(int wall, float offsetX, float offsetY)
{
	static float startTime = 0;
	auto& wallLoc = ECS::GetComponent<PhysicsBody>(wall);

	if (startTime == 0)
	{
		startTime = Timer::time;
	}

	float currentTime = Timer::StopWatch(startTime);

	if (currentTime >= 0.3) //this statement will run once the player has entered a ShadowAreaTrigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Set up components
		std::string fileName = "bullet.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 4, 8);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(wallLoc.GetPosition().x + offsetX, wallLoc.GetPosition().y + offsetY, 4.f));

		ECS::GetComponent<Trigger*>(entity) = new BulletTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(wallLoc.GetPosition().x + offsetX, wallLoc.GetPosition().y + offsetY);

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | GROUND | ENVIRONMENT);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		tempPhsBody.SetGravityScale(0.f); //ensures no bullet drop and bullet reaches the player

		ShootBullet(entity, 0);

		if (wall == bulletWalls[2]) //this has to be equal to the last entry in the bulletWalls array. If it isn't, any elements after this number will not spawn bullets.
		{
			startTime = 0;
		}
	}
}

void AngerLevel::ShootBullet(int bullet, float degrees)
{
	ECS::GetComponent<PhysicsBody>(bullet).SetRotationAngleDeg(degrees);
	ECS::GetComponent<PhysicsBody>(bullet).GetBody()->SetLinearVelocity(b2Vec2(0, -100));
}


void AngerLevel::ActivateShadow(int shadow)
{
	//Checks to see if the appropriate amount of seconds of passed between now and the last shot. 
	//If so, a bullet is fired from a shadow determined by the player's location.
	auto& shade = ECS::GetComponent<ShadowLoop>(shadow);


	shade.ShadowRoutine(shadow);

	if (shade.GetFiring() && shade.GetShadowSequence())
	{
		SpawnBullet(shadow);
	}

	//if (shade.GetFiring() == true)
	//{
	//	shade.ShadowRoutine(shadow);

	//	if (shade.GetFiring() && shade.GetShadowSequence())
	//	{
	//		SpawnBullet(shadow);
	//	}

	//	//if (shade.GetShadowLoc() == 1)
	//	//{
	//	//	SpawnBullet(boss);
	//	//}
	//}	
}

void AngerLevel::Separate(b2Vec2(newPair), int type)
{
	if (type == 0)
	{
		int static shadowID = 0;
		if (shadowID == 6)
		{
			boss = newPair.x;
		}
		else
		{
			shadows[shadowID] = newPair.x;
			sZones[shadowID] = newPair.y;
		}
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

void AngerLevel::PlayerDeath()
{
	//auto& playerHealth = ECS::GetComponent<Health>(player);
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	auto& playerBody = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());

	if (playerMech.GetRespawn() == true) //if player falls off map
	{
		playerBody.SetPosition(b2Vec2(50, 50));
		playerMech.SetHealth(3);
		playerMech.SetRespawn(false);
		for (int i = 0; i < 3; i++)
		{
			ECS::GetComponent<Sprite>(hearts[i]).SetTransparency(1.f);
		}
	}
}




void AngerLevel::UpdateUI()
{
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	//auto& shieldMech = ECS::GetComponent<ShieldMechanic>(shield);
	auto& gameCoolDown = ECS::GetComponent<CoolDown>(MainEntities::MainPlayer());

	//initalizing the shield UI as available
	if (playerMech.GetShield())
	{
		ECS::GetComponent<Sprite>(shieldUI).LoadSprite(shieldOn, 30, 30);
		ECS::GetComponent<Sprite>(shieldUI).SetTransparency(1.f);
	}
	else
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




 
