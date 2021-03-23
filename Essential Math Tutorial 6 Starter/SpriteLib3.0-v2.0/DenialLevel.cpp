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
		//vec4 temp = vec4(-100.f, 100.f, -100.f, 100.f);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		//Attaches the camera to vert and horiz scrolls
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	}

	//music created and looped 
	{		
		//BGM.Play(); 
		//denialBGM.Play();

		//denialBGM.SetVolume(4.5);
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
		tempDef.position.Set(float32(-450.f), float32(30.f));
		//tempDef.position.Set(float32(744.5), float32(187.5));
		//tempDef.position.Set(float32(1550), float32(447));
		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, PLAYER, ENEMY | OBJECTS | PICKUP | TRIGGER | SNAIL, 0.f, 1.f);
		//tempPhsBody = PhysicsBody(entity, tempBody, float((tempSpr.GetHeight() - shrinkY) / 2.f), vec2(0.f, 0.f), false, PLAYER, ENEMY | OBJECTS | PICKUP | TRIGGER | SNAIL, 0.5f, 3.f);

		tempPhsBody.SetRotationAngleDeg(0.f);
		tempPhsBody.SetFixedRotation(true);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
		tempPhsBody.SetGravityScale(0.75);
	}

	// STATIC PLATFORMS \\

	Scene::SpawnPlatform(-20.f, 8.f, 1000.f, 16.f, "platformA.png", 0.f);
	////Platform A (bottom 0-30)
	//{
	//	//Creates entity
	//	auto entity = ECS::CreateEntity();

	//	//Add components
	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);
	//	ECS::AttachComponent<PhysicsBody>(entity);

	//	//Sets up components
	//	std::string fileName = "platformA.png";
	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 1000, 16);
	//	ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

	//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	//	float shrinkX = 0.f;
	//	float shrinkY = 0.f;
	//	b2Body* tempBody;
	//	b2BodyDef tempDef;
	//	tempDef.type = b2_staticBody;
	//	tempDef.position.Set(float32(-20), float32(8.f));

	//	tempBody = m_physicsWorld->CreateBody(&tempDef);

	//	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
	//		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
	//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	//}

	//Platform A2
	{
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
			tempDef.position.Set(float32(-510), float32(240.f));

			tempBody = m_physicsWorld->CreateBody(&tempDef);

			tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
				float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
			tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
			tempPhsBody.SetRotationAngleDeg(90.f);
		}
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
		tempDef.position.Set(float32(1800.f), float32(446.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
		tempDef.type = b2_kinematicBody;

		float platX = 392.f;
		float platY = 168.f;
		tempDef.position.Set(float32(392.f), float32(148.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
		//ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);

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
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(32 - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(32 - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(32 - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
			float(32 - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
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
	cPlatforms[5] = Scene::SpawnCrumblingPlatform(1704.f, 416.f);

	//{
	//	//Creates entity
	//	auto entity = ECS::CreateEntity();
	//	cPlatforms[5] = entity;

	//	//Add components
	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);
	//	ECS::AttachComponent<PhysicsBody>(entity);
	//	ECS::AttachComponent<CrumblingSequence>(entity);
	//	ECS::AttachComponent<AnimationController>(entity);

	//	//Sets up components
	//	std::string fileName = "spritesheets/crumblingPlatform.png";
	//	std::string JSONFile = "crumble.json";

	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

	//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
	//	ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 48, 32, &ECS::GetComponent<Sprite>(entity),
	//		&ECS::GetComponent<AnimationController>(entity));

	//	float shrinkX = 0.f;
	//	float shrinkY = 0.f;
	//	b2Body* tempBody;
	//	b2BodyDef tempDef;
	//	tempDef.type = b2_staticBody;
	//	tempDef.position.Set(float32(1704.f), float32(416.f));

	//	tempBody = m_physicsWorld->CreateBody(&tempDef);

	//	tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
	//		float(32 - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
	//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	//}

	////Trigger M7 (crumbling trigger)
	//{
	//	//Creates entity
	//	auto entity = ECS::CreateEntity();
	//	cTriggers[5] = entity;

	//	//Add components
	//	ECS::AttachComponent<Transform>(entity);
	//	ECS::AttachComponent<PhysicsBody>(entity);
	//	ECS::AttachComponent<Trigger*>(entity);

	//	//Sets up components
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
	//	ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
	//	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
	//	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[5]);

	//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	//	float shrinkX = 0.f;
	//	float shrinkY = 0.f;
	//	b2Body* tempBody;
	//	b2BodyDef tempDef;
	//	tempDef.type = b2_staticBody;
	//	tempDef.position.Set(float32(1704.f), float32(416.f));

	//	tempBody = m_physicsWorld->CreateBody(&tempDef);

	//	tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
	//		float(32 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
	//	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	//}

	//Platform M8 (moving platform) *currently in lowest position of path*
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		vertMovingPlat = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<MovingPlatform>(entity);

		//Sets up components
		std::string fileName = "movingplatform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 96, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		ECS::GetComponent<MovingPlatform>(entity).SetMovementBoundaries(408.f, 588.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_kinematicBody;
		tempDef.position.Set(float32(1504.f), float32(408.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}

	//Trigger M8 (moving trigger)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		vertPlatTrigger = entity;

		//Add components
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<Kinematics>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new VerticalPlatformTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(vertMovingPlat);

		ECS::GetComponent<Kinematics>(entity).SetParent(vertMovingPlat);
		ECS::GetComponent<Kinematics>(entity).SetChild(entity);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0.f, 5.f);

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1504.f), float32(428.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(94 - shrinkX),
			float(8 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}


	//Creates line of crumbling platforms
	float crumblingX = 1430.f;

	for (int i = 0; i <= 11; i++)
	{
		{
			//Creates entity
			auto entity = ECS::CreateEntity();
			cPlatforms[i + 6] = entity;

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
			tempDef.position.Set(float32(crumblingX), float32(580.5));

			tempBody = m_physicsWorld->CreateBody(&tempDef);

			tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
				float(32 - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | TRIGGER);
			tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		}
		//creates associated destroy trigger
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Transform>(entity);
			ECS::AttachComponent<PhysicsBody>(entity);
			ECS::AttachComponent<Trigger*>(entity);

			//Sets up components
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
			ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
			ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
			ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[i + 6]);

			auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

			float shrinkX = 0.f;
			float shrinkY = 0.f;
			b2Body* tempBody;
			b2BodyDef tempDef;
			tempDef.type = b2_staticBody;
			tempDef.position.Set(float32(crumblingX), float32(580.5));

			tempBody = m_physicsWorld->CreateBody(&tempDef);

			tempPhsBody = PhysicsBody(entity, tempBody, float(48 - shrinkX),
				float(32 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
			tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		}
		crumblingX -= 48;
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
		ECS::GetComponent<ShadowLoop>(entity).SetPatrolVelocity(b2Vec2(30.f, 0.f));

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
		sZones[0] = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<Kinematics>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 200, 50);

		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(shadows[0], shadows[0] - 50, 0.f));

		ECS::GetComponent<Trigger*>(entity) = new ShadowAreaTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(shadows[0]);

		ECS::GetComponent<Kinematics>(entity).SetChild(sZones[0]);
		ECS::GetComponent<Kinematics>(entity).SetParent(shadows[0]);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0, -50);

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
		ECS::GetComponent<ShadowLoop>(entity).SetMovementBoundaries(438, 698);
		ECS::GetComponent<ShadowLoop>(entity).SetPatrolVelocity(b2Vec2(30.f, 0.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(545), float32(216));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(32), float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}

	//Shadow area trigger 2 entity
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 200, 50);

		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(shadows[0], shadows[0] - 50, 0.f));

		ECS::GetComponent<Trigger*>(entity) = new ShadowAreaTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(shadows[1]);

		ECS::GetComponent<Kinematics>(entity).SetChild(sZones[1]);
		ECS::GetComponent<Kinematics>(entity).SetParent(shadows[1]);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0, -50);

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
		ECS::GetComponent<ShadowLoop>(entity).SetMovementBoundaries(794, 1252);
		ECS::GetComponent<ShadowLoop>(entity).SetPatrolVelocity(b2Vec2(50.f, 10.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(1033), float32(380));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(32), float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}

	//Shadow area trigger 3 entity
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 200, 50);

		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(shadows[0], shadows[0] - 50, 0.f));

		ECS::GetComponent<Trigger*>(entity) = new ShadowAreaTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(shadows[2]);

		ECS::GetComponent<Kinematics>(entity).SetChild(sZones[2]);
		ECS::GetComponent<Kinematics>(entity).SetParent(shadows[2]);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0, -50);

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
		ECS::GetComponent<ShadowLoop>(entity).SetPatrolVelocity(b2Vec2(30.f, 15.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(1752.f), float32(536.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(32), float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}

	//Shadow area trigger 4 entity
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
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 200, 50);

		//ECS::GetComponent<Transform>(entity).SetPosition(vec3(shadows[0], shadows[0] - 50, 0.f));

		ECS::GetComponent<Trigger*>(entity) = new ShadowAreaTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(shadows[3]);

		ECS::GetComponent<Kinematics>(entity).SetChild(sZones[3]);
		ECS::GetComponent<Kinematics>(entity).SetParent(shadows[3]);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0, -50);

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

	//E5 (enemy 5)
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
		std::string fileName = "spritesheets/ShadowSpritesheet.png";
		std::string JSONfile = "Shadow.json";

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);

		ECS::GetComponent<ShadowLoop>(entity).InitRangedShadow(fileName, JSONfile, 32, 32, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity));
		ECS::GetComponent<ShadowLoop>(entity).SetMovementBoundaries(950, 1286);
		ECS::GetComponent<ShadowLoop>(entity).SetPatrolVelocity(b2Vec2(20.f, 0.f));

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(1118.f), float32(670.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(32), float(32), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}

	//Shadow area trigger 4 entity
	{
		auto entity = ECS::CreateEntity();
		sZones[4] = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<Kinematics>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 200, 50);

		ECS::GetComponent<Trigger*>(entity) = new ShadowAreaTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(shadows[4]);

		ECS::GetComponent<Kinematics>(entity).SetChild(sZones[4]);
		ECS::GetComponent<Kinematics>(entity).SetParent(shadows[4]);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0, -50);

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

	//Bullet wall
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		bulletWalls[0] = entity;

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
		tempDef.position.Set(float32(-260.f), float32(80.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(16.f), float(16.f), vec2(0.f, 0.f), false, ENVIRONMENT, PLAYER | TRIGGER);
			tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
			tempPhsBody.SetGravityScale(0.f);
	}

	//Bullet wall
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		bulletWalls[1] = entity;

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
		tempDef.position.Set(float32(512.f), float32(87.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(16.f), float(16.f), vec2(0.f, 0.f), false, ENVIRONMENT, PLAYER | TRIGGER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}

	//Bullet wall
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		bulletWalls[2] = entity;

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
		tempDef.position.Set(float32(1286.f), float32(650.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(16.f), float(16.f), vec2(0.f, 0.f), false, ENVIRONMENT, PLAYER | TRIGGER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}

	//Bullet wall
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		bulletWalls[3] = entity;

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
		tempDef.position.Set(float32(950.f), float32(650.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(16.f), float(16.f), vec2(0.f, 0.f), false, ENVIRONMENT, PLAYER | TRIGGER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetGravityScale(0.f);
	}

<<<<<<< HEAD



=======
>>>>>>> FramerateIndependenceDay
	// STATIC BACKGROUND TILES \\
	
	{		// TILE -2-0
			Scene::SpawnTile(-640.f, -176.f, "backgrounds/denial0-0.png");

		// TILE -1-0
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial0-0.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-384.f, -176.f, 1.f));
		}

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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-128.f, -176.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(128.f, -176.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(384.f, -176.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(640.f, -176.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(896, -176.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1152.f, -176.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1408.f, -176.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1664.f, -176.f, 1.f));
		}

		//TILE -2-1
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial-2-1.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-640, 80.f, 1.f));
		}

		//TILE -1-1
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial-1-1.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-384, 80.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-128, 80.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(128.f, 80.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(384.f, 80.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(640.f, 80.f, 1.f));
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
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256,256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(896.f, 80.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1152.f, 80.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1408.f, 80.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1664.f, 80.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1920.f, 80.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(2176.f, 80.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-128.f, 336.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(128.f, 336.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(384.f, 336.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(640.f, 336.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(896.f, 336.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1152.f, 336, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1408.f, 336.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1664.f, 336.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1920.f, 336.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(2176.f, 336, 1.f));
		}

		// TILE 0-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial0-3.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(-128.f, 592.f, 1.f));
		}

		// TILE 1-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial1-3.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(128.f, 592.f, 1.f));
		}

		// TILE 2-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial2-3.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(384.f, 592.f, 1.f));
		}

		// TILE 3-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial3-3.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(640.f, 592.f, 1.f));
		}

		// TILE 4-2
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial4-3.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(896.f, 592.f, 1.f));
		}

		// TILE 5-3
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial5-3.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1152.f, 592.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1408.f, 592.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1664.f, 592.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1920.f, 592.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(2176.f, 592.f, 1.f));
		}

		// TILE 5-4
		{
			//Creates entity
			auto entity = ECS::CreateEntity();

			//Add components
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);

			//Sets up components
			std::string fileName = "backgrounds/denial5-4.png";
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 256);
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1152.f, 848.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1408.f, 848.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1664.f, 848.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(1920.f, 848.f, 1.f));
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
			ECS::GetComponent<Transform>(entity).SetPosition(vec3(2176.f, 848.f, 1.f));
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
		std::string fileName = "test.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 48);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(float32(1952.f), float32(488.f), 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);

	}

	//Exit
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shield = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<Kinematics>(entity);


		//Sets up components
		std::string fileName = "ShieldTemp.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 48);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(float32(1952.f), float32(632.f), 2.f));

		ECS::GetComponent<Kinematics>(entity).SetChild(entity);
		ECS::GetComponent<Kinematics>(entity).SetParent(MainEntities::MainPlayer());
		ECS::GetComponent<Kinematics>(entity).SetOffset(0.f, 0.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		tempSpr.SetTransparency(0.f);
	}

	BuildUI();

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void DenialLevel::Update()
{
	auto& playerBody = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& player = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& kinTrig = ECS::GetComponent<Kinematics>(kinTrigger);
	auto& pMechanics = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	auto& sprite = ECS::GetComponent<Sprite>(MainEntities::MainPlayer());

	kinTrig.UpdatePosition();
	ECS::GetComponent<Kinematics>(vertPlatTrigger).UpdatePosition();
	ECS::GetComponent<MovingPlatform>(vertMovingPlat).MovePlatform(vertMovingPlat);
	pMechanics.RunKnockBackTime();

	//ECS::GetComponent<Kinematics>(kinTrigger).UpdatePosition();

	ECS::GetComponent<Kinematics>(shield).UpdateTransform();
	/*ECS::GetComponent<Kinematics>(uiElements[0]).UpdateTransform();*/

	if (pMechanics.GetCanMove() == true)
	{
		player.Update();
	}

	fmod.Update();

	for (int i = 0; i <= 17; i++)
	{
		ECS::GetComponent<CrumblingSequence>(cPlatforms[i]).Crumble(cPlatforms[i]);
		CrumblingPlatforms(cPlatforms[i]);
	}

	for (int i = 0; i <= 4; i++)
	{
		ActivateShadow(shadows[i]);
	}

	for (int i = 0; i <= 4; i++)
	{
		ECS::GetComponent<Kinematics>(sZones[i]).UpdatePosition();
	}

	for (int i = 0; i <= 3; i++)
	{
		SpawnBullet(bulletWalls[i], 0, -13);
	}

	if (pMechanics.GetShield())
	{
		ECS::GetComponent<Sprite>(shield).SetTransparency(1.f);
	}
	else
	{
		ECS::GetComponent<Sprite>(shield).SetTransparency(0.f);
	}

	std::cout << playerBody.GetPosition().x <<  "					" << playerBody.GetPosition().y << std::endl;

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).Update();
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).Update();

	for (int i = 0; i <= 4; i++)
	{
		ECS::GetComponent<Kinematics>(uiElements[i]).UpdateUI();
	}

	sprite.SetTransparency(1.f);
	MovePlatform();
}


