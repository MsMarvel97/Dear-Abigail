#pragma once 
#include "Scene.h" 
#include "PhysicsPlayground.h"

class AngerLevel : public Scene
{
public:
	AngerLevel(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	//functions to be called during scene initialization to build their respective scene elements
	void SpawnPlatforms();
	void SpawnCrumblingPlatforms();
	void SpawnTiles();
	void SpawnUI();
	void SpawnShadows();
	void SpawnMovingPlatforms();
	void SpawnSpikes();

	void Update() override;

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

	void ReattachCamera();

	/*void Defeated();*/

	void CheckShield();

	void ChangeVisualState(int shadowEntity);

	void SpawnBullet(int shadowEntity);
	void ShootBullet();

	void ActivateShadow();

	void Separate(b2Vec2(newPair), int type);

	void MoveShadow(int shadow);

	void MovePlatform();

	void PlayerDeath();

	void MouseClick(SDL_MouseButtonEvent evnt);

	void UpdatePositionWithCamera(int cameraEntity, int spriteEntity, int tempOffsetX, int tempOffsetY);

	void UpdateUI();

	b2Vec2 CalculateAngle(int entityOne, int entityTwo);

	std::string defaultPose = "testCube.png";
	std::string attackPose = "testCube2.png";
	std::string shieldOn = "ShieldOn.png";
	std::string shieldOff = "ShieldOff.png";
	std::string punchOn = "PunchOn.png";
	std::string punchOff = "PunchOff.png";
	bool switchDir = false;
	int bossPlatforms[6] = { 0,0,0,0,0,0 }; //last index is reserved for platform ZA
	int bossPlatformTriggers[6] = { 0,0,0,0,0,0 }; //last index is reserved for platform ZA
	int bigBossPlat[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int bigBossPlatTrig[10];
	int cPlatforms[4] = { 0,0,0,0 };
	int cTriggers[4] = { 0,0,0,0 };
	void CrumblingPlatforms(int entity);
	int flyingPieces[6] = { 0, 0, 0, 0, 0, 0 };

	int masterCrumblingPlatforms[20];

	void TestUpdatePosition(int cameraEntity, int bodyEntity, int tempOffsetX, int tempOffsetY);
protected:
	PhysicsPlaygroundListener listener;
	vec3 playerVel;
	b2Vec2 playerPos;
	int player = 0;
	int camera = 0;
	int shadows[6]; //shadows
	int sZones[6]; //shadow area trigger
	int enemy1 = 0, enemy2 = 0, enemy3 = 0, enemy4 = 0, enemy5 = 0, enemy6 = 0;
	int bossWall = 0; //aka
	bool bossWallDestroyed = false;
	int shield = 0;
	int bullet = 0;
	int boss = 0;
	int movingPlat = 0;
	int kinTrigger = 0;
	bool allShadowsDefeated = true;
	bool canMove = true; //turns false for a few seconds when the player hits a Shadow and gets knocked back
	int breakableWalls[1] = { 0 };
	int breakableWallTriggers[1] = { 0 };
	int hearts[3] = { 0,0,0 };
	int shieldUI = 0;
	int attackUI = 0;
	int ouchUI = 0;
	//UI ELEMENTS\\
	//0 = left heart
	//1 = middle heart
	//2 = right heart
	//3 = shield available icon
	//4 = shield active icon
	//5 = punch available icon
	//6 = punch active icon
	//7 = ouch icon
	int uiElements[7]; 

	//MOVING PLATFORMS\\
	//0 = Horizontal platform near level start
	//1 = Vertical platform near level end
	int movingPlatforms[1];
	//Parallel array of triggers for above platforms
	int movingTriggers[1];
};