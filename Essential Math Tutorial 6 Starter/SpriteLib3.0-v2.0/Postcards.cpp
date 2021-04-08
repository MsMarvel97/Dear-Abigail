#include "Postcards.h"
#include "Utilities.h"

Postcards::Postcards(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(0.f, -98.f);
	m_physicsWorld->SetGravity(m_gravity);
}

void Postcards::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;
	m_physicsWorld = new b2World(m_gravity);
	m_physicsWorld->SetContactListener(&listener);
	SetSceneChange(false, -1);

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;


	SpawnMainCamera(windowWidth, windowHeight);
	SpawnMenus();
	SpawnMainPlayer(-64.f, 30.f);

	//plays the transition music
	{
		//transitionBGM.Play();
		//transitionBGM.SetVolume(9.0f);
	}

	BuildPostcards();
	SpawnTile(64.f, 24.f, "CaveExit.png", true, 1.f, 20.f, 40.f);

	////Spawn exit
	//{
	//	//Creates entity
	//	auto entity = ECS::CreateEntity();

	//	//Add components
	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);

	//	//Sets up components
	//	std::string fileName = "CaveExit.png";
	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20.f, 40.f);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(64.f, 24.f, 2.f));
	//}

	SpawnPlatform(0.f, 0.f, 256.f, 10.f, "none", 0.f);
	SpawnPlatform(112.f, 0.f, 512.f, 10.f, "none", 0.f, 90.f);
	SpawnPlatform(-112.f, 0.f, 512.f, 10.f, "none", 0.f, 90.f);
	uiElements[0] = SpawnUIElement(110.f, -60.f, 30.f, 30.f, "InspectOn.png");
	uiElements[1] = SpawnUIElement(110.f, -60.f, 30.f, 30.f, "InspectOff.png");
	ECS::GetComponent<Sprite>(uiElements[0]).SetTransparency(0.f);

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

void Postcards::BuildPostcards()
{

	//how many times has the player been here?
	static int visit = 0;
	b2Vec2 postcard;
	switch (visit)
	{
	case 0:
		postcard = SpawnPostcard(0.f, 20.f, "GriefPostcardBack.png");
		break;
	case 1:
		postcard = SpawnPostcard(0.f, 20.f, "DenialPostcardBack.png");
		break;
	case 2:
		postcard = SpawnPostcard(0.f, 20.f, "AngerPostcardBack.png");
		break;
	default:
		postcard = SpawnPostcard(0.f, 20.f, "DenialPostcardFront.png");
		break;
	}
	nextScene = visit + 2;
	Separate(postcard);
	visit++;
}



void Postcards::Update()
{
	if (sceneActive)
	{
		auto& player = ECS::GetComponent<Player>(MainEntities::MainPlayer());
		auto& pPhysics = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
		auto& pMechanics = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());

		//static int visit = 0;

		ECS::GetComponent<Kinematics>(postcardMax).UpdateUI();

		if (pMechanics.GetCanMove() == true)
		{
			player.Update();
		}

		fmod.Update();

		if (pMechanics.GetExamine())
		{
			static bool maximized = false;
			static bool contactStep = false;

			if (Input::GetKeyDown(Key::F) && !maximized)
			{
				maximized = true;
				contactStep = true;
				ECS::GetComponent<Sprite>(postcardMin).SetTransparency(0.f);
				ECS::GetComponent<Sprite>(postcardMax).SetTransparency(1.f);
				ECS::GetComponent<Sprite>(uiElements[0]).SetTransparency(1.f);
				ECS::GetComponent<Transform>(uiElements[0]).SetPositionZ(11.f);
				ECS::GetComponent<Sprite>(uiElements[1]).SetTransparency(0.f);
				pMechanics.SetCanMove(false);
			}
			if (Input::GetKeyDown(Key::F) && maximized && !contactStep)
			{
				maximized = false;
				ECS::GetComponent<Sprite>(postcardMin).SetTransparency(1.f);
				ECS::GetComponent<Sprite>(postcardMax).SetTransparency(0.f);
				ECS::GetComponent<Sprite>(uiElements[0]).SetTransparency(0.f);
				ECS::GetComponent<Sprite>(uiElements[1]).SetTransparency(1.f);
				pMechanics.SetCanMove(true);
			}
			contactStep = false;
		}

		if (Input::GetKeyDown(Key::C))
		{
			pMechanics.SetComplete(true);
		}

		//ends music
		if (ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).GetComplete())
		{
			transitionBGM.Mute();
		}

		CheckEndLevel(nextScene);

		ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
		ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));

		ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).Update();
		ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).Update();

		for (int i = 0; i <= 1; i++)
		{
			ECS::GetComponent<Kinematics>(uiElements[i]).UpdateUI();
		}
		MenuKeys();
	}

	else
	{
		ECS::GetComponent<Kinematics>(menus.x).UpdateUI();
		ECS::GetComponent<Kinematics>(menus.y).UpdateUI();

		auto view = m_sceneReg->view<PhysicsBody>();
		//Finds all active physics bodies and freezes them in place
		for (auto entity : view)
		{
			//Grabs references to each component within view
			ECS::GetComponent<PhysicsBody>(entity).SetVelocity(vec3(0.f, 0.f, 0.f));
		}

		auto bullets = m_sceneReg->view<Trigger*>();
		//Finds all active bullets and deletes them so they don't stay frozen after game is unpaused
		for (auto entity : bullets)
		{
			if (ECS::GetComponent<Trigger*>(entity)->GetBulletTrigger())
			{
				PhysicsBody::m_bodiesToDelete.push_back(entity);
			}
		}

		MenuKeys();
	}
}

void Postcards::Separate(b2Vec2 newPair, int type)
{
	postcardMin = newPair.x;
	postcardMax = newPair.y;
}
