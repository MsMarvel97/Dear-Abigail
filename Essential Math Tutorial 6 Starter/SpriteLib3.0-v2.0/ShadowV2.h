#pragma once

#include "Scene.h"
#include "PhysicsPlaygroundListener.h"
class ShadowV2 : public Scene
{
public:
	ShadowV2(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	void ReattachCamera();

	void SpawnBullet();

	void ShootBullet();

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

protected:
	PhysicsPlaygroundListener listener;
	int player = 0;
	int shadow = 0;
	int bullet = 0;
};

