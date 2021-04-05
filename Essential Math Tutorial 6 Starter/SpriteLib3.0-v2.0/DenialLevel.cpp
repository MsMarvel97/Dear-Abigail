#include "DenialLevel.h"
#include "Utilities.h"
//#include "ToneFire.h"

//Denial constructor
DenialLevel::DenialLevel(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(0.f, -98.f);
	m_physicsWorld->SetGravity(m_gravity);
	m_physicsWorld->SetContactListener(&listener);
}

//SCENE CONSTRUCTION FUNCTIONS\\
//This function builds the scene
void DenialLevel::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register
	m_sceneReg = new entt::registry;
	m_physicsWorld = new b2World(m_gravity);
	m_physicsWorld->SetContactListener(&listener);
	SetSceneChange(false, -1);

	//Attach the register
	ECS::AttachRegister(m_sceneReg);
	
	//Setting up background music
	{
		//denialBGM.Play();
		//denialBGM.SetVolume(4.5f);
	}
	
	//Spawning camera
	SpawnMainCamera(windowWidth, windowHeight);

	//Abigail entity
	SpawnMainPlayer(-450.f, 30.f);
	//DEBUGGING POSITIONS\\
	//tempDef.position.Set(float32(744.5), float32(187.5));
	//tempDef.position.Set(float32(1550), float32(447));
	ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).SetPosition(b2Vec2 (1550.f, 447.f), true);

	//resetting vars
	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetCheckpoint(false);
	ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).SetComplete(false);

	//Temp Shield
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shield = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<Kinematics>(entity);


		//Sets up components
		std::string fileName = "ShieldTemp.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 32, 48);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(float32(1952.f), float32(632.f), 2.f));

		ECS::GetComponent<Kinematics>(entity).SetChild(entity);
		ECS::GetComponent<Kinematics>(entity).SetParent(MainEntities::MainPlayer());
		ECS::GetComponent<Kinematics>(entity).SetOffset(0.f, 0.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		tempSpr.SetTransparency(0.f);
	} 

	//calling the SpawnPlatforms function to construct the static platforms
	SpawnPlatforms();
	//calling the SpawnCrumblingPlatforms function to construct the crumbling platforms
	SpawnCrumblingPlatforms();
	//calling the SpawnTiles function to construct the background tiles
	SpawnTiles();
	//calling the SpawnShadow function to spawn shadows
	SpawnShadows();
	//calling the SpawnUI function to construct the UI elements
	SpawnUI();
	//calling the SpawnMovingPlatforms function to construct the moving platforms
	SpawnMovingPlatforms();

	//focusing the camera on the player
	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}