void DenialLevel::KeyboardHold()
{
}

void DenialLevel::MovePlatform()
{
	auto& moveTrig = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	auto& playerBody = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());

	auto& plat = ECS::GetComponent<PhysicsBody>(movingPlat);
	//auto& vert = ECS::GetComponent<PhysicsBody>(vertMovingPlat);

	float platX = plat.GetPosition().x;
	float platY = plat.GetPosition().y;

	int playerX = playerBody.GetPosition().x;
	int playerY = playerBody.GetPosition().y;

	static bool vertSwitch = false;

	/*if (vert.GetPosition().y <= 408)
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
	}*/

	if (platX > 670)
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
		//plat.SetPosition(b2Vec2(platX, platY)); 
		plat.SetVelocity(vec3(30.f, 0.f, 0.f));
		moveTrig.SetRight(true);
		moveTrig.SetLeft(false);
	}
	else if (switchDir == true)
	{
		platX -= 0.5;
		plat.SetVelocity(vec3(-30.f, 0.f, 0.f));
		//plat.SetPosition(b2Vec2(platX, platY));
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
	tempDef.type = b2_dynamicBody;
	tempDef.position.Set(tempX, tempY);

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | GROUND | ENVIRONMENT);
	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	tempPhsBody.SetGravityScale(0.f); //ensures no bullet drop and bullet reaches the player

	ShootBullet(entity);
}

