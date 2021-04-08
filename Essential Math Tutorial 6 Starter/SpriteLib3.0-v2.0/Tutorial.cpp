#include "Tutorial.h"
#include "Utilities.h"

Tutorial::Tutorial(std::string name) 
	: Scene (name)
{
	m_gravity = b2Vec2(0.f, -98.f);
	m_physicsWorld->SetGravity(m_gravity);
}

void Tutorial::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;
	m_physicsWorld = new b2World(m_gravity);
	m_physicsWorld->SetContactListener(&listener);
	SetSceneChange(false, -1);

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	SpawnMainCamera(windowWidth, windowHeight);
	SpawnMenus();
	SpawnMainPlayer(0.f, 20.f);
	//SpawnMainPlayer(530.f, 10.f);

	SpawnPlatform(140.f, 0.f, 300.f, 10.f, "", 0.f); //starting platform
	SpawnPlatform(-5.f, 25.f, 50.f, 10.f, "PlatformT.png", 1.f, 90.f); //left wall so player doesn't fall off the side //ADD AN ART ASSET HERE OR LEAVE THIS INVISIBLE AND ADJUST THE TILE AT THIS LOCATION
	SpawnPlatform(285.f, -55.f, 100.f, 10.f, "", 0.f, 90.f); //left pit wall
	SpawnPlatform(355.f, -55.f, 100.f, 10.f, "", 0.f, 90.f); //right pit wall
	SpawnPlatform(320.f, -55.f, 70.f, 10.f, "", 0.f); //pit floor
	SpawnPlatform(600.f, 0.f, 500.f, 10.f, "", 0.f); //pit exit platform
	SpawnPlatform(200.f, 142.f, 420.f, 200.f, "", 0.f);//roof
	SpawnPlatform(295.f, -45.f, 20.f, 25.f, "", 0.f);//ledge in pit
	SpawnPlatform(550.f, 20.f, 35.f, 40.f, "", 0.f);//ledge before moving platform
	SpawnPlatform(830.f, 25.f, 40.f, 50.f, "", 0.f);//ledge to exit after moving platform
	SpawnPlatform(925.f, 45.f, 150.f, 10.f, "", 0.f);//exit platform 
	SpawnTile(975.f, 70.f, "CaveExit.png", true, 2.f, 20.f, 40.f);
	movingPlatform = SpawnMovingPlatform(650.f, 45.f, 630.f, 740.f, 0.f, 100.f, 10.f); //moving platform leading to exit platform

	//Setting up the background tiles
	SpawnTile(-90.f, -115.f, "backgrounds/tutorial/tutorial0-0.png", false, 2.f, 160.f, 160.f);
	SpawnTile(70.f, -115.f, "backgrounds/tutorial/tutorial1-0.png", false, 2.f, 160.f, 160.f);	//layer 0
	SpawnTile(230.f, -115.f, "backgrounds/tutorial/tutorial2-0.png", false, 2.f, 160.f, 160.f);
	SpawnTile(390.f, -115.f, "backgrounds/tutorial/tutorial3-0.png", false, 2.f, 160.f, 160.f);
	SpawnTile(550.f, -115.f, "backgrounds/tutorial/tutorial4-0.png", false, 2.f, 160.f, 160.f);
	SpawnTile(710.f, -115.f, "backgrounds/tutorial/tutorial5-0.png", false, 2.f, 160.f, 160.f);
	SpawnTile(870.f, -115.f, "backgrounds/tutorial/tutorial6-0.png", false, 2.f, 160.f, 160.f);
	SpawnTile(1030.f, -115.f, "backgrounds/tutorial/tutorial7-0.png", false, 2.f, 160.f, 160.f);

	SpawnTile(-90.f, 45.f, "backgrounds/tutorial/tutorial0-1.png", false, 2.f, 160.f, 160.f);
	SpawnTile(70.f, 45.f, "backgrounds/tutorial/tutorial1-1.png", false, 2.f, 160.f, 160.f);	//layer 1
	SpawnTile(230.f, 45.f, "backgrounds/tutorial/tutorial2-1.png", false, 2.f, 160.f, 160.f);
	SpawnTile(390.f, 45.f, "backgrounds/tutorial/tutorial3-1.png", false, 2.f, 160.f, 160.f);
	SpawnTile(550.f, 45.f, "backgrounds/tutorial/tutorial4-1.png", false, 2.f, 160.f, 160.f);
	SpawnTile(710.f, 45.f, "backgrounds/tutorial/tutorial5-1.png", false, 2.f, 160.f, 160.f);
	SpawnTile(870.f, 45.f, "backgrounds/tutorial/tutorial6-1.png", false, 2.f, 160.f, 160.f);
	SpawnTile(1030.f, 45.f, "backgrounds/tutorial/tutorial7-1.png", false, 2.f, 160.f, 160.f);

	SpawnTile(-90.f, 205.f, "backgrounds/tutorial/tutorial0-1.png", false, 2.f, 160.f, 160.f);
	SpawnTile(70.f, 205.f, "backgrounds/tutorial/tutorial1-2.png", false, 2.f, 160.f, 160.f);	//layer 2
	SpawnTile(230.f, 205.f, "backgrounds/tutorial/tutorial2-2.png", false, 2.f, 160.f, 160.f);
	SpawnTile(390.f, 205.f, "backgrounds/tutorial/tutorial3-2.png", false, 2.f, 160.f, 160.f);
	SpawnTile(550.f, 205.f, "backgrounds/tutorial/tutorial4-2.png", false, 2.f, 160.f, 160.f);
	SpawnTile(710.f, 205.f, "backgrounds/tutorial/tutorial5-2.png", false, 2.f, 160.f, 160.f);
	SpawnTile(870.f, 205.f, "backgrounds/tutorial/tutorial6-2.png", false, 2.f, 160.f, 160.f);
	SpawnTile(1030.f, 205.f, "backgrounds/tutorial/tutorial7-2.png", false, 2.f, 160.f, 160.f);

	SpawnUI();

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));

	//tutorialBGM.Play();
	//tutorialBGM.SetVolume(1.5f);
}

void Tutorial::SpawnUI()
{
	uiElements[0] = Scene::SpawnUIElement(-120.f, 65.f, 20, 20, "heart.png");
	uiElements[1] = Scene::SpawnUIElement(-100.f, 65.f, 20, 20, "heart.png");
	uiElements[2] = Scene::SpawnUIElement(-80.f, 65.f, 20, 20, "heart.png");
}

void Tutorial::Update()
{
	if (sceneActive)
	{
		auto& player = ECS::GetComponent<Player>(MainEntities::MainPlayer());
		auto& pPhysics = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
		auto& pMechanics = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());

		if (pMechanics.GetCanMove() == true)
		{
			player.Update();
		}

		//if (pMechanics.GetComplete())
		//{
		//	SetSceneChange(true, 1);
		//}
		//if (Input::GetKeyDown(Key::C))
		//{
		//	SetSceneChange(true, 2);
		//}


		//ends music
		if (ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).GetComplete())
		{
			tutorialBGM.Mute();
		}
		CheckEndLevel(4);


		ECS::GetComponent<Kinematics>(movingPlatform.y).UpdatePosition();
		ECS::GetComponent<MovingPlatform>(movingPlatform.x).MovePlatform(movingPlatform.x);

		ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
		ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));

		ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).Update();
		ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).Update();

		for (int i = 0; i <= 2; i++)
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

		MenuKeys();
	}
}

void Tutorial::Separate(b2Vec2 newPair, int type)
{
}
