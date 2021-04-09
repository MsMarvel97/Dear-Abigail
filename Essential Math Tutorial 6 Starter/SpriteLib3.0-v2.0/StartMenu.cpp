#include "StartMenu.h"
#include "Utilities.h"

StartMenu::StartMenu(std::string name)
	: Scene(name)
{
}

void StartMenu::InitScene(float windowWidth, float windowHeight)
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

	{
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainPlayer(entity, true);

		//Add components
		//ECS::AttachComponent<Player>(entity);
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);


		//Set up components
		std::string fileName = "DearAbigailTitleScreen.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 270, 150);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 2.f));
	}

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));

}

void StartMenu::Update()
{
	MenuKeys();
}

void StartMenu::KeyboardDown()
{
	if (ECS::GetComponent<Sprite>(menus.y).GetTransparency() == 0.f && ECS::GetComponent<Sprite>(menus.x).GetTransparency() == 0.f)
	{
		if (Input::GetKeyDown(Key::Enter))
		{
			SetSceneChange(true, 1);
			menuBGM.Mute();
		}
	}
}
void StartMenu::Separate(b2Vec2 newPair, int type)
{

}
