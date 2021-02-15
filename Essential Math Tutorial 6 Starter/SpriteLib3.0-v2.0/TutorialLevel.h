#pragma once
#include "Scene.h"
#include "PhysicsPlaygroundListener.h"

class TutorialLevel : public Scene
{
public:
	TutorialLevel(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;
	void Update() override;
	
	void KeyboardHold() override;
	void KeyboardUp() override;
	void KeyboardDown() override;

protected:
	PhysicsPlaygroundListener listener;

	//can the player jump?
	//1 means can jump
	//0 means can't jump
	int jumpState;

	vec3 playerVel; //track player velocity to get y value
	b2Vec2 playerPos; //track player's position
	bool inAir;
	int frames;

};

