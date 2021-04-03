#include "DenialLevel.h"
#include "Utilities.h"
//#include "ToneFire.h"


DenialLevel::DenialLevel(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(0.f, -98.f);
	m_physicsWorld->SetGravity(m_gravity);
	m_physicsWorld->SetContactListener(&listener);
}

void DenialLevel::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register
	m_sceneReg = new entt::registry;

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;
	wWidth = windowWidth;
	wHeight = windowHeight;

	SpawnMainCamera(windowWidth, windowHeight);

	//music created and looped 
	{
		//ToneFire::CoreSound BGM("denialBGM.wav", FMOD_LOOP_NORMAL); 
		//ToneFire::CoreSound test2{ "TURKEYSONG8000.mp3",false,false,true };
		//
		////BGM.Play(); 
		//test2.Play();

		//test2.SetVolume(1.0f);
	}

	//Abigail entity
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
		//tempDef.position.Set(float32(0.f), float32(30.f));
		tempDef.position.Set(float32(744.5), float32(187.5));
		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, PLAYER, ENEMY | OBJECTS | PICKUP | TRIGGER | SNAIL, 0.f, 1.f);
		//tempPhsBody = PhysicsBody(entity, tempBody, float((tempSpr.GetHeight() - shrinkY) / 2.f), vec2(0.f, 0.f), false, PLAYER, ENEMY | OBJECTS | PICKUP | TRIGGER | SNAIL, 0.5f, 3.f);

		tempPhsBody.SetRotationAngleDeg(0.f);
		tempPhsBody.SetFixedRotation(true);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
		tempPhsBody.SetGravityScale(0.75);
	}

	// STATIC PLATFORMS \\

	//Platform A (bottom 0-30)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformA.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 480, 16);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(240.f), float32(8.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform B (bottom 30-50)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformB.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 320, 16);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(640.f), float32(8.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform C (Wall)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformC.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 160);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(824.f), float32(80.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform D (raised platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformD.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 128, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(736.f), float32(32.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempSpr.SetTransparency(0.f);
	}

	//Platform E (raised platform stacked)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformE.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(776.f), float32(64.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempSpr.SetTransparency(0.f);
	}

	//Platform F (floating platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformF.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 144, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(648.f), float32(104.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform G (floating platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformG.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(512.f), float32(104.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform H (floating platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformH.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(440.f), float32(104.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform I (floating platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformI.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 16);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(352.f), float32(104.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform J (floating platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformJ.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 48);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(320.f), float32(120.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform K (46-76 elevated ground)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformK.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 480, 16);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(976.f), float32(168));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform L (76-90 elevated platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "boxSprite.jpg";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 224, 16);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1328), float32(168.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform M (elevated wall)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "boxSprite.jpg";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 144);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1464.f), float32(232));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform N (raised platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "boxSprite.jpg";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 32);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(800.f), float32(192.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform O (floating platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformO.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1032.f), float32(264.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform P (79-109 highest ground platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "boxSprite.jpg";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 480, 32);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1504), float32(320.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform Q (109-130 highest ground platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "boxSprite.jpg";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 336, 32);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1912.f), float32(320.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform R (floating platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformR.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 64, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1536), float32(360.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform S (floating platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 80, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1800.f), float32(246.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform T (floating platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformT.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 128, 16);
		//ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1968), float32(456.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform U (floating platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platformU.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 208, 16);
		//ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1928.f), float32(616.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}


	// SPECIAL PLATFORMS (MOVING/CRUMBLING) \\

	//Platform M1 (moving platform 1) *currently in leftmost position*
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		movingPlat = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "movingplatform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 80, 8);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		//tempDef.type = b2_dynamicBody;
		tempDef.type = b2_staticBody;
		float platX = 392.f;
		float platY = 168.f;
		tempDef.position.Set(float32(392.f), float32(148.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetFixedRotation(true);
		tempPhsBody.SetGravityScale(0.f);
	}


	//Trigger M1 (moving platform 1 trigger) *currently in leftmost position*
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

		float shrinkX = 0.f;
		float shrinkY = 0.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		//tempDef.type = b2_dynamicBody;
		tempDef.type = b2_staticBody;

		tempDef.position.Set(float32(392.f), float32(148.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(16 * 5 - shrinkX),
			float(16 * 0.5 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetFixedRotation(true);
		tempPhsBody.SetGravityScale(0.f);
	}

	//Platform M2 (crumbling platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cPlatforms[0] = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<CrumblingSequence>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components

		std::string fileName = "spritesheets/crumblingPlatform.png";
		std::string JSONFile = "crumble.json";

		ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));


		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 32);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(872.f), float32(224.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Trigger M2 (crumbling trigger)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cTriggers[0] = entity;

		//Add components
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[0]);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(872.f), float32(224.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Platform M3 (crumbling platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cPlatforms[1] = entity;

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

		ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(952.f), float32(240.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Trigger M3 (crumbling trigger)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cTriggers[1] = entity;

		//Add components
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[1]);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(952.f), float32(240.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Platform M4 (crumbling platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cPlatforms[2] = entity;

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
		ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1112.f), float32(272.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Trigger M4 (crumbling trigger)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cTriggers[2] = entity;

		//Add components
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[2]);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1112.f), float32(272.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Platform M5 (crumbling platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cPlatforms[3] = entity;

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
		ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1192.f), float32(304.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Trigger M5 (crumbling trigger)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cTriggers[3] = entity;

		//Add components
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[3]);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1192.f), float32(304.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Platform M6 (crumbling platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cPlatforms[4] = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<CrumblingSequence>(entity);

		//Sets up components
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string fileName = "spritesheets/crumblingPlatform.png";
		std::string JSONFile = "crumble.json";

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1624.f), float32(384.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Trigger M6 (crumbling trigger)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cTriggers[4] = entity;

		//Add components
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[4]);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1624.f), float32(384.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(16 * 2 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Platform M7 (crumbling platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cPlatforms[5] = entity;

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
		ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1704.f), float32(416.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Trigger M7 (crumbling trigger)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cTriggers[5] = entity;

		//Add components
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[5]);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1704.f), float32(416.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Platform M8 (moving platform) *currently in lowest position of path*
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		vertMovingPlat = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 96, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1504.f), float32(408.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Platform M9 (crumbling platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cPlatforms[6] = entity;

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
		ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1624.f), float32(592.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Trigger M9 (crumbling trigger)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cTriggers[6] = entity;

		//Add components
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[6]);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1624.f), float32(592.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}



	//Platform M10 (crumbling platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cPlatforms[7] = entity;

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
		ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1736.f), float32(592.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Trigger M10 (crumbling trigger)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cTriggers[7] = entity;

		//Add components
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[7]);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1736.f), float32(592));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
			float(32 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	// SHADOWS \\

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
		std::string fileName = "spritesheets/ShadowSpritesheet.png";
		std::string JSONfile = "Shadow.json";

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);

		ECS::GetComponent<ShadowLoop>(entity).InitRangedShadow(fileName, JSONfile, 32, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));

		ECS::GetComponent<ShadowLoop>(entity).SetMovementBoundaries(0, 272);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(248.f), float32(88.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(32), float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);

		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);

	}
	//Shadow area trigger 1 entity
	{
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 480, 96);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(3510.f, 200.f, 0.1));

		ECS::GetComponent<Trigger*>(entity) = new ShadowAreaTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(shadows[0]);
		ECS::GetComponent<Trigger*>(entity)->SetShadowZone(1);

		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(240.f), float32(40.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}



	//E2 (enemy 2)
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
		std::string fileName = "spritesheets/ShadowSpritesheet.png";
		std::string JSONfile = "Shadow.json";

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);

		ECS::GetComponent<ShadowLoop>(entity).InitRangedShadow(fileName, JSONfile, 32, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));
		ECS::GetComponent<ShadowLoop>(entity).SetMovementBoundaries(322, 768);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(545), float32(216));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(32), float(32), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}

	//E3 (enemy 3)
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
		std::string fileName = "spritesheets/ShadowSpritesheet.png";
		std::string JSONfile = "Shadow.json";

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);

		ECS::GetComponent<ShadowLoop>(entity).InitRangedShadow(fileName, JSONfile, 32, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));
		ECS::GetComponent<ShadowLoop>(entity).SetMovementBoundaries(794, 1272);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(1033), float32(430));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(32), float(32), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}

	//E4 (enemy 4)
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
		std::string fileName = "spritesheets/ShadowSpritesheet.png";
		std::string JSONfile = "Shadow.json";

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);

		ECS::GetComponent<ShadowLoop>(entity).InitRangedShadow(fileName, JSONfile, 32, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));
		ECS::GetComponent<ShadowLoop>(entity).SetMovementBoundaries(1652, 1852);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(1752.f), float32(536.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(32), float(32), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}

	// STATIC BACKGROUND TILES \\
	
	{
		// TILE 0-0
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial0-0.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-128.f, -176.f, 2.f));
		}

		// TILE 1-0
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial1-0.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(128.f, -176.f, 2.f));
		}

		// TILE 2-0
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial2-0.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(384.f, -176.f, 2.f));
		}

		// TILE 3-0
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial3-0.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(640.f, -176.f, 2.f));
		}

		// TILE 4-0
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial4-0.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(896, -176, 2.f));
		}

		// TILE 5-0
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial5-0.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1152.f, -176, 2.f));
		}

		// TILE 6-0
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial6-0.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1280.f, -176, 2.f));
		}

		// TILE 7-0
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial7-0.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1536.f, -176, 2.f));
		}

		// TILE 0-1
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial0-1.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-128, 80.f, 2.f));
		}

		// TILE 1-1
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial1-1.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(128.f, 80.f, 2.f));
		}

		// TILE 2-1
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial2-1.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(384.f, 80.f, 2.f));
		}

		// TILE 3-1
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial3-1.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(640.f, 80, 2.f));
		}

		// TILE 4-1
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial4-1.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(896.f, 80.f, 2.f));
		}

		// TILE 5-1
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial5-1.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1152.f, 80.f, 2.f));
		}

		// TILE 6-1
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial6-1.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1280.f, 80.f, 2.f));
		}

		// TILE 7-1
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial7-1.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1536.f, 80.f, 2.f));
		}

		// TILE 8-1
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial8-1.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1792.f, 80.f, 2.f));
		}

		// TILE 9-1
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial9-1.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(2048.f, 50, 2.f));
		}

		// TILE 0-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial0-2.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-128.f, 336.f, 2.f));
		}

		// TILE 1-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial1-2.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(128.f, 336.f, 2.f));
		}

		// TILE 2-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial2-2.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(384.f, 336.f, 2.f));
		}

		// TILE 3-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial3-2.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(640.f, 336.f, 2.f));
		}

		// TILE 4-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial4-2.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(896.f, 336.f, 2.f));
		}

		// TILE 5-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial5-2.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1152.f, 336, 2.f));
		}

		// TILE 6-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial6-2.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1280.f, 336.f, 2.f));
		}

		// TILE 7-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial7-2.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1536.f, 336.f, 2.f));
		}

		// TILE 8-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial8-2.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1792.f, 336.f, 2.f));
		}

		// TILE 9-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial9-2.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(2048.f, 336, 2.f));
		}

		// TILE 6-3
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial6-3.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1280.f, 592.f, 2.f));
		}

		// TILE 7-3
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial7-3.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1536.f, 592.f, 2.f));
		}

		// TILE 8-3
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial8-3.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1792.f, 592.f, 2.f));
		}

		// TILE 9-3
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial9-3.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(2048.f, 592.f, 2.f));
		}

		// TILE 6-4
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial6-4.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1280.f, 848.f, 2.f));
		}

		// TILE 7-4
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial7-4.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1536.f, 848.f, 2.f));
		}

		// TILE 8-4
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial8-4.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1792, 848.f, 2.f));
		}

		// TILE 9-4
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial9-4.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(2048.f, 848.f, 2.f));
		}
	}

	//SPECIAL TRIGGERS \\

	//Switch
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);


		//Sets up components
		std::string fileName = "nachoFish.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 48);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(float32(1952.f), float32(488.f), 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);

	}

	//Exit
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);


		//Sets up components
		std::string fileName = "nachoFish.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 48);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(float32(1952.f), float32(632.f), 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);

	}

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void DenialLevel::Update()
{
	auto& playerBody = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& player = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& moveTrig = ECS::GetComponent<MovingClass>(MainEntities::MainPlayer());
	auto& kinTrig = ECS::GetComponent<Kinematics>(kinTrigger);
	auto& pMechanics = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	auto& sprite = ECS::GetComponent<Sprite>(MainEntities::MainPlayer());

	kinTrig.UpdatePosition();
	pMechanics.RunKnockBackTime();

	if (pMechanics.GetCanMove() == true)
	{
		player.Update();
	}

	//fmod.Update();

	for (int i = 0; i <= 7; i++)
	{
		ECS::GetComponent<CrumblingSequence>(cPlatforms[i]).Crumble(cPlatforms[i]);
		CrumblingPlatforms(cPlatforms[i]);
	}

	pMechanics.RunShadowTime();

	for (int i = 0; i <= 3; i++)
	{
		ActivateShadow(shadows[i]);
	}

	std::cout << ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x << std::endl;


	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	sprite.SetTransparency(1.f);
	MovePlatform();
}



