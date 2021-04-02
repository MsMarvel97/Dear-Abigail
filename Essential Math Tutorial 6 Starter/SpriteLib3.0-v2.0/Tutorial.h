#pragma once
#include "Scene.h"
#include "PhysicsPlaygroundListener.h"

class Tutorial :
    public Scene
{
public:
	Tutorial(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;
	void Update();

protected:
	PhysicsPlaygroundListener listener;
};

