#pragma once

#include "Scene.h"
#include "PhysicsPlaygroundListener.h"
#include <string>
class Shield : public Scene
{
public:
	Shield(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	void CheckShield();

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	void ReattachCamera();
	bool shieldActive = false;

protected:
	PhysicsPlaygroundListener listener;
	int player;
	int shield;
};

