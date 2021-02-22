#pragma once 
#include "Scene.h" 
#include "PhysicsPlayground.h"

class AngerLevel : public Scene
{
public:
	AngerLevel(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	void AdjustScrollOffset();

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

protected:
	PhysicsPlaygroundListener listener;
	vec3 playerVel;
	b2Vec2 playerPos; 
};