#include "Scene.h"
#include "Utilities.h"

Scene::Scene(std::string name)
{
	m_physicsWorld = new b2World(m_gravity);
	m_name = name;
}

void Scene::Unload()
{
	if (m_sceneReg != nullptr)
	{
		delete m_sceneReg;
		m_sceneReg = nullptr;
	}

	if (m_physicsWorld != nullptr)
	{
		delete m_physicsWorld;
		m_physicsWorld = nullptr;
	}
}

void Scene::InitScene(float windowWidth, float windowHeight)
{
	//Default scene class init just includes a camera so stuff doesn't immediately crash
	printf("You shouldn't be running this, while initializing this Scene Type.\n");

	//Dynamically allocates the register
	if (m_sceneReg == nullptr)
	{
		m_sceneReg = new entt::registry;
	}

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;

	//Setup Main Camera entity
	{
		//Creates Camera entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainCamera(entity, true);

		//Creates new orthographic camera
		ECS::AttachComponent<Camera>(entity);
		//ECS::AttachComponent<HorizontalScroll>(entity);
		vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
	}

	//Setup new Entity
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		m_helloWorldSign = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "HelloWorld.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 60);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.5f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 0.f));
	}
}

void Scene::Update()
{
	auto& tempSpr = m_sceneReg->get<Sprite>(m_helloWorldSign);
	
	tempSpr.SetTransparency((0.5 * sin(Timer::time * 3.f)) + 0.5f);
}

void Scene::AdjustScrollOffset()
{
	float maxSizeX = ECS::GetComponent<Camera>(MainEntities::MainCamera()).GetOrthoSize().y;
	float maxSizeY = ECS::GetComponent<Camera>(MainEntities::MainCamera()).GetOrthoSize().w;

	float playerHalfSize = ECS::GetComponent<Sprite>(MainEntities::MainPlayer()).GetWidth() / 2.f;

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetOffset((maxSizeX * BackEnd::GetAspectRatio()) - playerHalfSize);
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetOffset(maxSizeY - playerHalfSize);
}

void Scene::CreateCameraEntity(bool mainCamera, float windowWidth, float windowHeight, float left, float right, float bottom, float top, 
									float zNear, float zFar, float aspectRatio, bool vertScroll, bool horizScroll)
{
	//Setup main camera
	{
		//Creates Camera Entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainCamera(entity, false);

		ECS::AttachComponent<Camera>(entity);
		if (horizScroll)
		{
			ECS::AttachComponent<HorizontalScroll>(entity);
		}
		if (vertScroll)
		{
			ECS::AttachComponent<VerticalScroll>(entity);
		}

		vec4 temp = vec4(left, right, bottom, top);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, zNear, zFar);

		if (horizScroll)
		{
			ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		}
		if (vertScroll)
		{
			ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		}
	}
}

entt::registry* Scene::GetScene() const
{
	return m_sceneReg;
}

void Scene::SetScene(entt::registry& scene)
{
	m_sceneReg = &scene;
}

int Scene::SpawnUIElement(float xOffset, float yOffset, float width, float height, std::string sprite)
{
	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<Kinematics>(entity);

	//Sets up components
	ECS::GetComponent<Sprite>(entity).LoadSprite(sprite, width, height);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 10.f));

	ECS::GetComponent<Kinematics>(entity).SetChild(entity);
	ECS::GetComponent<Kinematics>(entity).SetParent(MainEntities::MainCamera());
	ECS::GetComponent<Kinematics>(entity).SetOffset(xOffset, yOffset);

	return entity;
}

