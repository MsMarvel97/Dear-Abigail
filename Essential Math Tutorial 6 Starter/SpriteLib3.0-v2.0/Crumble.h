#pragma once

#include "Scene.h"
#include "PhysicsPlaygroundListener.h"
#include <string>
class Crumble : public Scene
{
public:
	Crumble(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	void ReattachCamera();

	void OutputTime();

	void TestFunction(int platNum, int trigNum);//for test function

	void NewTrigger();
	void NewPlatform();

	void PleaseHelp(int entity);

	float timer = 0.f; //for test function

protected:
	PhysicsPlaygroundListener listener;
	int player;
	int toCrumble;
	int triggerRemove;
	int cPlatforms[10];
	int cTriggers[10];

	float startTime;//captures the time at which the player enters the trigger and adds x amount seconds for however long the platform should remain standing
	float respawnTime;//for crumbling platforms
	bool destroyed = false;//for crumbling platforms
};

