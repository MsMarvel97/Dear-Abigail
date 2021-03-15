#pragma once
#include "Scene.h"
#include "PhysicsPlaygroundListener.h"
#include <string>
class AttackScene : public Scene
{
public:
	AttackScene(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	void ReattachCamera();

	void Defeated();

	void CheckShield();
	
	void ChangeVisualState(int shadowEntity);

	void SpawnBullet(int shadowEntity);
	void ShootBullet();

	void ActivateShadow();

	std::string defaultPose = "testCube.png";
	std::string attackPose = "testCube2.png";

protected:
	PhysicsPlaygroundListener listener;
	int player = 0;
	int enemy1 = 0, enemy1Trigger = 0;
	int enemy2 = 0, enemy2Trigger = 0;
	int shield = 0;
	int bullet = 0;
	int boss = 0;
	bool canMove = true; //turns false for a few seconds when the player hits a Shadow and gets knocked back
};

