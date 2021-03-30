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
	{
		//Creates Camera entity 
		auto entity = ECS::CreateEntity();
		camera = entity;

		ECS::SetIsMainCamera(entity, true);

		//Creates new orthographic camera 
		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<VerticalScroll>(entity);


		vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f); //original
		//vec4 temp = vec4(-350.f, 350.f, -350.f, 350.f); //modified for debugging

		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		//Attaches the camera to vert and horiz scrolls 
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	}
	//main player entity 
	{
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainPlayer(entity, true);

		player = entity;
		//Add components 
		ECS::AttachComponent<Player>(entity);
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<MovingClass>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PlayerMechanics>(entity);
		ECS::AttachComponent<CoolDown>(entity); //denial exclusive?
		ECS::AttachComponent<BossLevel>(entity); //denial exclusive		

		//Sets up the components 
		std::string fileName = "spritesheets/abigailSpritesheet.png";
		std::string animations = "abigailAnimations.json";

		ECS::GetComponent<Player>(entity).InitPlayer(fileName, animations, 25, 25, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity), &ECS::GetComponent<Transform>(entity));
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 30.f, 5.f));
		ECS::GetComponent<PlayerMechanics>(entity).SetHealth(3);


		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);


		float shrinkX = 8.f;
		float shrinkY = 3.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;

		tempDef.position.Set(float32(0), float32(80.f)); //beginning
		//tempDef.position.Set(float32(3216.f), float32(80.f)); //boss platform
		//tempDef.position.Set(float32(700), float32(80.f)); //bridge
		//tempDef.position.Set(float32(1006), float32(80.f)); //spike
		//tempDef.position.Set(float32(2456), float32(120.f)); //beginning of crumbling platforms
		//tempDef.position.Set(float32(331), float32(70.f)); //shadow 1
		//tempDef.position.Set(float32(1266), float32(70.f)); //shadow 3		
		//tempDef.position.Set(float32(3806), float32(100.f)); //end platform
		//tempDef.position.Set(float32(2452.f), float32(130.f)); //shadow 5

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, PLAYER, ENEMY | OBJECTS | PICKUP | TRIGGER | SNAIL, 0.f, 1.f);


		tempPhsBody.SetRotationAngleDeg(0.f);
		tempPhsBody.SetFixedRotation(true);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));

		tempPhsBody.SetGravityScale(0.75f);
	}
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


		double playerSpriteX = ECS::GetComponent<Sprite>(player).GetWidth();
		double playerSpriteY = ECS::GetComponent<Sprite>(player).GetHeight();

		//Sets up components
		std::string fileName = "ShieldTemp.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, playerSpriteX, playerSpriteY);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 4.f));
		ECS::GetComponent<Kinematics>(entity).SetChild(entity);
		ECS::GetComponent<Kinematics>(entity).SetParent(player);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0.f, 0.f);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
	}

	//old platform code
	{
		////platform A
		//{
		//	//Creates entity 
		//	auto entity = ECS::CreateEntity();

		//	//Add components 
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components 
		//	std::string fileName = "SamplePlatform.png";
	 //
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 192, 16);
	 //
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 192, 16);
	 //
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 0.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
	 //
		//	tempDef.position.Set(float32(96.f), float32(8.f));
	 //

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Platform B 
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 224, 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
	 //
		//	tempDef.position.Set(float32(336.f), float32(40.f));
	 //
		//	tempDef.position.Set(float32(336.f), float32(40.f));
	 //

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Platform C 
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 0.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(608.f), float32(8.f)); //608,8

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//} 
		////Platform D 
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 240);
		//	ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;//change to dynamic and this is meant to fall down like a bridge
		//	tempDef.position.Set(840,60); //712,120

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

	 //
		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, OBJECTS, GROUND | ENVIRONMENT | PLAYER,0.3f);
	 //
		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, OBJECTS, GROUND | ENVIRONMENT | PLAYER, 0.3f);
	 //
		//	tempPhsBody.SetRotationAngleDeg(90.f);
		//	tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
		//	tempPhsBody.SetFixedRotation(true);
		//	tempPhsBody.SetGravityScale(0.5f);
		//}
		////Platform D_BridgeHelp_
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 48);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
	 //
		//	tempDef.position.Set(float32(700.8f), float32(24.f));
	 //
		//	tempDef.position.Set(float32(700.8f), float32(24.f));
	 //

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f)); 
		//	tempSpr.SetTransparency(1.f); 
		//}
		////Platform D_BridgeHelp_2
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
	 //
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 8.f, 8.f);
	 //
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(732.f), float32(20.f));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		//	tempPhsBody.GetBody()->SetActive(false);
		//}
		////Platform E
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 224, 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 0.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(1056.f), float32(8.f));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Platform F
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 192, 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
	 //
		//	tempDef.position.Set(float32(1296.f), float32(40.f));
	 //
		//	tempDef.position.Set(float32(1296.f), float32(48.f));
	 //

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//} 
		////Platform M 
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
	 //
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 16);
	 //
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 0.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(1616.f), float32(8.f));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Platform N 
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 64, 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
	 //
		//	tempDef.position.Set(float32(1888.f), float32(40.f));
	 //
		//	tempDef.position.Set(float32(1888.f), float32(40.f));
	 //

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Platform O 
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "LargeSamplePlatform.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 192, 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(2064.f), float32(72.f));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Platform P
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 64, 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(2224.f), float32(24.f));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Platform Q
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 64, 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(2336.f), float32(59.2f));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Platform R
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName,64, 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(2448.f), float32(92.8));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Platform S
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 64, 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(2544.f), float32(131.2f));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//}
		////Platform T
		//{
		//	//Creates entity
		//	auto entity = ECS::CreateEntity();

		//	//Add components
		//	ECS::AttachComponent<Sprite>(entity);
		//	ECS::AttachComponent<Transform>(entity);
		//	ECS::AttachComponent<PhysicsBody>(entity);

		//	//Sets up components
		//	std::string fileName = "SamplePlatform.png";
		//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 64, 16);
		//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//	float shrinkX = 0.f;
		//	float shrinkY = 0.f;
		//	b2Body* tempBody;
		//	b2BodyDef tempDef;
		//	tempDef.type = b2_staticBody;
		//	tempDef.position.Set(float32(2528.f), float32(51.2f));

		//	tempBody = m_physicsWorld->CreateBody(&tempDef);

		//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		//} 
	}


	//Platform U Crumbling Platform #1 //commented
	{
		////Creates entity
		//auto entity = ECS::CreateEntity();
		//cPlatforms[0] = entity;

		////Add components
		//ECS::AttachComponent<Sprite>(entity);
		//ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);
		//ECS::AttachComponent<CrumblingSequence>(entity);
		//ECS::AttachComponent<AnimationController>(entity);

		////Sets up components
		///*std::string fileName = "sandFloor.png";*/
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

		//tempDef.position.Set(float32(2640.f), float32(72.f)); //(2640,72)

		//tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//	float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Platform U Trigger //commented
	{
		////Creates entity
		//auto entity = ECS::CreateEntity();
		//cTriggers[0] = entity;

		////Add components
		//ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);
		//ECS::AttachComponent<Trigger*>(entity);

		////Sets up components
		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		//ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		//ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		//ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[0]);


		//auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		//
		//float shrinkX = 0.f;
		//float shrinkY = 0.f;
		//b2Body* tempBody;
		//b2BodyDef tempDef;
		//tempDef.type = b2_staticBody;

		//tempDef.position.Set(float32(2640), float32(72));

		//tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float(48),
		//	float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		//tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Platform V Crumbling Platform #2 //commented
	{
		////Creates entity
		//auto entity = ECS::CreateEntity();
		//cPlatforms[1] = entity;

		////Add components
		//ECS::AttachComponent<Sprite>(entity);
		//ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);
		//ECS::AttachComponent<CrumblingSequence>(entity);
		//ECS::AttachComponent<AnimationController>(entity);

		////Sets up components
		///*std::string fileName = "sandFloor.png";*/
		//std::string fileName = "spritesheets/crumblingPlatform.png";
		//std::string JSONFile = "crumble.json";

		//ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity), &ECS::GetComponent<AnimationController>(entity));
		//ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 32); //(64,16)

		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//float shrinkX = 0.f;
		//float shrinkY = 0.f;
		//b2Body* tempBody;
		//b2BodyDef tempDef;
		//tempDef.type = b2_staticBody;

		//tempDef.position.Set(float32(2736.f), float32(60.f)); 

		//tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//	float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Platform V Trigger //commented
	{
		////Creates entity
		//auto entity = ECS::CreateEntity();
		//cTriggers[1] = entity;
		//auto& plat = ECS::GetComponent<PhysicsBody>(cPlatforms[1]);
		////Add components
		//ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);
		//ECS::AttachComponent<Trigger*>(entity);

		////Sets up components
		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		//ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		//ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		//ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[1]);


		//auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		//auto& tempSpr = ECS::GetComponent<Sprite>(cPlatforms[1]);
		//float shrinkX = 0.f;
		//float shrinkY = 0.f;
		//b2Body* tempBody;
		//b2BodyDef tempDef;
		//tempDef.type = b2_staticBody;

		////tempDef.position.Set(plat.GetBody()->GetPosition().x, plat.GetBody()->GetPosition().y);

		//tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float(48),
		//	float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		//tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Platform W Crumbling Platform #3 //commented
	{
		////Creates entity
		//auto entity = ECS::CreateEntity();
		//cPlatforms[2] = entity;

		////Add components
		//ECS::AttachComponent<Sprite>(entity);
		//ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);
		//ECS::AttachComponent<CrumblingSequence>(entity);
		//ECS::AttachComponent<AnimationController>(entity);

		////Sets up components
		////std::string fileName = "sandFloor.png";
		//std::string fileName = "spritesheets/crumblingPlatform.png";
		//std::string JSONFile = "crumble.json";

		//ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity), &ECS::GetComponent<AnimationController>(entity));
		//ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 32);

		//auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//float shrinkX = 0.f;
		//float shrinkY = 0.f;
		//b2Body* tempBody;
		//b2BodyDef tempDef;
		//tempDef.type = b2_staticBody;

		//ECS::GetComponent<Transform>(entity).SetPositionZ(2.f);
		//tempDef.position.Set(float32(2864.f), float32(88.f));
		//

		//tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//	float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Platform W Trigger //commented
	{
		////Creates entity
		//auto entity = ECS::CreateEntity();
		//cTriggers[2] = entity;
		//auto& plat = ECS::GetComponent<PhysicsBody>(cPlatforms[2]);

		////Add components
		//ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);
		//ECS::AttachComponent<Trigger*>(entity);

		////Sets up components
		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		//ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		//ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		//ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[2]);


		//auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		//auto& tempSpr = ECS::GetComponent<Sprite>(cPlatforms[2]);
		//float shrinkX = 0.f;
		//float shrinkY = 0.f;
		//b2Body* tempBody;
		//b2BodyDef tempDef;
		//tempDef.type = b2_staticBody;

		////tempDef.position.Set(plat.GetBody()->GetPosition().x, plat.GetBody()->GetPosition().y);

		//tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//	float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		//tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Platform X Crumbling Platform #4 //commented
	{
		////Creates entity
		//auto entity = ECS::CreateEntity();
		//cPlatforms[3] = entity;


		////Add components
		//ECS::AttachComponent<Sprite>(entity);
		//ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);
		//ECS::AttachComponent<CrumblingSequence>(entity);
		//ECS::AttachComponent<AnimationController>(entity);

		////Sets up components
		///*std::string fileName = "sandFloor.png";*/
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

		//tempDef.position.Set(2960, 40); //(2960,40)


		//tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//	float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Platform X Trigger //commented
	{
		////Creates entity
		//auto entity = ECS::CreateEntity();
		//cTriggers[3] = entity;
		//auto& plat = ECS::GetComponent<PhysicsBody>(cPlatforms[3]);

		////Add components
		//ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);
		//ECS::AttachComponent<Trigger*>(entity);

		////Sets up components
		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		//ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		//ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		//ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[3]);


		//auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		//auto& tempSpr = ECS::GetComponent<Sprite>(cPlatforms[3]);
		//float shrinkX = 0.f;
		//float shrinkY = 0.f;
		//b2Body* tempBody;
		//b2BodyDef tempDef;
		//tempDef.type = b2_staticBody;

		//tempDef.position.Set(plat.GetBody()->GetPosition().x, plat.GetBody()->GetPosition().y);

		//tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//	float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		//tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Platform Y(moving floor)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		movingPlat = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components

		std::string fileName = "SamplePlatform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 80, 8);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_kinematicBody;

		tempDef.position.Set(3056,88); //(3056,88)


		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//moving trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		kinTrigger = entity;

		//Add components
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Kinematics>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		ECS::GetComponent<Kinematics>(entity).SetParent(movingPlat);
		ECS::GetComponent<Kinematics>(entity).SetChild(entity);

		ECS::GetComponent<Trigger*>(entity) = new MovingTrigger;
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);

 
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempSpr = ECS::GetComponent<Sprite>(movingPlat);
		float shrinkX = 0.f;
		float shrinkY = 0.f;
 
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(3848.f), float32(96.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

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
	//Platform ZB (end platform) //commented
	{
		////Creates entity
		//auto entity = ECS::CreateEntity();

		////Add components
		//ECS::AttachComponent<Sprite>(entity);
		//ECS::AttachComponent<Transform>(entity);
		//ECS::AttachComponent<PhysicsBody>(entity);

		////Sets up components
		//std::string fileName = "SamplePlatform.png";
		//ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 80, 16);
 
		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		//auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		//auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		//float shrinkX = 0.f;
		//float shrinkY = 0.f;
		//b2Body* tempBody;
		//b2BodyDef tempDef;
		//tempDef.type = b2_staticBody;
 
		//tempDef.position.Set(float32(3848.f), float32(72.f));
 

		//tempBody = m_physicsWorld->CreateBody(&tempDef);

		//tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		//	float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		//tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
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
	//Shadow 1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shadows[0] = entity;
 
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity); 
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string fileName = "spritesheets/AttackSheet.png";
		std::string JSONfile = "AttackShadow.json";

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);

		ECS::GetComponent<ShadowLoop>(entity).InitMeleeShadow(fileName, JSONfile, 32, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));
		//ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);
 
		ECS::GetComponent<ShadowLoop>(entity).SetMovementBoundaries(239, 449);
		ECS::GetComponent<ShadowLoop>(entity).SetPatrolVelocity(b2Vec2(30.f, 0.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		
		tempDef.position.Set(float32(416.f), float32(70.f));
		

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(32), float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}
	//ShadowAreaTrigger for Shadow 1
	{
		auto entity = ECS::CreateEntity();
		sZones[0] = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<Kinematics>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 50);

		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(shadows[0], shadows[0] - 50, 0.f));

		ECS::GetComponent<Trigger*>(entity) = new ShadowAreaTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(shadows[0]);

		ECS::GetComponent<Kinematics>(entity).SetChild(sZones[0]);
		ECS::GetComponent<Kinematics>(entity).SetParent(shadows[0]);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0, -20);

		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(416.f), float32(70.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Shadow 2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shadows[1] = entity;
 
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity); 
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		//Sets up components
		std::string fileName = "spritesheets/AttackSheet.png";
		std::string JSONfile = "AttackShadow.json";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<ShadowLoop>(entity).InitMeleeShadow(fileName, JSONfile, 32, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));
		//ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);

		ECS::GetComponent<ShadowLoop>(entity).SetMovementBoundaries(501, 664);
		ECS::GetComponent<ShadowLoop>(entity).SetPatrolVelocity(b2Vec2(30.f, 0.f)); 

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
 
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(656.f), float32(30.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}
	//ShadowAreaTrigger for Shadow 2
	{
		auto entity = ECS::CreateEntity();
		sZones[1] = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<Kinematics>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 50);

		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(shadows[0], shadows[0] - 50, 0.f));

		ECS::GetComponent<Trigger*>(entity) = new ShadowAreaTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(shadows[1]);

		ECS::GetComponent<Kinematics>(entity).SetChild(sZones[1]);
		ECS::GetComponent<Kinematics>(entity).SetParent(shadows[1]);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0, 50);

		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(416.f), float32(70.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Shadow 3
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shadows[2] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string fileName = "spritesheets/AttackSheet.png";
		std::string JSONfile = "AttackShadow.json";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<ShadowLoop>(entity).InitMeleeShadow(fileName, JSONfile, 32, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));
		//ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);

		ECS::GetComponent<ShadowLoop>(entity).SetMovementBoundaries(1220, 1368);
		ECS::GetComponent<ShadowLoop>(entity).SetPatrolVelocity(b2Vec2(30.f, 0.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(1344.f), float32(77.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}
	//ShadowAreaTrigger for Shadow 3
	{
		auto entity = ECS::CreateEntity();
		sZones[2] = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<Kinematics>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 50);

		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(shadows[0], shadows[0] - 50, 0.f));

		ECS::GetComponent<Trigger*>(entity) = new ShadowAreaTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(shadows[2]);

		ECS::GetComponent<Kinematics>(entity).SetChild(sZones[2]);
		ECS::GetComponent<Kinematics>(entity).SetParent(shadows[2]);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0, 50);

		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(416.f), float32(70.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Shadow 4
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shadows[3] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string fileName = "spritesheets/AttackSheet.png";
		std::string JSONfile = "AttackShadow.json";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<ShadowLoop>(entity).InitMeleeShadow(fileName, JSONfile, 32, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));
		//ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);

		ECS::GetComponent<ShadowLoop>(entity).SetMovementBoundaries(1991, 2149);
		ECS::GetComponent<ShadowLoop>(entity).SetPatrolVelocity(b2Vec2(30.f, 0.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(2096.f), float32(112.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}
	//ShadowAreaTrigger for Shadow 4
	{
		auto entity = ECS::CreateEntity();
		sZones[3] = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<Kinematics>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 50);

		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(shadows[0], shadows[0] - 50, 0.f));

		ECS::GetComponent<Trigger*>(entity) = new ShadowAreaTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(shadows[3]);

		ECS::GetComponent<Kinematics>(entity).SetChild(sZones[3]);
		ECS::GetComponent<Kinematics>(entity).SetParent(shadows[3]);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0, 50);

		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(416.f), float32(70.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Shadow 5
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shadows[4] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string fileName = "spritesheets/AttackSheet.png";
		std::string JSONfile = "AttackShadow.json";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<ShadowLoop>(entity).InitMeleeShadow(fileName, JSONfile, 32, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));
		//ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(2544.f), float32(176.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Shadow 6
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shadows[5] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string fileName = "spritesheets/AttackSheet.png";
		std::string JSONfile = "AttackShadow.json";
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<ShadowLoop>(entity).InitMeleeShadow(fileName, JSONfile, 32, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));
		//ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(2960, 90); //(2960,64)

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
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
		ECS::GetComponent<Trigger*>(entity) = new ShadowAreaTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<Trigger*>(entity)->SetShadowZone(1);
		ECS::GetComponent<Trigger*>(entity)->SetBossArea(true);
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
	//Trap/Spikes
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "Spike.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<Trigger*>(entity)->SetSpike(true);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;//change to dynamic
		tempDef.position.Set(float32(1048.f), float32(24.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float((tempSpr.GetWidth() - shrinkY) / 2.f), vec2(0.f, 0.f), true, TRIGGER, PLAYER, 0.3f);
 
		tempPhsBody.SetGravityScale(1.3f);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
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
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
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
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
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
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
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
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
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
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 3900, 20);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1900.f, -40.f, 0.f));
		ECS::GetComponent<Trigger*>(entity) = new RespawnTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
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
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
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
	// STATIC BACKGROUND TILES \\
	// TILE 0-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger0-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((-16 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 1-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger1-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3((0.f + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 2-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger2-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((16 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 3-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger3-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((32 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 4-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger4-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((48 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 5-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger5-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((64 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 6-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger6-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((80 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 7-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger7-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((96 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 8-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger8-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((112 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 9-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger9-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((128 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 10-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger10-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((144 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 11-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger11-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((160 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 12-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger12-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((176 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 13-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger13-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((192 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 14-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger14-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((208 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 15-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger15-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((224 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 16-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger16-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((240 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 1.f));
	}

	// TILE 0-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger0-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((-16 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 1-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger1-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3((0.f + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 2-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger2-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((16 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 3-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger3-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((32 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 4-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger4-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((48 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 5-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger5-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((64 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 6-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger6-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((80 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 7-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger7-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((96 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 8-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger8-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((112 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 9-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger9-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((128 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 10-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger10-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((144 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 11-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger11-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((160 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 12-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger12-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((176 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 13-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger13-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((192 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 14-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger14-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((208 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 15-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger15-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((224 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// TILE 16-2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger16-2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((240 * 16.f) + (16 * 7)), ((16 * 16.f) + (16 * 5)), 1.f));
	}

	// WATER
	{
		for (int i = 0; i < 18; i++)
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/anger/water.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3((((-16 + 16*i) * 16.f) + (16 * 7)), ((-16 * 16.f) + (16 * 5)), 1.f));
		}
	}

	SpawnUI();
	SpawnPlatforms();
	SpawnCrumblingPlatforms();
	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void AngerLevel::SpawnPlatforms()
{
	//SpawnPlatform(float xPos, float yPos, float width, float height, std::string sprite, float transparency)
	SpawnPlatform(96.f, 8.f, 192.f, 16.f, "SamplePlatform.png", 1.f); //Platform A
	SpawnPlatform(336.f, 40.f, 224.f, 16.f, "SamplePlatform.png", 1.f); //Platform B
	SpawnPlatform(608.f, 8.f, 256.f, 16.f, "SamplePlatform.png", 1.f); //Platform C
	SpawnPlatform(840.f, 60.f, 16.f, 240.f, "SamplePlatform.png", 1.f, 90.f); //Platform D
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
	auto& kinTrig = ECS::GetComponent<Kinematics>(kinTrigger);
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	
	if (playerMech.GetCanMove() == true)
	{
		player.Update();
	}
	
	kinTrig.UpdatePosition();
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


	AngerLevel::MovePlatform();
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

	ECS::GetComponent<ShadowLoop>(shadows[0]).ShadowRoutine(shadows[0]);
	ECS::GetComponent<Kinematics>(sZones[0]).UpdatePosition();
	ECS::GetComponent<ShadowLoop>(shadows[1]).ShadowRoutine(shadows[1]);	
	ECS::GetComponent<Kinematics>(sZones[1]).UpdatePosition();
	ECS::GetComponent<ShadowLoop>(shadows[2]).ShadowRoutine(shadows[2]);
	ECS::GetComponent<Kinematics>(sZones[2]).UpdatePosition();
	ECS::GetComponent<ShadowLoop>(shadows[3]).ShadowRoutine(shadows[3]);
	ECS::GetComponent<Kinematics>(sZones[3]).UpdatePosition();
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
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(player);
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
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);

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
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(player);
	if (playerMech.GetFiring() == true)
	{
		if (playerMech.GetShadowLoc() == 1)
		{
			AngerLevel::SpawnBullet(boss);
			AngerLevel::ShootBullet();
		}
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
	auto& moveTrig = ECS::GetComponent<MovingClass>(player);
	auto& playerBody = ECS::GetComponent<PhysicsBody>(player);
	auto& plat = ECS::GetComponent<PhysicsBody>(movingPlat);
	//auto& vert = ECS::GetComponent<PhysicsBody>(vertMovingPlat);
	float platX = plat.GetPosition().x;
	float platY = plat.GetPosition().y;
	int playerX = playerBody.GetPosition().x;
	int playerY = playerBody.GetPosition().y;

	static bool vertSwitch = false;

	if (platX > 3170)
	{
		switchDir = true;

	}
	if (platX < 3030)
	{
		switchDir = false;

	}
	if (switchDir == false)
	{
		platX += 0.5;
		//plat.SetPosition(b2Vec2(platX, platY));
		plat.SetVelocity(vec3(30.f, 0.f, 0.f));
		moveTrig.SetRight(true);
		moveTrig.SetLeft(false);

		//plat.SetVelocity(vec3(1250 * Timer::deltaTime, 0, 0));
		//if (moveTrig.GetMoving() == true)
		//{
		//	playerX += 1;
		//	if (!Input::GetKey(Key::A))
		//	{
		//		playerBody.SetVelocity(vec3(5000, 0, 0));
		//	}
		//	//playerBody.SetPosition(b2Vec2(playerX, playerY));
		//}
	}
	else if (switchDir == true)
	{
		platX -= 0.5;
		//plat.SetPosition(b2Vec2(platX, platY));
		plat.SetVelocity(vec3(-30.f, 0.f, 0.f));
		moveTrig.SetLeft(true);
		moveTrig.SetRight(false);
	}
}

void AngerLevel::PlayerDeath()
{
	//auto& playerHealth = ECS::GetComponent<Health>(player);
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(player);
	auto& playerBody = ECS::GetComponent<PhysicsBody>(player);
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
	auto& playerBody = ECS::GetComponent<PhysicsBody>(player);
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		std::cout << "(" << evnt.x << "," << evnt.y << ")\n";
	}
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
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(player);
	auto& shieldMech = ECS::GetComponent<ShieldMechanic>(shield);
	auto& gameCoolDown = ECS::GetComponent<CoolDown>(player);
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


 