void DenialLevel::SpawnBullet(int wall, float offsetX, float offsetY)
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
		
		if (wall == bulletWalls[3]) //this has to be equal to the last entry in the bulletWalls array. If it isn't, any elements after this number will not spawn bullets.
		{
			startTime = 0;
		}
	}
}

void DenialLevel::BuildUI()
{

	uiElements[0] = Scene::SpawnUIElement(-120.f, 65.f, 20, 20, "heart.png");
	uiElements[1] = Scene::SpawnUIElement(-100.f, 65.f, 20, 20, "heart.png");
	uiElements[2] = Scene::SpawnUIElement(-80.f, 65.f, 20, 20, "heart.png");
	uiElements[3] = Scene::SpawnUIElement(115.f, -60.f, 30, 30, "shieldOff.png");
	uiElements[4] = Scene::SpawnUIElement(115.f, -60.f, 30, 30, "shieldOn.png");

	ECS::GetComponent<Sprite>(uiElements[4]).SetTransparency(0.f);
}

void DenialLevel::ShootBullet(int bullet)
{
	//shootBulletSound.Play();
	//shootBulletSound.SetVolume(5.0f);
	b2Vec2 angle = CalculateAngle(MainEntities::MainPlayer(), bullet);

	float dirAngle = atan(angle.x/angle.y) * (180 / PI);

	ECS::GetComponent<PhysicsBody>(bullet).SetRotationAngleDeg(dirAngle * -1);
	ECS::GetComponent<PhysicsBody>(bullet).GetBody()->SetLinearVelocity(b2Vec2(angle.x * 100, angle.y * 100));

	float x = ECS::GetComponent<PhysicsBody>(bullet).GetVelocity().x;
	float y = ECS::GetComponent<PhysicsBody>(bullet).GetVelocity().y;
}

