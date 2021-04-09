#ifndef __SCENE_H__
#define __SCENE_H__

#include "JSON.h"
#include "ECS.h"
#include "Timer.h"
#include "Xinput.h"
#include "MainEntities.h"
#include <SDL2/SDL.h>


class Scene
{
public:
	Scene() { m_sceneReg = new entt::registry(); m_physicsWorld = new b2World(m_gravity); }
	Scene(std::string name);
	~Scene() { }

	void Unload();

	//Each scene will need to have a different
	//init, as each scene's contents will be different
	virtual void InitScene(float windowWidth, float windowHeight);

	virtual void Update();

	void AdjustScrollOffset();
	void CreateCameraEntity(bool mainCamera, float windowWidth, float windowHeight, float left, float right, float bottom, float top, 
								float zNear, float zFar, float aspectRatio, bool vertScroll=false, bool horizScroll=false);

	//Gamepad Input
	//Because these are virtual you can override them in your inherited classes.
	//The same way you do for Update().
	virtual void GamepadStroke(XInputController* con) { };
	virtual void GamepadUp(XInputController* con) { };
	virtual void GamepadDown(XInputController* con) { };
	virtual void GamepadStick(XInputController* con) { };
	virtual void GamepadTrigger(XInputController* con) { };
	virtual void KeyboardHold() { };
	virtual void KeyboardDown() { };
	virtual void KeyboardUp() { };

	//Mouse Input
	//Because these are virtual you can override them in your inherited classes.
	//The same way you do for Update().
	virtual void MouseMotion(SDL_MouseMotionEvent evnt) { };
	virtual void MouseClick(SDL_MouseButtonEvent evnt) { };
	virtual void MouseWheel(SDL_MouseWheelEvent evnt) { };

	//checks conditions for scene change
	int ChangeScene();
	void SetSceneChange(bool next, int newScene) { swap = next; sceneSwap = newScene; };
	int GetNewScene() {	return sceneSwap; };
	void SetSwap(bool sceneSwap) { swap = sceneSwap; };

	//Get the scene registry
	entt::registry* GetScene() const;
	//Set the scene registry
	void SetScene(entt::registry& scene);

	//Spawner Functions\\
	//spawn a UI element (PARAMETERS -> Camera offset [x, y], size [w, h], sprite)
	int SpawnUIElement(float xOffset, float yOffset, float width, float height, std::string sprite);

	//spawn a crumbling platform (PARAMETERS -> Position [x,y], size [w,h])
	int SpawnCrumblingPlatform(float xPos, float yPos, float width = 48.f, float height = 32.f, bool blue = true);

	//spawn a tile or other sprite-only entity (PARAMETERS -> Position [x,y], sprite, end-flag [is this the end of the level?], position [z], size [w, h])
	void SpawnTile(float xPos, float yPos, std::string sprite, bool endFlag = false, float zPos = 1.f, float width = 256.f, float height = 256.f );

	//spawn a platform (PARAMETERS -> Position [x, y], size [w, h], sprite, transparency, rotation [degrees])
	int SpawnPlatform(float xPos, float yPos, float width, float height, std::string sprite, float transparency = 1.f, float rotation = 0.f);

	//spawns a shadow (PARAMETERS -> Position [x,y], movement boundaries [min, max], patrol velocity, trigger offset [x, y], size [w, h])
	b2Vec2 SpawnShadow(float xPos, float yPos, float min, float max, bool ranged, b2Vec2 patrolVel, float xOffset = 0.f, float yOffset = -50.f, float width = 32.f, float height = 32.f, bool bossShadow = false);

	//spawns a moving platform (PARAMETERS -> Position [x,y], movement boundaries [min, max], type [0 = horizontal, 1 = vertical], size [w,h]) 
	b2Vec2 SpawnMovingPlatform(float xPos, float yPos, float min, float max, int type, float width, float height, std::string sprite ="movingPlatform.png");

	//spawns a bullet wall (PARAMETERS -> Position [x, y], Size [w,h])
	int SpawnBulletWall(float xPos, float yPos, float width = 16.f, float height = 16.f);

	b2Vec2 SpawnPostcard(float xPos, float yPos, std::string postcardBack);

	//spawn Abigail (PARAMETERS -> Position [x,y])
	void SpawnMainPlayer(float xPos, float yPos);

	b2Vec2 SpawnMenus();

	//spawn the camera (PARAMETERS -> View [w, h])
	void SpawnMainCamera(float width, float height);

	//spawn a spike (PARAMETERS -> Position [x,y], size [w,h])
	void SpawnSpike(float xPos, float yPos, float width = 16.f, float height = 16.f, std::string fileName = "Spike.png");

	//spawn a shadow orb (PARAMETERS -> Position [x,y], size [w,h])
	int SpawnOrb(float xPos, float yPos, float width = 10.f, float height = 10.f);

	//to be overridden for separating pairs of entities within each scene
	virtual void Separate(b2Vec2 newPair, int type) = 0;

	//checks if the player has completed the level
	void CheckEndLevel(int sceneID);

	void MenuKeys();

	void MenuOperations(int op);

	//Gets the background color of the scene
	vec4 GetClearColor() const;
	//Sets the background color of the scene
	void SetClearColor(vec4 clearColor);

	//Gets the name of the scene
	std::string GetName() const;
	//Sets the name of the scene
	void SetName(std::string name);
	
	//Gravity
	b2Vec2 GetGravity() const;
	void SetGravity(b2Vec2 grav);
	//Physics world
	b2World& GetPhysicsWorld();

	//Set window size (makes sure the camera aspect is proper)
	void SetWindowSize(float windowWidth, float windowHeight);

protected:
	ToneFire::FMODCore fmod;
	b2Vec2 menus;
	bool sceneActive = true;
	b2World* m_physicsWorld = nullptr;
	b2Vec2 m_gravity = b2Vec2(float32(0.f), float32(0.f));

	bool swap = false;
	int sceneSwap = 0;
	
	std::vector<int> shadowBullets;
	std::vector<int> wallBullets;
	std::vector<int> bullets;

	vec4 m_clearColor = vec4(0.f, 0.f, 0.f, 0.f);

	entt::registry* m_sceneReg = nullptr;	
	std::string m_name = "Default Name";
private:
	//Hello world entity number
	int m_helloWorldSign = 0;
};

#endif // !__SCENE_H__
