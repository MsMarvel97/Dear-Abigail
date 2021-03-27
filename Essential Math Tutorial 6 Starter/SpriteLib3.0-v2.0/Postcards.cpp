#include "Postcards.h"
#include "Utilities.h"

Postcards::Postcards(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(0.f, -98.f);
	m_physicsWorld->SetGravity(m_gravity);
	m_physicsWorld->SetContactListener(&listener);
	
}

void Postcards::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;
	m_physicsWorld = new b2World(m_gravity);
	SetSceneChange(false, -1);

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
		//vec4 temp = vec4(-100.f, 100.f, -100.f, 100.f);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		//Attaches the camera to vert and horiz scrolls
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	}

	//Abigail entity
	{
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainPlayer(entity, true);

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
		tempDef.position.Set(float32(-64.f), float32(30.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, PLAYER, ENEMY | OBJECTS | PICKUP | TRIGGER | SNAIL, 0.f, 1.f);

		tempPhsBody.SetFixedRotation(true);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
		tempPhsBody.SetGravityScale(0.75);
	}

	//Spawn postcard
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		postcardMin = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "DenialPostcardBack.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 30.f, 20.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 20.f, 2.f));
	}

	//Spawn postcard
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		postcardMax = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<Kinematics>(entity);

		//Sets up components
		std::string fileName = "DenialPostcardBack.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 150.f, 120.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 24.f, 2.f));
		ECS::GetComponent<Kinematics>(entity).SetParent(MainEntities::MainCamera());
		ECS::GetComponent<Kinematics>(entity).SetChild(entity);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0.f, 0.f);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
	}

	//Spawn exit
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "CaveExit.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20.f, 40.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(64.f, 24.f, 2.f));
	}

	SpawnPlatform(0.f, 0.f, 256.f, 10.f, "none", 0.f);
	SpawnPlatform(112.f, 0.f, 512.f, 10.f, "none", 0.f, 90.f);
	SpawnPlatform(-112.f, 0.f, 512.f, 10.f, "none", 0.f, 90.f);

	// TILE POSTCARD BACKGROUND
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/postcards/background.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3((0), (0.f + 52), 1.f));
	}

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}



void Postcards::Update()
{
	auto& player = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& pPhysics = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& pMechanics = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());

	ECS::GetComponent<Kinematics>(postcardMax).UpdateUI();

	if (pMechanics.GetCanMove() == true)
	{
		player.Update();
	}

	fmod.Update();

	if (pPhysics.GetPosition().x >= 40.f && pPhysics.GetPosition().x <= 100.f)
	{
		static bool maximized = false;
		static bool contactStep = false;

		if (Input::GetKeyDown(Key::F) && !maximized)
		{
			maximized = true;
			contactStep = true;
			ECS::GetComponent<Sprite>(postcardMin).SetTransparency(0.f);
			ECS::GetComponent<Sprite>(postcardMax).SetTransparency(1.f);
		}
		if (Input::GetKeyDown(Key::F) && maximized && !contactStep)
		{
			maximized = false;
			ECS::GetComponent<Sprite>(postcardMin).SetTransparency(1.f);
			ECS::GetComponent<Sprite>(postcardMax).SetTransparency(0.f);
		}
		contactStep = false;
	}

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).Update();
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).Update();
}