void DenialLevel::ShootBullet(int bullet, float degrees)
{
	ECS::GetComponent<PhysicsBody>(bullet).SetRotationAngleDeg(degrees);
	ECS::GetComponent<PhysicsBody>(bullet).GetBody()->SetLinearVelocity(b2Vec2(0, -100));
}

void DenialLevel::ActivateShadow(int shadow)
{
	//Checks to see if the appropriate amount of seconds of passed between now and the last shot. 
	//If so, a bullet is fired from a shadow determined by the player's location.
	auto& pMechanics = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	auto& shade = ECS::GetComponent<ShadowLoop>(shadow);

	shade.ShadowRoutine(shadow);

	if (shade.GetFiring() && shade.GetShadowSequence())
	{
		SpawnBullet(shadow);
	}
}

b2Vec2 DenialLevel::CalculateAngle(int entityOne, int entityTwo)
{
	float deltaX = 0, deltaY = 0;
	deltaX = ECS::GetComponent<PhysicsBody>(entityOne).GetBody()->GetPosition().x - ECS::GetComponent<PhysicsBody>(entityTwo).GetBody()->GetPosition().x;
	deltaY = ECS::GetComponent<PhysicsBody>(entityOne).GetBody()->GetPosition().y - ECS::GetComponent<PhysicsBody>(entityTwo).GetBody()->GetPosition().y;

	return b2Vec2(deltaX , deltaY);
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