int Scene::SpawnCrumblingPlatform(float xPos, float yPos, float width, float height)
{
	int entity;
	{
		//Creates entity
		entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<CrumblingSequence>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string fileName = "spritesheets/crumblingPlatform.png";
		std::string JSONFile = "crumble.json";

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, width, height, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(xPos), float32(yPos));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(width - shrinkX),
			float(height - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//creates associated destroy trigger
	{
		//Creates entity
		auto trig = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Transform>(trig);
		ECS::AttachComponent<PhysicsBody>(trig);
		ECS::AttachComponent<Trigger*>(trig);

		//Sets up components
		ECS::GetComponent<Transform>(trig).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(trig) = new DestroyPlatformTrigger();
		ECS::GetComponent<Trigger*>(trig)->SetTriggerEntity(trig);
		ECS::GetComponent<Trigger*>(trig)->AddTargetEntity(entity);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(trig);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(xPos), float32(yPos));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(trig, tempBody, float(width - shrinkX),
			float(height - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	return entity;
}

void Scene::SpawnTile(float xPos, float yPos, std::string sprite, float width, float height)
{
	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);

	//Sets up components
	ECS::GetComponent<Sprite>(entity).LoadSprite(sprite, width, height);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(xPos, yPos, 1.f));
}

int Scene::SpawnPlatform(float xPos, float yPos, float width, float height, std::string sprite, float transparency, float degrees)
{
	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	//Sets up components
	ECS::GetComponent<Sprite>(entity).LoadSprite(sprite, width, height);
	ECS::GetComponent<Sprite>(entity).SetTransparency(transparency);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_staticBody;
	tempDef.position.Set(float32(xPos), float32(yPos));

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	tempPhsBody.SetRotationAngleDeg(degrees);
	return entity;
}

b2Vec2 Scene::SpawnShadow(float xPos, float yPos, float min, float max, bool ranged, b2Vec2 patrolVel, float xOffset, float yOffset, float width, float height)
{
	b2Vec2 shadowPair;

	//Shadow 1
	{
		//Creates entity
		shadowPair.x = ECS::CreateEntity();
		std::string fileName = "";
		std::string JSONfile = "";

		//Add components
		ECS::AttachComponent<Sprite>(shadowPair.x);
		ECS::AttachComponent<Transform>(shadowPair.x);
		ECS::AttachComponent<PhysicsBody>(shadowPair.x);
		ECS::AttachComponent<Trigger*>(shadowPair.x);
		ECS::AttachComponent<ShadowLoop>(shadowPair.x);
		ECS::AttachComponent<AnimationController>(shadowPair.x);

		if (ranged == true)
		{
			//Sets up ranged shadow components
			fileName = "spritesheets/ShadowSpritesheet.png";
			JSONfile = "Shadow.json";

			ECS::GetComponent<ShadowLoop>(shadowPair.x).InitRangedShadow(fileName, JSONfile, width, height, &ECS::GetComponent<Sprite>(shadowPair.x),
				&ECS::GetComponent<AnimationController>(shadowPair.x));
		}
		else
		{
			//sets up melee shadow components
			fileName = "spritesheets/Squid.png";
			JSONfile = "SquidMovement.json";
			//void InitMeleeShadow(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, AnimationController* controller);
			ECS::GetComponent<ShadowLoop>(shadowPair.x).InitMeleeShadow(fileName, JSONfile, width, height, &ECS::GetComponent<Sprite>(shadowPair.x),
				&ECS::GetComponent<AnimationController>(shadowPair.x));
		}

		ECS::GetComponent<Transform>(shadowPair.x).SetPosition(vec3(30.f, -20.f, 2.f));

		ECS::GetComponent<Trigger*>(shadowPair.x) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(shadowPair.x)->SetTriggerEntity(shadowPair.x);
		ECS::GetComponent<Trigger*>(shadowPair.x)->AddTargetEntity(MainEntities::MainPlayer());


		ECS::GetComponent<ShadowLoop>(shadowPair.x).SetMovementBoundaries(min, max);
		ECS::GetComponent<ShadowLoop>(shadowPair.x).SetPatrolVelocity(patrolVel);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(shadowPair.x);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(xPos, yPos);

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(shadowPair.x, tempBody, width, height, vec2(0.f, 0.f), true, TRIGGER, PLAYER);

		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);

	}

	//Shadow area trigger 1 entity
	{
		shadowPair.y = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(shadowPair.y);
		ECS::AttachComponent<Transform>(shadowPair.y);
		ECS::AttachComponent<PhysicsBody>(shadowPair.y);
		ECS::AttachComponent<Trigger*>(shadowPair.y);
		ECS::AttachComponent<Kinematics>(shadowPair.y);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(shadowPair.y).LoadSprite(fileName, 200, 50);

		ECS::GetComponent<Trigger*>(shadowPair.y) = new ShadowAreaTrigger();
		ECS::GetComponent<Trigger*>(shadowPair.y)->SetTriggerEntity(shadowPair.y);
		ECS::GetComponent<Trigger*>(shadowPair.y)->AddTargetEntity(shadowPair.x);

		ECS::GetComponent<Kinematics>(shadowPair.y).SetChild(shadowPair.y);
		ECS::GetComponent<Kinematics>(shadowPair.y).SetParent(shadowPair.x);
		ECS::GetComponent<Kinematics>(shadowPair.y).SetOffset(xOffset, yOffset);

		ECS::GetComponent<Sprite>(shadowPair.y).SetTransparency(0.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(shadowPair.y);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(shadowPair.y);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		//tempDef.position.Set(float32(240.f), float32(40.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(shadowPair.y, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	return shadowPair;
}

b2Vec2 Scene::SpawnMovingPlatform(float xPos, float yPos, float min, float max, int type, float width, float height, std::string sprite)
{
	//stores the entity numbers of the platform and its trigger 
	b2Vec2 platform;

	//Creates a moving platform 
	{
		//Creates entity 
		platform.x = ECS::CreateEntity();

		//Add components 
		ECS::AttachComponent<Sprite>(platform.x);
		ECS::AttachComponent<Transform>(platform.x);
		ECS::AttachComponent<PhysicsBody>(platform.x);
		ECS::AttachComponent<MovingPlatform>(platform.x);

		//Sets up components 
		ECS::GetComponent<Sprite>(platform.x).LoadSprite(sprite, width, height);
		ECS::GetComponent<Transform>(platform.x).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<MovingPlatform>(platform.x).SetType(type);
		ECS::GetComponent<MovingPlatform>(platform.x).SetMovementBoundaries(min, max);

		auto& tempSpr = ECS::GetComponent<Sprite>(platform.x);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(platform.x);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_kinematicBody;
		tempDef.position.Set(xPos, yPos);

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(platform.x, tempBody, width,
			height, vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Creates a trigger for the moving platform 
	{
		//Creates entity 
		platform.y = ECS::CreateEntity();

		//Add components 
		ECS::AttachComponent<Trigger*>(platform.y);
		ECS::AttachComponent<Transform>(platform.y);
		ECS::AttachComponent<PhysicsBody>(platform.y);
		ECS::AttachComponent<Kinematics>(platform.y);

		//Sets up components 
		ECS::GetComponent<Transform>(platform.y).SetPosition(vec3(30.f, -20.f, 2.f));

		ECS::GetComponent<Kinematics>(platform.y).SetParent(platform.x);
		ECS::GetComponent<Kinematics>(platform.y).SetChild(platform.y);

		if (type == 0)
		{
			ECS::GetComponent<Trigger*>(platform.y) = new MovingTrigger;
		}
		else
		{
			ECS::GetComponent<Trigger*>(platform.y) = new VerticalPlatformTrigger();
			ECS::GetComponent<Trigger*>(platform.y)->AddTargetEntity(platform.x);
			ECS::GetComponent<Kinematics>(platform.y).SetOffset(0.f, 1.f);
			width -= 2;
		}

		ECS::GetComponent<Trigger*>(platform.y)->SetTriggerEntity(platform.y);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(platform.y);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(platform.y, tempBody, width,
			height, vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//{ 
	//	//Creates entity 
	//	auto entity = ECS::CreateEntity(); 

	//	//Add components 
	//	ECS::AttachComponent<Transform>(entity); 
	//	ECS::AttachComponent<PhysicsBody>(entity); 
	//	ECS::AttachComponent<Trigger*>(entity); 
	//	ECS::AttachComponent<Kinematics>(entity); 

	//	//Sets up components 
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f)); 

	//	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity); 


	//	ECS::GetComponent<Kinematics>(entity).SetParent(vertMovingPlat); 
	//	ECS::GetComponent<Kinematics>(entity).SetChild(entity); 


	//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity); 

	//	float shrinkX = 0.f; 
	//	float shrinkY = 0.f; 
	//	b2Body* tempBody; 
	//	b2BodyDef tempDef; 
	//	tempDef.type = b2_staticBody; 
	//	tempDef.position.Set(float32(1504.f), float32(428.f)); 

	//	tempBody = m_physicsWorld->CreateBody(&tempDef); 

	//	tempPhsBody = PhysicsBody(entity, tempBody, float(94 - shrinkX), 
	//		float(8 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER); 
	//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f)); 
	//} 

	//returning the entity numbers 
	return platform;
}

int Scene::SpawnBulletWall(float xPos, float yPos, float width, float height)
{
	//Creates entity 
	auto entity = ECS::CreateEntity();

	//Add components 
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	//Sets up components 
	std::string fileName = "BulletNode.png";

	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 3.f));

	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_staticBody;
	tempDef.position.Set(xPos, yPos);

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, width, height, vec2(0.f, 0.f), false, ENVIRONMENT, PLAYER | TRIGGER);
	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	tempPhsBody.SetGravityScale(0.f);

	return entity;
}

void Scene::SpawnMainPlayer()
{
	auto entity = ECS::CreateEntity();
	ECS::SetIsMainPlayer(entity, true);

	//Add components
	ECS::AttachComponent<Player>(entity);
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<AnimationController>(entity);
	ECS::AttachComponent<PlayerMechanics>(entity);
	ECS::AttachComponent<CoolDown>(entity); //anger
	ECS::AttachComponent<BossLevel>(entity); //anger
	ECS::AttachComponent<MovingClass>(entity);//anger

	//Sets up the components
	std::string fileName = "spritesheets/abigailSpritesheet.png";
	std::string animations = "abigailAnimations.json";

	ECS::GetComponent<Player>(entity).InitPlayer(fileName, animations, 25, 25, &ECS::GetComponent<Sprite>(entity),
		&ECS::GetComponent<AnimationController>(entity), &ECS::GetComponent<Transform>(entity));

	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 30.f, 5.f));

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 8.f;
	float shrinkY = 3.f;

	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_dynamicBody;
	tempDef.position.Set(float32(-450.f), float32(30.f));

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, PLAYER, ENEMY | OBJECTS | PICKUP | TRIGGER | SNAIL, 0.f, 1.f);

	tempPhsBody.SetRotationAngleDeg(0.f);
	tempPhsBody.SetFixedRotation(true);
	tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
	tempPhsBody.SetGravityScale(0.75);
}

