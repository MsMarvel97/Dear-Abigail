#pragma once
#include "Scene.h"
#include "PhysicsPlayground.h"

class Postcards : public Scene
{
public:
	Postcards(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;
	void Update();

protected:
	PhysicsPlaygroundListener listener;
	int postcardMin = 0;
	int postcardMax = 0;

};

