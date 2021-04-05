#pragma once
#include "Scene.h"
#include "PhysicsPlayground.h"

class Tutorial : public Scene
{
public:
	Tutorial(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;
	void SpawnUI();
	void Update() override;

	void Separate(b2Vec2 newPair, int type) override;

protected:
	PhysicsPlaygroundListener listener;
	//UI ELEMENTS\\
	//0 = left heart
	//1 = middle heart
	//2 = right heart
	int uiElements[3];
	
	b2Vec2 movingPlatform;
	//b2Vec2 movingPlatform;
};