void Scene::SpawnMainCamera(float width, float height)
{
	float aspectRatio = width / height;

	//Creates Camera entity
	auto entity = ECS::CreateEntity();
	ECS::SetIsMainCamera(entity, true);

	//Creates new orthographic camera
	ECS::AttachComponent<Camera>(entity);
	ECS::AttachComponent<HorizontalScroll>(entity);
	ECS::AttachComponent<VerticalScroll>(entity);

	vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f);
	ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
	ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
	ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(width), float(height)));
	ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

	//Attaches the camera to vert and horiz scrolls
	ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
}

void Scene::SpawnSpike(float xPos, float yPos, float width, float height)
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
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, width, height);
	ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
	ECS::GetComponent<Trigger*>(entity) = new SpikeTrigger();
	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 2.f;
	float shrinkY = 2.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_staticBody;
	tempDef.position.Set(float32(xPos), float32(yPos));

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float((tempSpr.GetWidth() - shrinkY) / 2.f), vec2(0.f, 0.f), true, TRIGGER, PLAYER, 0.3f);
}

int Scene::SpawnOrb(float xPos, float yPos, float width, float height)
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
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, width, height);
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
	tempDef.position.Set(xPos, yPos);

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	return entity;
}

vec4 Scene::GetClearColor() const
{
	return m_clearColor;
}

void Scene::SetClearColor(vec4 clearColor)
{
	m_clearColor = clearColor;
}

std::string Scene::GetName() const
{
	return m_name;
}

void Scene::SetName(std::string name)
{
	m_name = name;
}

b2Vec2 Scene::GetGravity() const
{
	return m_gravity;
}

void Scene::SetGravity(b2Vec2 grav)
{
	m_gravity = grav;
}

b2World & Scene::GetPhysicsWorld()
{
	return *m_physicsWorld;
}

void Scene::SetWindowSize(float windowWidth, float windowHeight)
{
	//TODO: Find new way to get the main camera
	auto& tempCam = m_sceneReg->get<Camera>(MainEntities::MainCamera());
	
	tempCam.SetWindowSize(vec2(windowWidth, windowHeight));
	tempCam.Orthographic(float(windowWidth / windowHeight), tempCam.GetOrthoSize().x, tempCam.GetOrthoSize().y,
															tempCam.GetOrthoSize().z, tempCam.GetOrthoSize().w,
															tempCam.GetNear(), tempCam.GetFar());
}