//This function constructs all of the static platforms during scene initialization
void DenialLevel::SpawnPlatforms()
{
	SpawnPlatform(-20.f, 8.f, 1000.f, 16.f, "platformA.png", 0.f);//Platform A (bottom 0-30)

	SpawnPlatform(-510.f, 240.f, 480.f, 16.f, "platformA.png", 0.f);//Platform A2

	SpawnPlatform(640.f, 8.f, 320.f, 16.f, "platformB.png", 0.f);//Platform B (bottom 30-50)

	SpawnPlatform(824.f, 80.f, 48.f, 160.f, "platformC.png", 0.f);//Platform C (Wall)

	SpawnPlatform(736.f, 32.f, 128.f, 32.f, "platformD.png", 0.f);//Platform D (raised platform)

	SpawnPlatform(776.f, 64.f, 48.f, 32.f, "platformE.png", 0.f);//Platform E (raised platform stacked)

	SpawnPlatform(648.f, 104.f, 144.f, 16.f, "platformF.png", 1.f);//Platform F (floating platform)

	SpawnPlatform(512.f, 104.f, 32.f, 16.f, "platformG.png", 1.f);//Platform G (floating platform)

	SpawnPlatform(440.f, 104.f, 48.f, 16.f, "platformH.png", 1.f);//Platform H (floating platform)

	SpawnPlatform(352.f, 104.f, 32.f, 16.f, "platformI.png", 0.f);//Platform I (floating platform)

	SpawnPlatform(320.f, 120.f, 32.f, 48.f, "platformJ.png", 0.f);//Platform J (floating platform)	

	SpawnPlatform(976.f, 168.f, 480.f, 16.f, "platformK.png", 0.f);//Platform K (46-76 elevated ground)

	SpawnPlatform(1328.f, 168.f, 224.f, 16.f, "boxSprite.jpg", 0.f);//Platform L (76-90 elevated platform)

	SpawnPlatform(1464.f, 232.f, 48.f, 144.f, "boxSprite.jpg", 0.f);//Platform M (elevated wall)	

	SpawnPlatform(800.f, 192.f, 32.f, 32.f, "boxSprite.jpg", 0.f);//Platform N (raised platform)

	SpawnPlatform(1032.f, 264.f, 48.f, 16.f, "platformO.png", 1.f);//Platform O (floating platform)	

	SpawnPlatform(1504.f, 320.f, 480.f, 32.f, "boxSprite.jpg", 0.f);//Platform P (79-109 highest ground platform)

	SpawnPlatform(1912.f, 320.f, 336.f, 32.f, "boxSprite.jpg", 0.f);//Platform Q (109-130 highest ground platform)

	SpawnPlatform(1536.f, 360.f, 64.f, 16.f, "platformR.png", 1.f);//Platform R (floating platform)

	SpawnPlatform(1800.f, 446.f, 80.f, 16.f, "platformS.png", 1.f);//Platform S (floating platform)	

	SpawnPlatform(1968.f, 456.f, 128.f, 16.f, "platformT.png", 1.f);//Platform T (floating platform)	

	SpawnPlatform(1928.f, 616.f, 208.f, 16.f, "platformU.png", 1.f);//Platform U (floating platform)

	SpawnPlatform(845.f, 610.f, 80.f, 10.f, "platformT.png", 1.f);//exit platform
}
//This function constructs all of the crumbling platforms during scene initialization
void DenialLevel::SpawnCrumblingPlatforms()
{
	cPlatforms[0] = SpawnCrumblingPlatform(872.f, 224.f);//Platform M2 (crumbling platform)

	cPlatforms[1] = SpawnCrumblingPlatform(952.f, 240.f);//Platform M3 (crumbling platform)	

	cPlatforms[2] = SpawnCrumblingPlatform(1112.f, 272.f);//Platform M4 (crumbling platform)	

	cPlatforms[3] = SpawnCrumblingPlatform(1192.f, 304.f);//Platform M5 (crumbling platform)	

	cPlatforms[4] = SpawnCrumblingPlatform(1624.f, 384.f);//Platform M6

	cPlatforms[5] = SpawnCrumblingPlatform(1704.f, 416.f);//Platform M7 (crumbling platform)

	//Creates line of crumbling platforms
	float crumblingX = 1430.f;
	for (int i = 0; i <= 11; i++)
	{
		cPlatforms[i + 6] = SpawnCrumblingPlatform(crumblingX, 580.5);
		crumblingX -= 48;
	}
}
//This function constructs all of the shadows and bullet walls during scene initialization
void DenialLevel::SpawnShadows()
{
	//array for holding shadow b2Vec2s before they can be unpacked
	b2Vec2 newShadows[5];

	//spawning shadows with their associated triggers
	newShadows[0] = SpawnShadow(248.f, 88.f, 0.f, 272.f, true, b2Vec2(30.f, 0.f));
	newShadows[1] = SpawnShadow(545.f, 216.f, 438.f, 698.f, true, b2Vec2(30.f, 0.f));
	newShadows[2] = SpawnShadow(1033.f, 380.f, 794.f, 1252.f, true, b2Vec2(50.f, 10.f));
	newShadows[3] = SpawnShadow(1752.f, 536.f, 1652.f, 1852.f, true, b2Vec2(30.f, 15.f));
	newShadows[4] = SpawnShadow(1118.f, 670.f, 950.f, 1286.f, true, b2Vec2(20.f, 0.f));

	//separating all the entities from their triggers and placing them in their respective arrays
	for (int i = 0; i <= 4; i++)
	{
		Separate(newShadows[i], 0);
	}

	bulletWalls[0] = SpawnBulletWall(-260.f, 80.f);
	bulletWalls[1] = SpawnBulletWall(512.f, 87.f);
	bulletWalls[2] = SpawnBulletWall(1286.f, 650.f);
	bulletWalls[3] = SpawnBulletWall(950.f, 650.f);
}
//This function constructs all of the moving platforms during scene initialization
void DenialLevel::SpawnMovingPlatforms()
{
	b2Vec2 movingPlatforms[2];

	movingPlatforms[0] = SpawnMovingPlatform(392.f, 148.f, 380.f, 670.f, 0, 80.f, 8.f);
	movingPlatforms[1] = SpawnMovingPlatform(1504.f, 408.f, 408.f, 588.f, 1, 96.f, 16.f);

	for (int i = 0; i <= 1; i++)
	{
		Separate(movingPlatforms[i], 1);
	}
}
//This function constructs all of the background tiles during scene initialization
void DenialLevel::SpawnTiles()
{
	SpawnTile(845.f, 635.f, "CaveExit.png", true, 2.f, 20.f, 40.f); //Cave exit sprite-entity

	SpawnTile(-640.f, -176.f, "backgrounds/denial0-0.png");// TILE -2-0

	SpawnTile(-384.f, -176.f, "backgrounds/denial0-0.png");

	SpawnTile(-128.f, -176.f, "backgrounds/denial0-0.png");// TILE 0-0

	SpawnTile(128.f, -176.f, "backgrounds/denial1-0.png");// TILE 1-0

	SpawnTile(384.f, -176.f, "backgrounds/denial2-0.png");// TILE 2-0		

	SpawnTile(640.f, -176.f, "backgrounds/denial3-0.png");// TILE 3-0		

	SpawnTile(896.f, -176.f, "backgrounds/denial4-0.png");// TILE 4-0		

	SpawnTile(1152.f, -176.f, "backgrounds/denial5-0.png");// TILE 5-0		

	SpawnTile(1408, -176.f, "backgrounds/denial6-0.png");// TILE 6-0		

	SpawnTile(1664.f, -176.f, "backgrounds/denial7-0.png");// TILE 7-0		

	SpawnTile(-640.f, 80.f, "backgrounds/denial-2-1.png");//TILE -2-1		

	SpawnTile(-384.f, 80.f, "backgrounds/denial-1-1.png");//TILE -1-1		

	SpawnTile(-128.f, 80.f, "backgrounds/denial0-1.png");// TILE 0-1

	SpawnTile(128.f, 80.f, "backgrounds/denial1-1.png");// TILE 1-1

	SpawnTile(384.f, 80.f, "backgrounds/denial2-1.png");// TILE 2-1		

	SpawnTile(640.f, 80.f, "backgrounds/denial3-1.png");// TILE 3-1		

	SpawnTile(896.f, 80.f, "backgrounds/denial4-1.png");// TILE 4-1

	SpawnTile(1152.f, 80.f, "backgrounds/denial5-1.png");// TILE 5-1		

	SpawnTile(1408.f, 80.f, "backgrounds/denial6-1.png");// TILE 6-1		

	SpawnTile(1664.f, 80.f, "backgrounds/denial7-1.png");// TILE 7-1

	SpawnTile(1920.f, 80.f, "backgrounds/denial8-1.png");// TILE 8-1

	SpawnTile(2176.f, 80.f, "backgrounds/denial9-1.png");// TILE 9-1

	SpawnTile(-128.f, 336.f, "backgrounds/denial0-2.png");// TILE 0-2

	SpawnTile(128.f, 336.f, "backgrounds/denial1-2.png");// TILE 1-2

	SpawnTile(384.f, 336.f, "backgrounds/denial2-2.png");// TILE 2-2

	SpawnTile(640.f, 336.f, "backgrounds/denial3-2.png");// TILE 3-2

	SpawnTile(896.f, 336.f, "backgrounds/denial4-2.png");// TILE 4-2

	SpawnTile(1152.f, 336.f, "backgrounds/denial5-2.png");// TILE 5-2

	SpawnTile(1408.f, 336.f, "backgrounds/denial6-2.png");// TILE 6-2

	SpawnTile(1664.f, 336.f, "backgrounds/denial7-2.png");// TILE 7-2

	SpawnTile(1920.f, 336.f, "backgrounds/denial8-2.png");// TILE 8-2

	SpawnTile(2176.f, 336.f, "backgrounds/denial9-2.png");// TILE 9-2

	SpawnTile(-128.f, 592.f, "backgrounds/denial0-3.png");// TILE 0-2

	SpawnTile(128.f, 592.f, "backgrounds/denial1-3.png");// TILE 1-2

	SpawnTile(384.f, 592.f, "backgrounds/denial2-3.png");// TILE 2-2

	SpawnTile(640.f, 592.f, "backgrounds/denial3-3.png");// TILE 3-2

	SpawnTile(896.f, 592.f, "backgrounds/denial4-3.png");// TILE 4-2

	SpawnTile(1152.f, 592.f, "backgrounds/denial5-3.png");// TILE 5-3

	SpawnTile(1408.f, 592.f, "backgrounds/denial6-3.png");// TILE 6-3

	SpawnTile(1664.f, 592.f, "backgrounds/denial7-3.png");// TILE 7-3

	SpawnTile(1920.f, 592.f, "backgrounds/denial0-3.png");// TILE 8-3

	SpawnTile(2176.f, 592.f, "backgrounds/denial9-3.png");// TILE 9-3

	SpawnTile(1152.f, 848.f, "backgrounds/denial5-4.png");// TILE 5-4

	SpawnTile(1408.f, 848.f, "backgrounds/denial6-4.png");// TILE 6-4

	SpawnTile(1664.f, 848.f, "backgrounds/denial7-4.png");// TILE 7-4

	SpawnTile(1920.f, 848.f, "backgrounds/denial8-4.png");// TILE 8-4

	SpawnTile(2176.f, 848.f, "backgrounds/denial9-4.png");// TILE 9-4
}
//This function constructs all the UI elements and stores them in the uiElements array
void DenialLevel::SpawnUI()
{

	uiElements[0] = Scene::SpawnUIElement(-120.f, 65.f, 20, 20, "heart.png");
	uiElements[1] = Scene::SpawnUIElement(-100.f, 65.f, 20, 20, "heart.png");
	uiElements[2] = Scene::SpawnUIElement(-80.f, 65.f, 20, 20, "heart.png");
	uiElements[3] = Scene::SpawnUIElement(115.f, -60.f, 30, 30, "shieldOff.png");
	uiElements[4] = Scene::SpawnUIElement(115.f, -60.f, 30, 30, "shieldOn.png");

	ECS::GetComponent<Sprite>(uiElements[4]).SetTransparency(0.f);
}
//END OF SCENE CONSTRUCTION FUNCTIONS\\


