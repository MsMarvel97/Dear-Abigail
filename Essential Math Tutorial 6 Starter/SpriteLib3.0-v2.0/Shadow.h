#pragma once

#include "Scene.h"
#include "PhysicsPlaygroundListener.h"
#include <string>
#include <math.h>
class Shadow : public Scene
{
public:
	Shadow(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	/*void MoveBullet();*/

	void MakeBullet();

	void ReattachCamera();

	void TestFunction();

	bool testVariable = true;

private:
	PhysicsPlaygroundListener listener;
	int player;
	int shadow;
	int bullet;
};

