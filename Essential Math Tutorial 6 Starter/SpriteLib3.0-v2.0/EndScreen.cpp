#include "EndScreen.h"
#include "Utilities.h"

EndScreen::EndScreen(std::string name)
{
}

void EndScreen::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register
	m_sceneReg = new entt::registry;
	m_physicsWorld = new b2World(m_gravity);
	SetSceneChange(false, -1);
	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;
	SpawnMainCamera(windowWidth, windowHeight);
	SpawnMenus();

	{
		menuBGM.Play();
		menuBGM.SetVolume(1.0f);
	}

	//Creating end game art screen
	{
		endScreens[0] = ECS::CreateEntity();
		ECS::SetIsMainPlayer(endScreens[0], true);

		//Add components
		//ECS::AttachComponent<Player>(entity);
		ECS::AttachComponent<Sprite>(endScreens[0]);
		ECS::AttachComponent<Transform>(endScreens[0]);


		//Set up components
		std::string fileName = "DearAbigailEndScreen.png";
		ECS::GetComponent<Sprite>(endScreens[0]).LoadSprite(fileName, 270, 150);
		ECS::GetComponent<Transform>(endScreens[0]).SetPosition(vec3(0.f, 0.f, 2.f));
	}

	//Creating end message screen
	{
		endScreens[1] = ECS::CreateEntity();

		//Add components
		//ECS::AttachComponent<Player>(entity);
		ECS::AttachComponent<Sprite>(endScreens[1]);
		ECS::AttachComponent<Transform>(endScreens[1]);


		//Set up components
		std::string fileName = "DearAbigailEndScreenMessage.png";
		ECS::GetComponent<Sprite>(endScreens[1]).LoadSprite(fileName, 270, 150);
		ECS::GetComponent<Transform>(endScreens[1]).SetPosition(vec3(0.f, 0.f, 2.f));
		ECS::GetComponent<Sprite>(endScreens[1]).SetTransparency(0.f);
	}

	//Creating credits screen
	{
		endScreens[2] = ECS::CreateEntity();

		//Add components
		//ECS::AttachComponent<Player>(entity);
		ECS::AttachComponent<Sprite>(endScreens[2]);
		ECS::AttachComponent<Transform>(endScreens[2]);


		//Set up components
		std::string fileName = "CreditsScreen.png";
		ECS::GetComponent<Sprite>(endScreens[2]).LoadSprite(fileName, 270, 150);
		ECS::GetComponent<Transform>(endScreens[2]).SetPosition(vec3(0.f, 0.f, 2.f));
		ECS::GetComponent<Sprite>(endScreens[2]).SetTransparency(0.f);
	}

	//Creating thanks for playing screen
	{
		endScreens[3] = ECS::CreateEntity();

		//Add components
		//ECS::AttachComponent<Player>(entity);
		ECS::AttachComponent<Sprite>(endScreens[3]);
		ECS::AttachComponent<Transform>(endScreens[3]);


		//Set up components
		std::string fileName = "tyfp.png";
		ECS::GetComponent<Sprite>(endScreens[3]).LoadSprite(fileName, 270, 150);
		ECS::GetComponent<Transform>(endScreens[3]).SetPosition(vec3(0.f, 0.f, 2.f));
		ECS::GetComponent<Sprite>(endScreens[3]).SetTransparency(0.f);
	}

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));

}

void EndScreen::Update()
{
}


void EndScreen::KeyboardDown()
{
	static int stage = 0;

	if (Input::GetKeyDown(Key::Enter))
	{
		switch (stage)
		{
			case 0:
				ECS::GetComponent<Sprite>(endScreens[0]).SetTransparency(0.f);
				ECS::GetComponent<Sprite>(endScreens[1]).SetTransparency(1.f);
				break;
			case 1:
				ECS::GetComponent<Sprite>(endScreens[1]).SetTransparency(0.f);
				ECS::GetComponent<Sprite>(endScreens[2]).SetTransparency(1.f);
				break;
			case 2:
				ECS::GetComponent<Sprite>(endScreens[2]).SetTransparency(0.f);
				ECS::GetComponent<Sprite>(endScreens[3]).SetTransparency(1.f);
				break;
			case 3:
				exit(0);
				break;
		}
		stage++;
	}
}

void EndScreen::Separate(b2Vec2 newPair, int type)
{
}