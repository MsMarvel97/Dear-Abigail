#pragma once
#include "Scene.h"
#include "PhysicsPlayground.h"

class DenialLevel : public Scene
{
public:
	DenialLevel(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;
	void Update() override;

	void KeyboardHold() override;
	void KeyboardUp() override;
	void KeyboardDown() override;

	void CrumblingPlatforms(int entity);
	void MovePlatform();

	void SpawnBullet(int shadow);
	void SpawnBullet(int wall, float offsetX, float offsetY);

	void ShootBullet(int bullet); //shoots bullets with an angle determined between player and origin
	void ShootBullet(int bullet, float degrees); //shoots bullets at a fixed angle

	void ActivateShadow(int shadow);

	b2Vec2 CalculateAngle(int entityOne, int entityTwo);

	int uiElements[7];
	int shield = 0;
	int player;
	int movingPlat;
	int vertMovingPlat;
	int vertPlatTrigger;
	int kinTrigger;
	bool switchDir = false;
	int cPlatforms[8];
	int cTriggers[8];
	int shadows[4];
	int sZones[4];
	int bulletWalls[2];
	int bullet = 0;


protected:
	PhysicsPlaygroundListener listener;

	float wWidth = 0;
	float wHeight = 0;
	vec3 playerVel; //track player velocity to get y value
	b2Vec2 playerPos; //track player's position
};