//UPDATE FUNCTIONS\\
//Update loop for Denial level
void DenialLevel::Update()
{
	auto& playerBody = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& player = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	auto& pMechanics = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	auto& sprite = ECS::GetComponent<Sprite>(MainEntities::MainPlayer());

	pMechanics.RunKnockBackTime();

	for (int i = 0; i <= 1; i++)
	{
		ECS::GetComponent<Kinematics>(movingTriggers[i]).UpdatePosition();
		ECS::GetComponent<MovingPlatform>(movingPlatforms[i]).MovePlatform(movingPlatforms[i]);
	}

	ECS::GetComponent<Kinematics>(shield).UpdateTransform();

	if (pMechanics.GetCanMove() == true)
	{
		player.Update();
	}

	fmod.Update();

	for (int i = 0; i <= 17; i++)
	{
		ECS::GetComponent<CrumblingSequence>(cPlatforms[i]).Crumble(cPlatforms[i]);
		CrumblingPlatforms(cPlatforms[i]);
	}

	for (int i = 0; i <= 4; i++)
	{
		ActivateShadow(shadows[i]);
	}

	for (int i = 0; i <= 4; i++)
	{
		ECS::GetComponent<Kinematics>(sZones[i]).UpdatePosition();
	}

	for (int i = 0; i <= 3; i++)
	{
		SpawnBullet(bulletWalls[i], 0, -13);
	}

	if (pMechanics.GetShield())
	{
		ECS::GetComponent<Sprite>(shield).SetTransparency(1.f);
	}
	else
	{
		ECS::GetComponent<Sprite>(shield).SetTransparency(0.f);
	}

	std::cout << playerBody.GetPosition().x <<  "					" << playerBody.GetPosition().y << std::endl;

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).Update();
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).Update();

	for (int i = 0; i <= 4; i++)
	{
		ECS::GetComponent<Kinematics>(uiElements[i]).UpdateUI();
	}

	sprite.SetTransparency(1.f);
	CheckUIConditions();
	CheckEndLevel();
}
//Called in each update to update the shadow loop and call bullet functions
void DenialLevel::ActivateShadow(int shadow)
{
	//Checks to see if the appropriate amount of seconds of passed between now and the last shot. 
	//If so, a bullet is fired from a shadow determined by the player's location.
	auto& pMechanics = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	auto& shade = ECS::GetComponent<ShadowLoop>(shadow);

	shade.ShadowRoutine(shadow);

	if (shade.GetFiring() && shade.GetShadowSequence())
	{
		SpawnBullet(shadow);
	}
}
//This function is called in each update to check conditions governing each UI element and updates the elements accordingly
void DenialLevel::CheckUIConditions()
{
	auto& player = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());
	auto& pPhysics = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());

	switch (player.GetHealth())
	{
	case 0: //respawning the player at either start or middle depending on whether they have made it more than halfway through level
		if (player.GetCheckpoint())
		{
			pPhysics.SetPosition(b2Vec2(1285.f, 347.f));
		}
		else
		{
			pPhysics.SetPosition(b2Vec2(-450.f, 30.f));
		}
		player.SetHealth(3);
		
		for (int i = 1; i <= 2; i++)
		{
			ECS::GetComponent<Sprite>(uiElements[i]).SetTransparency(1.f);
		}
		break;

	case 1: 
		ECS::GetComponent<Sprite>(uiElements[1]).SetTransparency(0.f);
		break;

	case 2:
		ECS::GetComponent<Sprite>(uiElements[2]).SetTransparency(0.f);
		break;
	}

	if (player.GetShield())
	{
		ECS::GetComponent<Sprite>(uiElements[3]).SetTransparency(0.f);
		ECS::GetComponent<Sprite>(uiElements[4]).SetTransparency(1.f);
	}
	else
	{
		ECS::GetComponent<Sprite>(uiElements[3]).SetTransparency(1.f);
		ECS::GetComponent<Sprite>(uiElements[4]).SetTransparency(0.f);
	}

	if (pPhysics.GetPosition().x >= 700.f)
	{
		player.SetCheckpoint(true);
	}

}
//This function is called each update to check if the end of the level has been reached. If it has, this also changes the scene.
void DenialLevel::CheckEndLevel()
{
	if (ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer()).GetComplete())
	{
		SetSceneChange(true, 2);
	}
}
//platform for making platforms crumble - pass crumbling platforms to this during the update
void DenialLevel::CrumblingPlatforms(int entity)
{
	if (ECS::GetComponent<CrumblingSequence>(entity).disablePlatform() != -1)
	{
		if (ECS::GetComponent<CrumblingSequence>(entity).disablePlatform() == 0)
		{
			ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
			ECS::GetComponent<PhysicsBody>(entity).GetBody()->SetActive(true);
			ECS::GetComponent<CrumblingSequence>(entity).disable = false;
		}
		else if (ECS::GetComponent<CrumblingSequence>(entity).disablePlatform() == 1)
		{
			ECS::GetComponent<PhysicsBody>(entity).GetBody()->SetActive(false);
			ECS::GetComponent<CrumblingSequence>(entity).disable = false;
		}
	}
}
//END OF UPDATE FUNCTIONS\\


