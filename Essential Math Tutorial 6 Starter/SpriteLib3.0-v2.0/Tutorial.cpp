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
	//SpawnMainPlayer(0.f, 20.f);
	SpawnMainPlayer(530.f, 10.f);

	SpawnPlatform(140.f, 0.f, 300.f, 10.f, ""); //starting platform
	SpawnPlatform(285.f, -55.f, 100.f, 10.f, "", 1.f, 90.f); //left pit wall
	SpawnPlatform(355.f, -55.f, 100.f, 10.f, "", 1.f, 90.f); //right pit wall
	SpawnPlatform(320.f, -55.f, 70.f, 10.f, ""); //pit floor
	SpawnPlatform(600.f, 0.f, 500.f, 10.f, ""); //pit exit platform
	SpawnPlatform(200.f, 142.f, 420.f, 200.f, "");//roof
	SpawnPlatform(295.f, -45.f, 20.f, 25.f, "");//ledge in pit
	SpawnPlatform(550.f, 20.f, 35.f, 40.f, "");//ledge before moving platform
	SpawnPlatform(830.f, 25.f, 40.f, 50.f, "");//ledge to exit after moving platform
	SpawnPlatform(925.f, 45.f, 150.f, 10.f, "");//exit platform 
	SpawnTile(975.f, 70.f, "CaveExit.png", true, 2.f, 20.f, 40.f);
	movingPlatform = SpawnMovingPlatform(650.f, 45.f, 630.f, 740.f, 0.f, 100.f, 10.f); //moving platform leading to exit platform

	SpawnUI();

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void Tutorial::SpawnUI()
{
	uiElements[0] = Scene::SpawnUIElement(-120.f, 65.f, 20, 20, "heart.png");
	uiElements[1] = Scene::SpawnUIElement(-100.f, 65.f, 20, 20, "heart.png");
	uiElements[2] = Scene::SpawnUIElement(-80.f, 65.f, 20, 20, "heart.png");
}

void Tutorial::Update()
{
	auto& player = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& pPhysics = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& pMechanics = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());

	if (pMechanics.GetCanMove() == true)
	{
		player.Update();
	}

	if (pMechanics.GetComplete())
	{
		SetSceneChange(true, 1);
	}

	if (Input::GetKeyDown(Key::C))
	{
		SetSceneChange(true, 2);
	}

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
}

void Tutorial::Separate(b2Vec2 newPair, int type)
{
}
