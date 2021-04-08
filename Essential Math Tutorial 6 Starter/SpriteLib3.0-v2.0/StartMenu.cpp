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

	////Setup MainCamera Entity
	//{
	//	//Creates Camera entity
	//	auto entity = ECS::CreateEntity();
	//	ECS::SetIsMainCamera(entity, true);

	//	//Creates new orthographic camera
	//	ECS::AttachComponent<Camera>(entity);
	//	ECS::AttachComponent<HorizontalScroll>(entity);
	//	ECS::AttachComponent<VerticalScroll>(entity);

	//	vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f);
	//	ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
	//	ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
	//	ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

	//	//Attaches Camera for Side Scrolling
	//	ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	//	ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	//}

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
		}
	}
}
void StartMenu::Separate(b2Vec2 newPair, int type)
{

}