void DenialLevel::KeyboardHold()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	float speed = 1.f;
	b2Vec2 vel = b2Vec2(0.f, 0.f);
	vec3 velocity = vec3(0.f, 0.f, 0.f);

}

void DenialLevel::MovePlatform()
{
	auto& moveTrig = ECS::GetComponent<MovingClass>(player);
	auto& playerBody = ECS::GetComponent<PhysicsBody>(player);
	auto& plat = ECS::GetComponent<PhysicsBody>(movingPlat);
	auto& vert = ECS::GetComponent<PhysicsBody>(vertMovingPlat);
	float platX = plat.GetPosition().x;
	float platY = plat.GetPosition().y;
	int playerX = playerBody.GetPosition().x;
	int playerY = playerBody.GetPosition().y;

	static bool vertSwitch = false;

	if (vert.GetPosition().y <= 408)
	{
		vertSwitch = false;
	}
	if (vert.GetPosition().y >= 808)
	{
		vertSwitch = true;
	}

	if (vertSwitch == false)
	{
		vert.SetPosition(b2Vec2(vert.GetPosition().x, vert.GetPosition().y + 0.5));
	}
	else
	{
		vert.SetPosition(b2Vec2(vert.GetPosition().x, vert.GetPosition().y - 0.5));
	}

	if (platX > 680)
	{
		switchDir = true;

	}
	if (platX < 380)
	{
		switchDir = false;

	}
	if (switchDir == false)
	{
		platX += 0.5;
		plat.SetPosition(b2Vec2(platX, platY));
		moveTrig.SetRight(true);
		moveTrig.SetLeft(false);
	}
	else if (switchDir == true)
	{
		platX -= 0.5;
		plat.SetPosition(b2Vec2(platX, platY));
		moveTrig.SetLeft(true);
		moveTrig.SetRight(false);
	}

}