//BULLET FUNCTIONS\\
//Spawns bullets from shadows
void DenialLevel::SpawnBullet(int shadow)
{
	auto& shadowBody = ECS::GetComponent<PhysicsBody>(shadow);
	float tempX = shadowBody.GetBody()->GetPosition().x; //directly subbing in the GetBody line throws an error
	float tempY = shadowBody.GetBody()->GetPosition().y;
	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Trigger*>(entity);

	//Set up components
	std::string fileName = "bullet.png";
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 4, 8);

	ECS::GetComponent<Transform>(entity).SetPosition(vec3(tempX, tempY, 4.f));

	ECS::GetComponent<Trigger*>(entity) = new BulletTrigger();
	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_dynamicBody;
	tempDef.position.Set(tempX, tempY);

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | GROUND | ENVIRONMENT);
	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	tempPhsBody.SetGravityScale(0.f); //ensures no bullet drop and bullet reaches the player

	ShootBullet(entity);
}
//Shoots bullets spawned by shadows
void DenialLevel::ShootBullet(int bullet)
{
	//shootBulletSound.Play();
	//shootBulletSound.SetVolume(5.0f);
	b2Vec2 angle = CalculateAngle(MainEntities::MainPlayer(), bullet);

	float dirAngle = atan(angle.x / angle.y) * (180 / PI);

	ECS::GetComponent<PhysicsBody>(bullet).SetRotationAngleDeg(dirAngle * -1);
	ECS::GetComponent<PhysicsBody>(bullet).GetBody()->SetLinearVelocity(b2Vec2(angle.x * 100, angle.y * 100));

	float x = ECS::GetComponent<PhysicsBody>(bullet).GetVelocity().x;
	float y = ECS::GetComponent<PhysicsBody>(bullet).GetVelocity().y;
}
//Spawns bullets from bullet walls
void DenialLevel::SpawnBullet(int wall, float offsetX, float offsetY)
{
	static float startTime = 0;
	auto& wallLoc = ECS::GetComponent<PhysicsBody>(wall);

	if (startTime == 0)
	{
		startTime = Timer::time;
	}

	float currentTime = Timer::StopWatch(startTime);

	if (currentTime >= 0.3) //this statement will run once the player has entered a ShadowAreaTrigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Set up components
		std::string fileName = "bullet.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 4, 8);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(wallLoc.GetPosition().x + offsetX, wallLoc.GetPosition().y + offsetY, 4.f));

		ECS::GetComponent<Trigger*>(entity) = new BulletTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(wallLoc.GetPosition().x + offsetX, wallLoc.GetPosition().y + offsetY);

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | GROUND | ENVIRONMENT);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

		tempPhsBody.SetGravityScale(0.f); //ensures no bullet drop and bullet reaches the player

		ShootBullet(entity, 0);

		if (wall == bulletWalls[3]) //this has to be equal to the last entry in the bulletWalls array. If it isn't, any elements after this number will not spawn bullets.
		{
			startTime = 0;
		}
	}
}
//shoots bullets spawned by bullet walls
void DenialLevel::ShootBullet(int bullet, float degrees)
{
	ECS::GetComponent<PhysicsBody>(bullet).SetRotationAngleDeg(degrees);
	ECS::GetComponent<PhysicsBody>(bullet).GetBody()->SetLinearVelocity(b2Vec2(0, -100));
}
//END OF BULLET FUNCTIONS\\


