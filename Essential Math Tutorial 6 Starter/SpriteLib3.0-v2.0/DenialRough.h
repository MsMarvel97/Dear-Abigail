#pragma once

#include "Scene.h"
#include "PhysicsPlaygroundListener.h"
#include <string>
class DenialRough : public Scene
{
public:
	DenialRough(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	void CheckShield();

	void SpawnBullet();
	void ShootBullet();

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	void ReattachCamera();
	bool shieldActive = false;

protected:
	PhysicsPlaygroundListener listener;
	int player = 0;
	int shield = 0;
	int shadow = 0;
	int bullet = 0;
};