void DenialLevel::SpawnBullet(int shadow)
{
	auto& shadowBody = ECS::GetComponent<PhysicsBody>(shadow);
	float tempX = shadowBody.GetBody()->GetPosition().x; //directly subbing in the GetBody line throws an error
	float tempY = shadowBody.GetBody()->GetPosition().y;
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

	ShootBullet(entity);
}

void DenialLevel::ShootBullet(int bullet)
{
	ECS::GetComponent<PhysicsBody>(bullet).GetBody()->SetType(b2BodyType::b2_dynamicBody);

	b2Vec2 angle = CalculateAngle(MainEntities::MainPlayer(), bullet);

	float dirAngle = atan(angle.x / angle.y) * (180 / PI);

	ECS::GetComponent<PhysicsBody>(bullet).SetRotationAngleDeg(dirAngle * -1);
	ECS::GetComponent<PhysicsBody>(bullet).GetBody()->SetLinearVelocity(b2Vec2(angle.x * 100000000, angle.y * 100000000));
}

void DenialLevel::ActivateShadow(int shadow)
{
	//Checks to see if the appropriate amount of seconds of passed between now and the last shot. 
	//If so, a bullet is fired from a shadow determined by the player's location.
	auto& pMechanics = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	auto& shade = ECS::GetComponent<ShadowLoop>(shadow);

	shade.ShadowRoutine(shadow);

	if (pMechanics.GetFiring() == true)
	{
		if (pMechanics.GetShadowLoc() == 1)
		{
			SpawnBullet(shadow);
		}
		//add additional else if statements for additional shadows
	}
}

b2Vec2 DenialLevel::CalculateAngle(int entityOne, int entityTwo)
{
	float deltaX = 0, deltaY = 0;
	deltaX = ECS::GetComponent<PhysicsBody>(entityOne).GetBody()->GetPosition().x - ECS::GetComponent<PhysicsBody>(entityTwo).GetBody()->GetPosition().x;
	deltaY = ECS::GetComponent<PhysicsBody>(entityOne).GetBody()->GetPosition().y - ECS::GetComponent<PhysicsBody>(entityTwo).GetBody()->GetPosition().y;

	return b2Vec2(deltaX, deltaY);
}


void DenialLevel::CrumblingPlatforms(int entity)
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


void DenialLevel::KeyboardUp()
{
}

void DenialLevel::KeyboardDown()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	float speed = 1.f;
	b2Vec2 vel = b2Vec2(0.f, 0.f);

	playerVel = player.GetVelocity();
	playerPos = player.GetPosition();

	if (Input::GetKeyDown(Key::M))
	{
		std::cout << "X Pos: " << playerPos.x << std::endl;
		std::cout << "Y Pos: " << playerPos.y << std::endl << std::endl;
	}
}