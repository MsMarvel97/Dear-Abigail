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

	void MovePlatform();

	int player;
	int movingPlat;
	bool switchDir = false;

protected:
	PhysicsPlaygroundListener listener;

	vec3 playerVel; //track player velocity to get y value
	b2Vec2 playerPos; //track player's position
};

