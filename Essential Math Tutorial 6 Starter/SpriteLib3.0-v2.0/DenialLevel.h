#pragma once
#include "Scene.h"
#include "PhysicsPlayground.h"

class DenialLevel : public Scene
{
public:
	DenialLevel(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;

	//functions to be called during scene initialization to build their respective scene elements
	void SpawnPlatforms();
	void SpawnCrumblingPlatforms();
	void SpawnTiles();
	void SpawnUI();
	void SpawnShadows();
	void SpawnMovingPlatforms();

	void Update() override;

	void KeyboardHold() override;
	void KeyboardUp() override;
	void KeyboardDown() override;

	void CrumblingPlatforms(int entity);




	void SpawnBullet(int shadow);
	void SpawnBullet(int wall, float offsetX, float offsetY);


	void CheckUIConditions();
	void CheckEndLevel();

	void ShootBullet(int bullet); //shoots bullets with an angle determined between player and origin
	void ShootBullet(int bullet, float degrees); //shoots bullets at a fixed angle

	void ActivateShadow(int shadow);

	//sends a pair and splits it. Types are 0 = Shadow, 1 = Moving Platform.
	void Separate(b2Vec2(newPair), int type);
	//calculates the delta X and Y between two entities and returns them in a b2Vec2 to be used for angle calculation (DOES NOT RETURN ANGLE DEGREES)
	b2Vec2 CalculateAngle(int entityOne, int entityTwo);



protected:
	PhysicsPlaygroundListener listener;


	//UI ELEMENTS\\
	//0 = left heart
	//1 = middle heart
	//2 = right heart
	//3 = shield available icon
	//4 = shield active icon
	int uiElements[5];
	//shield (temp)
	int shield = 0;
	
	//MOVING PLATFORMS\\
	//0 = Horizontal platform near level start
	//1 = Vertical platform near level end
	int movingPlatforms[2];
	//Parallel array of triggers for above platforms
	int movingTriggers[2];

	//CRUMBLING PLATFORMS\\

	int cPlatforms[18];
	int shadows[5];
	int sZones[5];
	int bulletWalls[4];
	int bullet = 0;


	vec3 playerVel; //track player velocity to get y value
	b2Vec2 playerPos; //track player's position

private:
	ToneFire::CoreSound shootBulletSound{ "shadowBulletThree.wav",false,false,true };
	ToneFire::CoreSound denialBGM{ "denialBGM.wav", false, false, true };
	ToneFire::CoreSound crumbleSound{ "crumble.wav", false, false, true };
	ToneFire::CoreSound abigailHit{ "abigailHitOne.wav", false, false, true };
};

