#pragma once
#include "Scene.h"
#include "PhysicsPlayground.h"

class DenialLevel : public Scene
{
public:
	DenialLevel(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;

	//functions to be called during scene initialization to build their respective scene elements
	void SpawnPlatforms();
	void SpawnCrumblingPlatforms();
	void SpawnTiles();
	void SpawnUI();

	void Update() override;

	void KeyboardHold() override;
	void KeyboardUp() override;
	void KeyboardDown() override;

	void CrumblingPlatforms(int entity);
	void MovePlatform();

	void SpawnBullet(int shadow);
	void SpawnBullet(int wall, float offsetX, float offsetY);


	void CheckUIConditions();

	void ShootBullet(int bullet); //shoots bullets with an angle determined between player and origin
	void ShootBullet(int bullet, float degrees); //shoots bullets at a fixed angle

	void ActivateShadow(int shadow);

	b2Vec2 CalculateAngle(int entityOne, int entityTwo);

	//int uiElements[7];
	int shield = 0;
	int player;
	int movingPlat;
	int vertMovingPlat;
	int vertPlatTrigger;
	int kinTrigger;
	bool switchDir = false;
	int cPlatforms[18];
	int cTriggers[8];
	int shadows[5];
	int sZones[5];
	int bulletWalls[4];
	int bullet = 0;


protected:
	PhysicsPlaygroundListener listener;


	//UI ELEMENTS\\
	//0 = left heart
	//1 = middle heart
	//2 = right heart
	//3 = shield available icon
	//4 = shield active icon
	int uiElements[5];



	float wWidth = 0;
	float wHeight = 0;
	vec3 playerVel; //track player velocity to get y value
	b2Vec2 playerPos; //track player's position

private:
	ToneFire::CoreSound shootBulletSound{ "shadowBulletThree.wav",false,false,true };
	ToneFire::CoreSound denialBGM{ "denialBGM.wav", false, false, true };
	ToneFire::CoreSound crumbleSound{ "crumble.wav", false, false, true };
	ToneFire::CoreSound abigailHit{ "abigailHitOne.wav", false, false, true };
};

