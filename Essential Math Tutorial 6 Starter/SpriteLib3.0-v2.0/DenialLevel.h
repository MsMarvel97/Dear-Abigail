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

	int player;
	int movingPlat;
	int vertMovingPlat;
	int kinTrigger;
	bool switchDir = false;
	int cPlatforms[8];
	int cTriggers[8];

protected:
	PhysicsPlaygroundListener listener;

	vec3 playerVel; //track player velocity to get y value
	b2Vec2 playerPos; //track player's position
};