//Returns the delta x and delta y as a b2vec2 to be used for angle calculations
b2Vec2 DenialLevel::CalculateAngle(int entityOne, int entityTwo)
{
	float deltaX = 0, deltaY = 0;
	deltaX = ECS::GetComponent<PhysicsBody>(entityOne).GetBody()->GetPosition().x - ECS::GetComponent<PhysicsBody>(entityTwo).GetBody()->GetPosition().x;
	deltaY = ECS::GetComponent<PhysicsBody>(entityOne).GetBody()->GetPosition().y - ECS::GetComponent<PhysicsBody>(entityTwo).GetBody()->GetPosition().y;

	return b2Vec2(deltaX, deltaY);
}
//Splits a b2Vec2 container for an entity/trigger pair into its components and adds them to their respective arrays (0 for shadow, 1 for moving platform)
void DenialLevel::Separate(b2Vec2 newPair, int type)
{
	if (type == 0)
	{
		int static shadowID = 0;
		shadows[shadowID] = newPair.x;
		sZones[shadowID] = newPair.y;
		shadowID++;
	}
	else
	{
		int static movingID = 0;
		movingPlatforms[movingID] = newPair.x;
		movingTriggers[movingID] = newPair.y;
		movingID++;
	}
}

void DenialLevel::KeyboardHold()
{
}

void DenialLevel::KeyboardUp()
{
}

void DenialLevel::KeyboardDown()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	float speed = 1.f;
	b2Vec2 vel = b2Vec2(0.f, 0.f);

	playerVel = player.GetVelocity();
	playerPos = player.GetPosition();

	if (Input::GetKeyDown(Key::M))
	{
		std::cout << "X Pos: " << playerPos.x << std::endl;
		std::cout << "Y Pos: " << playerPos.y << std::endl << std::endl;
	}
}