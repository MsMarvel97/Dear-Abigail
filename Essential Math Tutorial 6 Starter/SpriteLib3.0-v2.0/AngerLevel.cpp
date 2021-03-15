#include "AngerLevel.h" 
#include "Utilities.h" 

#include <random> 

AngerLevel::AngerLevel(std::string name)
	: Scene(name)
{
	//No gravity this is a top down scene 
	m_gravity = b2Vec2(0.f, -98.f);
	m_physicsWorld->SetGravity(m_gravity);
	m_physicsWorld->SetContactListener(&listener);
}

void AngerLevel::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register 
	m_sceneReg = new entt::registry;

	//Attach the register 
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera 
	float aspectRatio = windowWidth / windowHeight;

	//Setup MainCamera Entity 
	{
		//Creates Camera entity 
		auto entity = ECS::CreateEntity();
<<<<<<< Updated upstream
=======
		camera = entity;
>>>>>>> Stashed changes
		ECS::SetIsMainCamera(entity, true);

		//Creates new orthographic camera 
		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<VerticalScroll>(entity);

<<<<<<< Updated upstream
		vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f);
=======
		vec4 temp = vec4(-75, 75, -75, 75);//formally 75
>>>>>>> Stashed changes
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		//Attaches the camera to vert and horiz scrolls 
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	}


<<<<<<< Updated upstream
	//rat entity 
=======
	//main player entity 
>>>>>>> Stashed changes
	{

		auto entity = ECS::CreateEntity();
		ECS::SetIsMainPlayer(entity, true);
<<<<<<< Updated upstream

		//Add components 
		ECS::AttachComponent<Player>(entity);
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<CanJump>(entity);

		//Sets up the components 
		std::string fileName = "ratspritesheet.png";
		std::string animations = "rat.json";

		ECS::GetComponent<Player>(entity).InitPlayer(fileName, animations, 20, 30, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity), &ECS::GetComponent<Transform>(entity));
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 2.f));
=======
		player = entity;
		//Add components 
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<CanJump>(entity);
		ECS::AttachComponent<AttackMechanic>(entity);//to remove
		ECS::AttachComponent<Health>(entity);//to remove
		ECS::AttachComponent<Player>(entity);
		ECS::AttachComponent<KnockBack>(entity);//to remove
		ECS::AttachComponent<CoolDown>(entity);
		ECS::AttachComponent<BossLevel>(entity);
		ECS::AttachComponent<ShadowSense>(entity);//to remove
		ECS::AttachComponent<ShadowTime>(entity);//to remove
		ECS::AttachComponent<MovingClass>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PlayerMechanics>(entity);

		//Sets up the components 
		std::string fileName = "spritesheets/abigailSpritesheet.png";
		std::string animations = "abigailAnimations.json";

		ECS::GetComponent<Player>(entity).InitPlayer(fileName, animations, 25, 25, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity), &ECS::GetComponent<Transform>(entity));
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 2.f));
		ECS::GetComponent<Health>(entity).SetHealth(3);
>>>>>>> Stashed changes

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

<<<<<<< Updated upstream
		float shrinkX = 6.f;
		float shrinkY = 17.f;

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(10.f), float32(10.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, PLAYER, ENEMY | OBJECTS | PICKUP | TRIGGER | SNAIL, 0.5f, 3.f);
=======
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(0.f), float32(60.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth()-8), float(tempSpr.GetHeight()-3), vec2(0.f, 0.f), false, PLAYER, ENEMY | OBJECTS | PICKUP | TRIGGER | SNAIL, 0, 1);
>>>>>>> Stashed changes
		//tempPhsBody = PhysicsBody(entity, tempBody, float((tempSpr.GetHeight() - shrinkY) / 2.f), vec2(0.f, 0.f), false, PLAYER, ENEMY | OBJECTS | PICKUP | TRIGGER | SNAIL, 0.5f, 3.f); 

		tempPhsBody.SetRotationAngleDeg(0.f);
		tempPhsBody.SetFixedRotation(true);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
<<<<<<< Updated upstream
		tempPhsBody.SetGravityScale(3.5f);
	}

=======
		tempPhsBody.SetGravityScale(0.75f);
	}

	//Set up shield
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shield = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		/*ECS::AttachComponent<PhysicsBody>(entity);*/
		ECS::AttachComponent<Kinematics>(entity);
		ECS::AttachComponent<ShieldMechanic>(entity);


		double playerSpriteX = ECS::GetComponent<Sprite>(player).GetWidth();
		double playerSpriteY = ECS::GetComponent<Sprite>(player).GetHeight();

		//Sets up components
		std::string fileName = "shield.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, playerSpriteX, playerSpriteY);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 4.f));
		ECS::GetComponent<Kinematics>(entity).SetChild(entity);
		ECS::GetComponent<Kinematics>(entity).SetParent(player);
		ECS::GetComponent<Kinematics>(entity).SetOffset(0.f, 0.f);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
	}
>>>>>>> Stashed changes

	//platform A
	{
		//Creates entity 
		auto entity = ECS::CreateEntity();

		//Add components 
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components 
		std::string fileName = "platform.png";
<<<<<<< Updated upstream
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16*12, 16*1);
=======
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 12, 16 * 1);
>>>>>>> Stashed changes
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32(0.f+(16*12/2)), float32(0.f + (16 / 2)));
=======
		tempDef.position.Set(float32(0.f + (16 * 12 / 2)), float32(0.f + (16 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform B 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 14, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 14.f) + (16 * 14/ 2)), float32((16 * 2.f) + (16 * 1/ 2)));
=======
		tempDef.position.Set(float32((16 * 14.f) + (16 * 14 / 2)), float32((16 * 2.f) + (16 * 1 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform C 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 30.f) + (16 * 16 / 2)), float32((16 * 0.f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
<<<<<<< Updated upstream
=======
	//Mini Platform
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(790), float32(15)); //(734,8)

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
>>>>>>> Stashed changes
	//Platform D 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "boxSprite.jpg";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 1, 16 * 15);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;//change to dynamic and this is meant to fall down like a bridge
		tempDef.position.Set(float32((16 * 44.f) + (16 * 1 / 2)), float32((16 * 0.f) + (16 * 15 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

<<<<<<< Updated upstream
		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, OBJECTS, GROUND | ENVIRONMENT | PLAYER,0.3f);
=======
		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, OBJECTS, GROUND | ENVIRONMENT | PLAYER, 0.3f);
>>>>>>> Stashed changes
		tempPhsBody.SetRotationAngleDeg(0.f);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
		tempPhsBody.SetFixedRotation(false);
		tempPhsBody.SetGravityScale(0.5f);
	}
	//Platform D_BridgeHelp_
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 1, 16 * 3);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 43.3f) + (16 * 1/ 2)), float32((16 * 0.f) + (16 * 3/ 2)));
=======
		tempDef.position.Set(float32((16 * 43.3f) + (16 * 1 / 2)), float32((16 * 0.f) + (16 * 3 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
<<<<<<< Updated upstream

=======
		tempSpr.SetTransparency(1.f);
>>>>>>> Stashed changes
	}
	//Platform D_BridgeHelp_2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
<<<<<<< Updated upstream
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 0.5f, 16 *0.5f);
=======
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 0.5f, 16 * 0.5f);
>>>>>>> Stashed changes
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 45.5f) + (16 * 0.5f / 2)), float32((16 * 1.f) + (16 * 0.5f / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}

	//Platform E
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 14, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 59.f) + (16 * 14 / 2)), float32((16 * 0.f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform F
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 12, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 75.f) + (16 * 12 / 2)), float32((16 * 2.f) + (16 * 1 / 2)));
=======
		tempDef.position.Set(float32((16 * 75.f) + (16 * 12 / 2)), float32((16 * 2.f) + (16 * 2 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
<<<<<<< Updated upstream
	
	//Platform G 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

=======
	/*
	//Platform G  //Random block
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		flyingPieces[0] = entity;
>>>>>>> Stashed changes
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
<<<<<<< Updated upstream
		std::string fileName = "boxSprite.jpg";
=======
		std::string fileName = "goose.png";
>>>>>>> Stashed changes
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;//change to dynamic
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 97.f) + (16 * 14 / 2)), float32((16 * 1.f) + (16 * 1 / 2)));
=======
		tempDef.position.Set(float32((16 * 97.f) + (16 * 14 / 2)), float32((16 * 1.f) + (16 * 1 / 2))); //(1664,8)
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, OBJECTS, GROUND | ENVIRONMENT | PLAYER, 0.3f);
		tempPhsBody.SetGravityScale(1.3f);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
		tempPhsBody.SetFixedRotation(false);
	}
<<<<<<< Updated upstream
	//Platform H 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

=======
	//Platform H  //Random block 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		flyingPieces[1] = entity;
>>>>>>> Stashed changes
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
<<<<<<< Updated upstream
		std::string fileName = "boxSprite.jpg";
=======
		std::string fileName = "goose.png";
>>>>>>> Stashed changes
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;//change to dynamic
		tempDef.position.Set(float32((16 * 100.f) + (16 * 14 / 2)), float32((16 * 1.f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, OBJECTS, GROUND | ENVIRONMENT | PLAYER, 0.3f);
		tempPhsBody.SetGravityScale(1.3f);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
		tempPhsBody.SetFixedRotation(false);

	}
<<<<<<< Updated upstream
	//Platform I 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

=======
	//Platform I  //Random block 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		flyingPieces[2] = entity;
>>>>>>> Stashed changes
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
<<<<<<< Updated upstream
		std::string fileName = "boxSprite.jpg";
=======
		std::string fileName = "goose.png";
>>>>>>> Stashed changes
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 3, 16 * 2);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;//change to dynamic
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 *98.5f) + (16 * 14 / 2)), float32((16 * 3.f) + (16 * 1 / 2)));
=======
		tempDef.position.Set(float32((16 * 98.5f) + (16 * 14 / 2)), float32((16 * 3.f) + (16 * 1 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, OBJECTS, GROUND | ENVIRONMENT | PLAYER, 0.3f);
		tempPhsBody.SetGravityScale(1.3f);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
		tempPhsBody.SetFixedRotation(false);
	}
<<<<<<< Updated upstream
	//Platform J 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

=======
	//Platform J  //Random block 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		flyingPieces[3] = entity;
>>>>>>> Stashed changes
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
<<<<<<< Updated upstream
		std::string fileName = "boxSprite.jpg";
=======
		std::string fileName = "goose.png";
>>>>>>> Stashed changes
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 1, 16 * 1);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;//change to dynamic
		tempDef.position.Set(float32((16 * 98.f) + (16 * 14 / 2)), float32((16 * 4.5f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, OBJECTS, GROUND | ENVIRONMENT | PLAYER, 0.3f);
		tempPhsBody.SetGravityScale(1.3f);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
		tempPhsBody.SetFixedRotation(false);
	}
<<<<<<< Updated upstream
	//Platform K 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

=======
	//Platform K  //Random block 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		flyingPieces[4] = entity;
>>>>>>> Stashed changes
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
<<<<<<< Updated upstream
		std::string fileName = "boxSprite.jpg";
=======
		std::string fileName = "goose.png";
>>>>>>> Stashed changes
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 1, 16 * 2);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;//change to dynamic
		tempDef.position.Set(float32((16 * 99.7f) + (16 * 14 / 2)), float32((16 * 5.f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, OBJECTS, GROUND | ENVIRONMENT | PLAYER, 0.3f);
		tempPhsBody.SetGravityScale(1.3f);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
		tempPhsBody.SetFixedRotation(false);
	}
<<<<<<< Updated upstream
	//Platform L 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

=======
	//Platform L  //Random block 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		flyingPieces[5] = entity;
>>>>>>> Stashed changes
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
<<<<<<< Updated upstream
		std::string fileName = "boxSprite.jpg";
=======
		std::string fileName = "goose.png";
>>>>>>> Stashed changes
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 1, 16 * 1);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;//change to dynamic
		tempDef.position.Set(float32((16 * 95.5f) + (16 * 14 / 2)), float32((16 * 0.5f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, OBJECTS, GROUND | ENVIRONMENT | PLAYER, 0.3f);
		tempPhsBody.SetGravityScale(1.3f);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));
		tempPhsBody.SetFixedRotation(false);
	}
<<<<<<< Updated upstream
=======
	//Outburst Trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "testCube.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 20);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new OutburstTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		for (int i = 0; i < 6; i++)
		{
			ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(flyingPieces[i]);
		}

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempSprite = ECS::GetComponent<Sprite>(entity);
		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1600), float32(40));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, tempSprite.GetWidth(), tempSprite.GetHeight(), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Outburst Trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "testCube.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 20);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new OutburstTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		for (int i = 0; i < 6; i++)
		{
			ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(flyingPieces[i]);
		}

		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempSprite = ECS::GetComponent<Sprite>(entity);
		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1700), float32(40));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, tempSprite.GetWidth(), tempSprite.GetHeight(), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	*/

>>>>>>> Stashed changes
	//Platform M 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
<<<<<<< Updated upstream
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 24, 16 * 1);
=======
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 25, 16 * 1);
>>>>>>> Stashed changes
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 89.f) + (16 * 24 / 2)), float32((16 * 0.f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform N 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 116.f) + (16 * 4 / 2)), float32((16 * 2.f) + (16 * 1 / 2)));
=======
		tempDef.position.Set(float32((16 * 112.f) + (16 * 12 / 2)), float32((16 * 2.f) + (16 * 1 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform O 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 12, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 123.f) + (16 * 12 / 2)), float32((16 * 4.f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform P
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 137.f) + (16 * 4 / 2)), float32((16 * 1.f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform Q
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 144.f) + (16 * 4 / 2)), float32((16 * 3.2f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform R
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 151.f) + (16 * 4 / 2)), float32((16 * 5.3f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform S
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 157.f) + (16 * 4 / 2)), float32((16 * 7.7f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform T
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 156.f) + (16 * 4 / 2)), float32((16 * 2.7f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
<<<<<<< Updated upstream
	//Platform U
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

=======
	//Platform U Crumbling Platform #1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cPlatforms[0] = entity;
>>>>>>> Stashed changes
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
<<<<<<< Updated upstream

		//Sets up components
		std::string fileName = "sandFloor.png";
=======
		ECS::AttachComponent<CrumblingSequence>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		/*std::string fileName = "sandFloor.png";*/
		std::string fileName = "spritesheets/crumblingPlatform.png";
		std::string JSONFile = "crumble.json";

		ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 16 * 3, 16 * 2, entity, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity), &ECS::GetComponent<Transform>(entity), false, &ECS::GetComponent<PhysicsBody>(entity));
>>>>>>> Stashed changes
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 163.f) + (16 * 4 / 2)), float32((16 * 4.f) + (16 * 1 / 2)));
=======
		tempDef.position.Set(float32((16 * 163.f) + (16 * 4 / 2)), float32((16 * 4.f) + (16 * 1 / 2))); //(2640,72)
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
<<<<<<< Updated upstream

	//Platform V
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
=======
	//Platform U Trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cTriggers[0] = entity;

		//Add components
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[0]);

>>>>>>> Stashed changes
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 169.f) + (16 * 4 / 2)), float32((16 * 6.f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform W
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

=======
		tempDef.position.Set(float32(2640), float32(72));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float((64) - shrinkX),
			float((16) - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Platform V Crumbling Platform #2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cPlatforms[1] = entity;
>>>>>>> Stashed changes
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
<<<<<<< Updated upstream

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
=======
		ECS::AttachComponent<CrumblingSequence>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		/*std::string fileName = "sandFloor.png";*/
		std::string fileName = "spritesheets/crumblingPlatform.png";
		std::string JSONFile = "crumble.json";

		ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 16 * 3, 16 * 2, entity, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity), &ECS::GetComponent<Transform>(entity), false, &ECS::GetComponent<PhysicsBody>(entity));
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1); //(64,16)
>>>>>>> Stashed changes
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 177.f) + (16 * 4 / 2)), float32((16 * 5.f) + (16 * 1 / 2)));
=======
		tempDef.position.Set(float32((16 * 169.f) + (16 * 4 / 2)), float32((16 * 6.f) + (16 * 1 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
<<<<<<< Updated upstream
	//Platform X 
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
=======
	//Platform V Trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cTriggers[1] = entity;

		//Add components
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[1]);

>>>>>>> Stashed changes
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 183.f) + (16 * 4 / 2)), float32((16 * 2.f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform Y(moving floor)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

=======
		tempDef.position.Set(float32(2736), float32(104));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float((64) - shrinkX),
			float((16) - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Platform W Crumbling Platform #3
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cPlatforms[2] = entity;
>>>>>>> Stashed changes
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
<<<<<<< Updated upstream

		//Sets up components
		std::string fileName = "dwaynethedarkerrockfloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 6, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

=======
		ECS::AttachComponent<CrumblingSequence>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
	/*	std::string fileName = "sandFloor.png";*/
		std::string fileName = "spritesheets/crumblingPlatform.png";
		std::string JSONFile = "crumble.json";

		ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 16 * 3, 16 * 2, entity, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity), &ECS::GetComponent<Transform>(entity), false, &ECS::GetComponent<PhysicsBody>(entity));
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
>>>>>>> Stashed changes
		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 188.f) + (16 * 6 / 2)), float32((16 * 5.f) + (16 * 1 / 2)));
=======
		tempDef.position.Set(float32((16 * 177.f) + (16 * 4 / 2)), float32((16 * 5.f) + (16 * 1 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
<<<<<<< Updated upstream
	//Platform Z
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
=======
	//Platform W Trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cTriggers[2] = entity;

		//Add components
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[2]);

>>>>>>> Stashed changes
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 200.f) + (16 * 2 / 2)), float32((16 * 2.f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform Z
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
=======
		tempDef.position.Set(float32(2864), float32(88));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float((64) - shrinkX),
			float((16) - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Platform X Crumbling Platform #4
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cPlatforms[3] = entity;
>>>>>>> Stashed changes

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
<<<<<<< Updated upstream

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 1);
=======
		ECS::AttachComponent<CrumblingSequence>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		//Sets up components
		/*std::string fileName = "sandFloor.png";*/
		std::string fileName = "spritesheets/crumblingPlatform.png";
		std::string JSONFile = "crumble.json";

		ECS::GetComponent<CrumblingSequence>(entity).InitPlatform(fileName, JSONFile, 16 * 3, 16 * 2, entity, &ECS::GetComponent<Sprite>(entity),
			&ECS::GetComponent<AnimationController>(entity), &ECS::GetComponent<Transform>(entity), false, &ECS::GetComponent<PhysicsBody>(entity));
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
>>>>>>> Stashed changes
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 200.f) + (16 * 2 / 2)), float32((16 * 2.f) + (16 * 1 / 2)));
=======
		tempDef.position.Set(float32((16 * 183.f) + (16 * 4 / 2)), float32((16 * 2.f) + (16 * 1 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
<<<<<<< Updated upstream

	}
	//Platform ZA (main boss platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 30, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
=======
	}
	//Platform X Trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		cTriggers[3] = entity;

		//Add components
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new DestroyPlatformTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(cPlatforms[3]);

>>>>>>> Stashed changes
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 205.f) + (16 * 30 / 2)), float32((16 * 2.f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Platform ZB (end platform)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

=======
		tempDef.position.Set(float32(2960), float32(40));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float((64) - shrinkX),
			float((16) - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Platform Y(moving floor)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		movingPlat = entity;
>>>>>>> Stashed changes
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
<<<<<<< Updated upstream
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 5, 16 * 1);
=======
		std::string fileName = "dwaynethedarkerrockfloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 6, 16 * 1);
>>>>>>> Stashed changes
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 238.f) + (16 * 5 / 2)), float32((16 * 4.f) + (16 * 1 / 2)));
=======
		tempDef.position.Set(float32((16 * 188.f) + (16 * 6 / 2)), float32((16 * 5.f) + (16 * 1 / 2))); //(3056,88)
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
<<<<<<< Updated upstream
	//Ending Door
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "justgotmarried.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 1, 16 * 2);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
=======
	//moving trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		kinTrigger = entity;

		//Add components
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Kinematics>(entity);

		//Sets up components
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		ECS::GetComponent<Kinematics>(entity).SetParent(movingPlat);
		ECS::GetComponent<Kinematics>(entity).SetChild(entity);

		ECS::GetComponent<Trigger*>(entity) = new MovingTrigger;
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);

>>>>>>> Stashed changes
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
<<<<<<< Updated upstream
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 240.f) + (16 * 1 / 2)), float32((16 * 5.f) + (16 * 2 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Shadow 1
=======

		b2Body* tempBody;
		b2BodyDef tempDef;
		//tempDef.type = b2_dynamicBody;
		tempDef.type = b2_staticBody;

		tempDef.position.Set(float32((16 * 22.f) + (16 * 5 / 2)), float32((16 * 10.f) + (16 * 1 / 2) - 20));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(16 * 6 - shrinkX),
			float(16 * 1 - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
		tempPhsBody.SetFixedRotation(true);
		tempPhsBody.SetGravityScale(0.f);
	}
	//Platform Z
>>>>>>> Stashed changes
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
<<<<<<< Updated upstream
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
=======
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 1);
>>>>>>> Stashed changes
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 25.f) + (16 * 2 / 2)), float32((16 * 4.f) + (16 * 2 / 2)));
=======
		tempDef.position.Set(float32((16 * 200.f) + (16 * 2 / 2)), float32((16 * 2.f) + (16 * 1 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
<<<<<<< Updated upstream
	//Shadow 2
=======
	//Platform Z
>>>>>>> Stashed changes
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
<<<<<<< Updated upstream
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
=======
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 1);
>>>>>>> Stashed changes
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 40.f) + (16 * 2 / 2)), float32((16 * 2.f) + (16 * 2 / 2)));
=======
		tempDef.position.Set(float32((16 * 200.f) + (16 * 2 / 2)), float32((16 * 2.f) + (16 * 1 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
<<<<<<< Updated upstream
	//Shadow 3
=======
	//Platform ZA (main boss platform)
>>>>>>> Stashed changes
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
<<<<<<< Updated upstream
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
=======
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 30, 16 * 1);
>>>>>>> Stashed changes
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 83.f) + (16 * 2 / 2)), float32((16 * 5.f) + (16 * 2 / 2)));
=======
		tempDef.position.Set(float32((16 * 205.f) + (16 * 30 / 2)), float32((16 * 2.f) + (16 * 1 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
<<<<<<< Updated upstream
	//Shadow 4
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

=======
	//Boss wall
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		bossWall = entity;
>>>>>>> Stashed changes
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
<<<<<<< Updated upstream
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
=======
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16, 180);
>>>>>>> Stashed changes
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 130.f) + (16 * 2 / 2)), float32((16 * 6.f) + (16 * 2 / 2)));
=======
		tempDef.position.Set(float32(3790), float32(120)); //(3520,40)
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
<<<<<<< Updated upstream

	}
	//Shadow 5
=======
	}
	//Platform ZB (end platform)
>>>>>>> Stashed changes
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
<<<<<<< Updated upstream
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
=======
		std::string fileName = "platform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 5, 16 * 1);
>>>>>>> Stashed changes
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 158.f) + (16 * 2 / 2)), float32((16 * 10.f) + (16 * 2 / 2)));
=======
		tempDef.position.Set(float32((16 * 238.f) + (16 * 5 / 2)), float32((16 * 4.f) + (16 * 1 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
<<<<<<< Updated upstream
	//Shadow 6
=======
	//Ending Door
>>>>>>> Stashed changes
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
<<<<<<< Updated upstream
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
=======
		std::string fileName = "justgotmarried.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 1, 16 * 2);
>>>>>>> Stashed changes
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 184.f) + (16 * 2 / 2)), float32((16 * 3.f) + (16 * 2 / 2)));
=======
		tempDef.position.Set(float32((16 * 240.f) + (16 * 1 / 2)), float32((16 * 5.f) + (16 * 2 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
<<<<<<< Updated upstream
	//Shadow 7(Final Boss)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

=======
	//Shadow 1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shadows[0] = entity;
>>>>>>> Stashed changes
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
<<<<<<< Updated upstream

		//Sets up components
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 6, 16 * 6);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
=======
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);

		//Sets up components
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);
>>>>>>> Stashed changes

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
<<<<<<< Updated upstream
		tempDef.position.Set(float32((16 * 230.f) + (16 * 2 / 2)), float32((16 *6.5f) + (16 * 2 / 2)));
=======
		tempDef.position.Set(float32((16 * 25.f) + (16 * 2 / 2)), float32((16 * 4.f) + (16 * 2 / 2)));
>>>>>>> Stashed changes

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
<<<<<<< Updated upstream
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Trap/Spikes
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

=======
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Shadow 2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shadows[1] = entity;
>>>>>>> Stashed changes
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
<<<<<<< Updated upstream

		//Sets up components
		std::string fileName = "bullet.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 1, 16 * 1);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
=======
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);

		//Sets up components
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);
>>>>>>> Stashed changes

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
<<<<<<< Updated upstream
		tempDef.type = b2_staticBody;//change to dynamic
		tempDef.position.Set(float32((16 * 65.f) + (16 * 1 / 2)), float32((16 * 1.f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float((tempSpr.GetWidth() - shrinkY) / 2.f), vec2(0.f, 0.f), false, OBJECTS, GROUND | ENVIRONMENT | PLAYER, 0.3f);
=======
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 40.f) + (16 * 2 / 2)), float32((16 * 2.f) + (16 * 2 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Shadow 3
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shadows[2] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);

		//Sets up components
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 83.f) + (16 * 2 / 2)), float32((16 * 5.f) + (16 * 2 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Shadow 4
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shadows[3] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);

		//Sets up components
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 130.f) + (16 * 2 / 2)), float32((16 * 6.f) + (16 * 2 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Shadow 5
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shadows[4] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);

		//Sets up components
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 158.f) + (16 * 2 / 2)), float32((16 * 10.f) + (16 * 2 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Shadow 6
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		shadows[5] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);
		ECS::AttachComponent<ShadowLoop>(entity);
		//Sets up components
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 2, 16 * 2);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<ShadowLoop>(entity).setSequenceStart(true);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32((16 * 184.f) + (16 * 2 / 2)), float32((16 * 3.f) + (16 * 2 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Shadow 7(Final Boss)
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		boss = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "shadow2.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 6, 16 * 6);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(3500.f), float32(250));//(3696.f,120.f)

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, ENEMY, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	}
	//Final Boss Area Trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 480, 500);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(3510.f, 200.f, 5.f));
		ECS::GetComponent<Trigger*>(entity) = new ShadowAreaTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<Trigger*>(entity)->SetShadowZone(1);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.5f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(3520.f), float32(200.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Trap/Spikes
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "bullet.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 1, 16 * 1);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new KnockBackTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<Trigger*>(entity)->SetSpike(true);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;//change to dynamic
		tempDef.position.Set(float32((16 * 65.f) + (16 * 1 / 2)), float32((16 * 1.f) + (16 * 1 / 2)));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float((tempSpr.GetWidth() - shrinkY) / 2.f), vec2(0.f, 0.f), true, TRIGGER, PLAYER, 0.3f);
>>>>>>> Stashed changes
		tempPhsBody.SetGravityScale(1.3f);
		tempPhsBody.SetColor(vec4(1.f, 0.f, 1.f, 0.3f));

	}
<<<<<<< Updated upstream

	// STATIC BACKGROUND TILES \\

	// TILE 1-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger1-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3((0.f + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 2-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger2-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((16 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 3-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger3-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((32 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 4-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger4-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((48 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 5-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger5-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((64 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 6-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger6-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((80 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 7-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger7-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((96 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 8-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger8-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((112 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 9-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger9-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((128 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 10-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger10-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((144 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 11-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger11-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((160 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 12-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger12-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((176 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 13-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger13-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((192 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 14-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger14-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((208 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 15-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger15-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((224 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

	// TILE 16-1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "backgrounds/anger/anger16-1.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 16, 16 * 16);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(((240 * 16.f) + (16 * 7)), (0.f + (16 * 5)), 2.f));
	}

=======
	//Boss Platform 1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		bossPlatforms[0] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(3300), float32(150));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Boss Platform 2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		bossPlatforms[1] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(3380), float32(110));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Boss Platform 3
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		bossPlatforms[2] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(3480), float32(84));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Boss Platform 4
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		bossPlatforms[3] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(3580), float32(110));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Boss Platform 5
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		bossPlatforms[4] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "sandFloor.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 16 * 4, 16 * 1);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(3680), float32(144));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//setup orb 1
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		auto& bossPlat = ECS::GetComponent<PhysicsBody>(bossPlatforms[0]);
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "shadowOrb.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(160.f, 30.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float(bossPlat.GetBody()->GetPosition().x), float32(bossPlat.GetBody()->GetPosition().y + 30));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//setup orb 2
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		auto& bossPlat = ECS::GetComponent<PhysicsBody>(bossPlatforms[1]);
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "shadowOrb.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(160.f, 30.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float(bossPlat.GetBody()->GetPosition().x), float32(bossPlat.GetBody()->GetPosition().y + 30));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//setup orb 3
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		auto& bossPlat = ECS::GetComponent<PhysicsBody>(bossPlatforms[2]);
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "shadowOrb.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(160.f, 30.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float(bossPlat.GetBody()->GetPosition().x), float32(bossPlat.GetBody()->GetPosition().y + 30));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//setup orb 4
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		auto& bossPlat = ECS::GetComponent<PhysicsBody>(bossPlatforms[3]);
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "shadowOrb.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(160.f, 30.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float(bossPlat.GetBody()->GetPosition().x), float32(bossPlat.GetBody()->GetPosition().y + 30));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//setup orb 5
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		auto& bossPlat = ECS::GetComponent<PhysicsBody>(bossPlatforms[4]);
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "shadowOrb.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(160.f, 30.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new OrbTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float(bossPlat.GetBody()->GetPosition().x), float32(bossPlat.GetBody()->GetPosition().y + 30));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Set up respawn trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		auto& bossPlat = ECS::GetComponent<PhysicsBody>(bossPlatforms[4]);
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "testCube.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 3900, 20);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1900.f, -40.f, 2.f));
		ECS::GetComponent<Trigger*>(entity) = new RespawnTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(1900.f),float32(-40.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Set up breakable wall
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		breakableWalls[0] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "maxHealth.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 30);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(80.f, 20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(80), float32(33));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//Set up breakable wall trigger
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		breakableWallTriggers[0] = entity;
		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);
		ECS::AttachComponent<Trigger*>(entity);

		//Sets up components
		std::string fileName = "testCube.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 30);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(50.f, 33.f, 3.f));
		ECS::GetComponent<Trigger*>(entity) = new BreakableWallTrigger();
		ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
		ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(50.f), float32(33.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
			float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
		tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));
	}
	//test sprite #1
	{
		auto entity = ECS::CreateEntity();
		testSprites[0] = entity;
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		std::string fileName = "heartUI.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(20, 20, 4));
	}
	//test sprite #2
	{
		auto entity = ECS::CreateEntity();
		testSprites[1] = entity;
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		std::string fileName = "heartUI.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(20, 20, 4));
	}
	//test sprite #3
	{
		auto entity = ECS::CreateEntity();
		testSprites[2] = entity;
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		std::string fileName = "heartUI.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(20, 20, 4));
	}
	//Shield UI Sprite
	{
		auto entity = ECS::CreateEntity();
		shieldUI = entity;
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		std::string fileName = "shieldUI.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(20, 20, 4));
	}
	//Shield UI Sprite
	{
		auto entity = ECS::CreateEntity();
		attackUI = entity;
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		std::string fileName = "attackUI.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(20, 20, 4));
	}
	//Ouch Sprite
	{
		auto entity = ECS::CreateEntity();
		ouchUI = entity;
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Kinematics>(entity);
		ECS::AttachComponent<Transform>(entity);
		std::string fileName = "ouch.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 40, 20);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30, 60, 5));
		ECS::GetComponent<Kinematics>(entity).SetParent(player);
		ECS::GetComponent<Kinematics>(entity).SetChild(ouchUI);
		ECS::GetComponent<Kinematics>(entity).SetOffset(10, 30);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.f);
	}
>>>>>>> Stashed changes
	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void AngerLevel::Update()
{
<<<<<<< Updated upstream
	auto& player = ECS::GetComponent<Player>(MainEntities::MainPlayer());
	player.Update();
=======
	allShadowsDefeated = true;
	for (int i = 0; i < 6; i++)
	{
		if (ECS::GetComponent<ShadowLoop>(shadows[i]).isShadowAlive == true)
		{
			allShadowsDefeated = false;
		}
	}
	auto& playerSprite = ECS::GetComponent<Sprite>(player);
	auto& thePlayer = ECS::GetComponent<Player>(player);
	auto& playerShield = ECS::GetComponent<Kinematics>(shield);
	auto& shieldThing = ECS::GetComponent<ShieldMechanic>(shield);
	//auto& isKnocked = ECS::GetComponent<KnockBack>(player);
	//auto& attackComponent = ECS::GetComponent<AttackMechanic>(player);
	auto& theCoolDown = ECS::GetComponent<CoolDown>(player);
	auto& angerBoss = ECS::GetComponent<BossLevel>(player);
	//auto& shadowThing2 = ECS::GetComponent<ShadowTime>(MainEntities::MainPlayer());
	auto& bossSprite = ECS::GetComponent<Sprite>(boss);
	auto& bossBody = ECS::GetComponent<PhysicsBody>(boss);
	auto& kinTrig = ECS::GetComponent<Kinematics>(kinTrigger);
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(player);
	kinTrig.UpdatePosition();
	playerMech.RunKnockBackTime();
	playerShield.SetPosition();
	AngerLevel::CheckShield();
	shieldThing.activateShield();
	AngerLevel::ReattachCamera();
	if (playerMech.GetCanMove() == true)
	{
		thePlayer.Update();
	}
	playerMech.Attacking();
	//shadow1
	if (ECS::GetComponent<ShadowLoop>(shadows[0]).isShadowAlive == true)
	{
		AngerLevel::ChangeVisualState(shadows[0]);
		ECS::GetComponent<ShadowLoop>(shadows[0]).ShadowRoutine();
	}
	else
	{
		ECS::GetComponent<PhysicsBody>(shadows[0]).GetBody()->SetActive(false);
		ECS::GetComponent<Sprite>(shadows[0]).SetTransparency(0.f);
	}
	//shadow2
	if (ECS::GetComponent<ShadowLoop>(shadows[1]).isShadowAlive == true)
	{
		AngerLevel::ChangeVisualState(shadows[1]);
		ECS::GetComponent<ShadowLoop>(shadows[1]).ShadowRoutine();
	}
	else
	{
		ECS::GetComponent<PhysicsBody>(shadows[1]).GetBody()->SetActive(false);
		ECS::GetComponent<Sprite>(shadows[1]).SetTransparency(0.f);
	}
	//shadow3
	if (ECS::GetComponent<ShadowLoop>(shadows[2]).isShadowAlive == true)
	{
		AngerLevel::ChangeVisualState(shadows[2]);
		ECS::GetComponent<ShadowLoop>(shadows[2]).ShadowRoutine();
	}
	else
	{
		ECS::GetComponent<PhysicsBody>(shadows[2]).GetBody()->SetActive(false);
		ECS::GetComponent<Sprite>(shadows[2]).SetTransparency(0.f);
	}
	//shadow4
	if (ECS::GetComponent<ShadowLoop>(shadows[3]).isShadowAlive == true)
	{
		AngerLevel::ChangeVisualState(shadows[3]);
		ECS::GetComponent<ShadowLoop>(shadows[3]).ShadowRoutine();
	}
	else
	{
		ECS::GetComponent<PhysicsBody>(shadows[3]).GetBody()->SetActive(false);
		ECS::GetComponent<Sprite>(shadows[3]).SetTransparency(0.f);
	}
	//shadow5
	if (ECS::GetComponent<ShadowLoop>(shadows[4]).isShadowAlive == true)
	{
		AngerLevel::ChangeVisualState(shadows[4]);
		ECS::GetComponent<ShadowLoop>(shadows[4]).ShadowRoutine();
	}
	else
	{
		ECS::GetComponent<PhysicsBody>(shadows[4]).GetBody()->SetActive(false);
		ECS::GetComponent<Sprite>(shadows[4]).SetTransparency(0.f);
	}
	//shadow6
	if (ECS::GetComponent<ShadowLoop>(shadows[5]).isShadowAlive == true)
	{
		AngerLevel::ChangeVisualState(shadows[5]);
		ECS::GetComponent<ShadowLoop>(shadows[5]).ShadowRoutine();
	}
	else
	{
		ECS::GetComponent<PhysicsBody>(shadows[5]).GetBody()->SetActive(false);
		ECS::GetComponent<Sprite>(shadows[5]).SetTransparency(0.f);
	}
	/*if (attackComponent.isAttacking == true)
	{
		playerSprite.LoadSprite(attackPose, 20, 20);
	}
	else if (attackComponent.isAttacking == false)
	{
		playerSprite.LoadSprite(defaultPose, 20, 20);
	}*/
	theCoolDown.GlobalCoolDown();
	angerBoss.CheckBossStatus();
	playerMech.RunShadowTime();
	if (angerBoss.GetBossDefeated() == false)
	{
		AngerLevel::ActivateShadow();
	}
	else
	{
		bossSprite.SetTransparency(0.f);
		bossBody.GetBody()->SetActive(false);
	}


	AngerLevel::MovePlatform();
	AngerLevel::PlayerDeath();

	if (angerBoss.GetBossDefeated() == true && allShadowsDefeated == true)
	{
		if (bossWallDestroyed == false)
		{
			PhysicsBody::m_bodiesToDelete.push_back(bossWall);
			bossWallDestroyed = true;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		ECS::GetComponent<CrumblingSequence>(cPlatforms[i]).Crumble(cPlatforms[i]);
		CrumblingPlatforms(cPlatforms[i]);
	}
	playerMech.CheckWallStatus(breakableWalls[0],breakableWallTriggers[0]);
	
	UpdatePositionWithCamera(camera, testSprites[0], -100, 60);
	UpdatePositionWithCamera(camera, testSprites[1], -90, 60);
	UpdatePositionWithCamera(camera, testSprites[2], -80, 60);
	UpdatePositionWithCamera(camera, shieldUI, -70, 60);
	UpdatePositionWithCamera(camera, attackUI, -60, 60);
	UpdateUI();
	
	ECS::GetComponent<Kinematics>(ouchUI).SetPosition();
>>>>>>> Stashed changes
}

void AngerLevel::KeyboardHold()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	float speed = 3.f;
	b2Vec2 vel = b2Vec2(0.f, 0.f);
	vec3 velocity = vec3(0.f, 0.f, 0.f);

<<<<<<< Updated upstream
	if (Input::GetKey(Key::Shift))
=======
	/*if (Input::GetKey(Key::Shift))
>>>>>>> Stashed changes
	{
		speed *= 5.f;
	}

	if (Input::GetKey(Key::A))
	{
<<<<<<< Updated upstream
		player.GetBody()->SetLinearVelocity(b2Vec2(-38000.f * (speed * Timer::deltaTime), 0.f));
=======
		player.GetBody()->SetLinearVelocity(b2Vec2(-100000.f * (speed * Timer::deltaTime), 0.f));
>>>>>>> Stashed changes
		velocity = velocity + vec3(-100.f, 0.f, 0.f);
	}
	if (Input::GetKey(Key::D))
	{
<<<<<<< Updated upstream
		player.GetBody()->SetLinearVelocity(b2Vec2(38000.f * (speed * Timer::deltaTime), 0.f));
=======
		player.GetBody()->SetLinearVelocity(b2Vec2(100000.f * (speed * Timer::deltaTime), 0.f));
>>>>>>> Stashed changes
		velocity = velocity + vec3(100.f, 0.f, 0.f);
	}

	if (Input::GetKey(Key::W))
	{
<<<<<<< Updated upstream
		player.GetBody()->SetLinearVelocity(b2Vec2(-38000.f * (speed * Timer::deltaTime), 0.f));
=======
		player.GetBody()->SetLinearVelocity(b2Vec2(-100000.f * (speed * Timer::deltaTime), 0.f));
>>>>>>> Stashed changes
		velocity = velocity + vec3(0.f, 30.f, 0.f);
	}
	if (Input::GetKey(Key::S))
	{
		player.GetBody()->SetAngularVelocity((38000.f * (speed * Timer::deltaTime), 0.f));
		velocity = velocity + vec3(0.f, -30.f, 0.f);
	}

<<<<<<< Updated upstream
	player.SetVelocity(velocity);
=======
	player.SetVelocity(velocity);*/
>>>>>>> Stashed changes
}

void AngerLevel::KeyboardUp()
{
}

void AngerLevel::KeyboardDown()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());
<<<<<<< Updated upstream
=======
	//auto& attackComponent = ECS::GetComponent<AttackMechanic>(MainEntities::MainPlayer());
	auto& shieldSprite = ECS::GetComponent<Sprite>(shield);
	auto& shieldMech = ECS::GetComponent<ShieldMechanic>(shield);
	auto& theCoolDown = ECS::GetComponent<CoolDown>(MainEntities::MainPlayer());
	auto& angerBoss = ECS::GetComponent<BossLevel>(MainEntities::MainPlayer());
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(MainEntities::MainPlayer());

>>>>>>> Stashed changes
	float speed = 1.f;
	b2Vec2 vel = b2Vec2(0.f, 0.f);

	playerVel = player.GetVelocity();
	playerPos = player.GetPosition();

<<<<<<< Updated upstream
=======
	if (Input::GetKeyDown(Key::Enter) && shieldMech.restart == true && theCoolDown.isCoolDownActive == false) //checks to see if the shield cooldown if complete before reactivating shield
	{
		shieldMech.setSequenceStart(true);
		theCoolDown.SetSequenceStart(true);
	}

	if (Input::GetKeyDown(Key::E) && playerMech.GetAttackSequence() == false && theCoolDown.isCoolDownActive == false)
	{
		playerMech.SetAttackSequence(true);
		theCoolDown.SetSequenceStart(true);
	}

>>>>>>> Stashed changes
	if (Input::GetKeyDown(Key::M)) {
		std::cout << "X Pos: " << playerPos.x << std::endl;
		std::cout << "Y Pos: " << playerPos.y << std::endl << std::endl;
	}
	if (Input::GetKeyDown(Key::T))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}
<<<<<<< Updated upstream
}
=======

	if (Input::GetKeyDown(Key::Alt))
	{
		auto& cameraBody = ECS::GetComponent<Camera>(camera);
		std::cout << "(" << cameraBody.GetPosition().x << "," << cameraBody.GetPosition().y << ")\n";
	}
}

void AngerLevel::ReattachCamera()
{
	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

//void AngerLevel::Defeated()
//{
//	auto& attackComponent = ECS::GetComponent<AttackMechanic>(MainEntities::MainPlayer());
//
//	if (attackComponent.GetShadow() == 1)
//	{
//		ECS::GetComponent<PhysicsBody>(enemy1).GetBody()->SetActive(false);
//		ECS::GetComponent<PhysicsBody>(enemy1Trigger).GetBody()->SetActive(false);
//		ECS::GetComponent<Sprite>(enemy1).SetTransparency(0.f);
//		ECS::GetComponent<Sprite>(enemy1Trigger).SetTransparency(0.f);
//	}
//	else if (attackComponent.GetShadow() == 2)
//	{
//		ECS::GetComponent<PhysicsBody>(enemy2).GetBody()->SetActive(false);
//		ECS::GetComponent<PhysicsBody>(enemy2Trigger).GetBody()->SetActive(false);
//		ECS::GetComponent<Sprite>(enemy2).SetTransparency(0.f);
//		ECS::GetComponent<Sprite>(enemy2Trigger).SetTransparency(0.f);
//	}
//	//add more as necessary
//}

void AngerLevel::CheckShield()
{
	//checks inputs from the ShieldMechanic and proceeds to turn the shield on or off
	//auto& playerHealth = ECS::GetComponent<Health>(player);
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(player);
	if (ECS::GetComponent<ShieldMechanic>(shield).shieldOn == true)
	{
		/*ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetActive(true);*/
		//ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetAwake(true);
		ECS::GetComponent<Sprite>(shield).SetTransparency(1.f);
		//shieldActive = true; //currently useless
		playerMech.SetShield(true); //Used by the BulletTrigger to check if the shield is on.
	}
	else if (ECS::GetComponent<ShieldMechanic>(shield).shieldOn == false)
	{
		/*ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetActive(false);*/
		//ECS::GetComponent<PhysicsBody>(shield).GetBody()->SetAwake(false);
		ECS::GetComponent<Sprite>(shield).SetTransparency(0.f);
		//shieldActive = false; //currently useless
		playerMech.SetShield(false); //Used by the BulletTrigger to check if the shield is on.
	}
}

void AngerLevel::ChangeVisualState(int shadowEntity)
{
	auto& shadowState = ECS::GetComponent<ShadowLoop>(shadowEntity);
	auto& shadowSprite = ECS::GetComponent<Sprite>(shadowEntity);
	std::string restingSprite = "shadow2.png";
	std::string chargingSprite = "shadow3.png";
	std::string attackingSprite = "shadow4.png";
	if (shadowState.s_resting == true)
	{
		shadowSprite.LoadSprite(restingSprite, 30, 30);
	}
	else if (shadowState.s_charging == true)
	{
		shadowSprite.LoadSprite(chargingSprite, 30, 30);
	}
	else if (shadowState.s_attacking == true)
	{
		shadowSprite.LoadSprite(attackingSprite, 30, 30);
	}
}

void AngerLevel::SpawnBullet(int shadowEntity)
{
	auto& shadowBody = ECS::GetComponent<PhysicsBody>(shadowEntity);
	float tempX = shadowBody.GetBody()->GetPosition().x; //directly subbing in the GetBody line throws an error
	float tempY = shadowBody.GetBody()->GetPosition().y;
	//Creates entity
	auto entity = ECS::CreateEntity();
	bullet = entity;

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Trigger*>(entity);

	//Set up components
	std::string fileName = "bullet.png";
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 5, 5);
	ECS::GetComponent<Transform>(entity).SetPosition(vec3(tempX, tempY, 4.f));
	ECS::GetComponent<Trigger*>(entity) = new BulletTrigger();
	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(player);

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = b2_staticBody;
	tempDef.position.Set(tempX, tempY);

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);
	tempPhsBody.SetColor(vec4(0.f, 1.f, 0.f, 0.3f));

	tempPhsBody.SetGravityScale(0.f); //ensures no bullet drop and bullet reaches the player

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void AngerLevel::ShootBullet()
{
	auto& bulletBody = ECS::GetComponent<PhysicsBody>(bullet);
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	float deltaX = 0, deltaY = 0;
	deltaX = player.GetBody()->GetPosition().x - bulletBody.GetBody()->GetPosition().x;
	deltaY = player.GetBody()->GetPosition().y - bulletBody.GetBody()->GetPosition().y;
	float n_deltaX = 0, n_deltaY = 0;
	n_deltaX = deltaX / (deltaX * deltaX + deltaY * deltaY);
	n_deltaY = deltaY / (deltaX * deltaX + deltaY * deltaY);
	bulletBody.GetBody()->SetType(b2BodyType::b2_dynamicBody);
	bulletBody.GetBody()->SetLinearVelocity(b2Vec2(deltaX * 100000000, deltaY * 100000000));
}

void AngerLevel::ActivateShadow()
{
	//Checks to see if the appropriate amount of seconds of passed between now and the last shot. 
	//If so, a bullet is fired from a shadow determined by the player's location.
	/*auto& theTime = ECS::GetComponent<ShadowTime>(player);
	auto& theLoc = ECS::GetComponent<ShadowSense>(player);*/
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(player);
	if (playerMech.GetFiring() == true)
	{
		if (playerMech.GetShadowLoc() == 1)
		{
			AngerLevel::SpawnBullet(boss);
			AngerLevel::ShootBullet();
		}
		//add additional else if statements for additional shadows
	}
}

void AngerLevel::MovePlatform()
{
	auto& moveTrig = ECS::GetComponent<MovingClass>(player);
	auto& playerBody = ECS::GetComponent<PhysicsBody>(player);
	auto& plat = ECS::GetComponent<PhysicsBody>(movingPlat);
	//auto& vert = ECS::GetComponent<PhysicsBody>(vertMovingPlat);
	float platX = plat.GetPosition().x;
	float platY = plat.GetPosition().y;
	int playerX = playerBody.GetPosition().x;
	int playerY = playerBody.GetPosition().y;

	static bool vertSwitch = false;

	//if (vert.GetPosition().y <= 408)
	//{
	//	vertSwitch = false;
	//}
	//if (vert.GetPosition().y >= 808)
	//{
	//	vertSwitch = true;
	//}

	//if (vertSwitch == false)
	//{
	//	vert.SetPosition(b2Vec2(vert.GetPosition().x, vert.GetPosition().y + 0.5));
	//}
	//else
	//{
	//	vert.SetPosition(b2Vec2(vert.GetPosition().x, vert.GetPosition().y - 0.5));
	//}

	if (platX > 3170)
	{
		switchDir = true;

	}
	if (platX < 3030)
	{
		switchDir = false;

	}
	if (switchDir == false)
	{
		platX += 0.5;
		plat.SetPosition(b2Vec2(platX, platY));
		moveTrig.SetRight(true);
		moveTrig.SetLeft(false);

		//plat.SetVelocity(vec3(1250 * Timer::deltaTime, 0, 0));
		//if (moveTrig.GetMoving() == true)
		//{
		//	playerX += 1;
		//	if (!Input::GetKey(Key::A))
		//	{
		//		playerBody.SetVelocity(vec3(5000, 0, 0));
		//	}
		//	//playerBody.SetPosition(b2Vec2(playerX, playerY));
		//}
	}
	else if (switchDir == true)
	{
		platX -= 0.5;
		plat.SetPosition(b2Vec2(platX, platY));
		moveTrig.SetLeft(true);
		moveTrig.SetRight(false);
	}
}

void AngerLevel::PlayerDeath()
{
	//auto& playerHealth = ECS::GetComponent<Health>(player);
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(player);
	auto& playerBody = ECS::GetComponent<PhysicsBody>(player);
	if (playerMech.GetRespawn() == true) //if palyer falls off map
	{
		playerBody.SetPosition(b2Vec2(50, 50));
		playerMech.SetHealth(3);
		playerMech.SetRespawn(false);
		for (int i = 0; i < 3; i++)
		{
			ECS::GetComponent<Sprite>(testSprites[i]).SetTransparency(1.f);
		}
	}
	else if (playerMech.GetHealth() <= 0) //if player dies from shadow attack
	{
		playerBody.SetPosition(b2Vec2(50, 50));
		playerMech.SetHealth(3);
		for (int i = 0; i < 3; i++)
		{
			ECS::GetComponent<Sprite>(testSprites[i]).SetTransparency(1.f);
		}
	}
}

void AngerLevel::MouseClick(SDL_MouseButtonEvent evnt)
{
	auto& playerBody = ECS::GetComponent<PhysicsBody>(player);
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		std::cout << "(" << evnt.x << "," << evnt.y << ")\n";
	}
}

void AngerLevel::UpdatePositionWithCamera(int cameraEntity, int spriteEntity, int tempOffsetX, int tempOffsetY)
{
	auto& cameraBody = ECS::GetComponent<Camera>(cameraEntity);
	auto& spriteBody = ECS::GetComponent<Transform>(spriteEntity);
	int offsetX = tempOffsetX;
	int offsetY = tempOffsetY;

	spriteBody.SetPosition(vec3(cameraBody.GetPosition().x + offsetX, cameraBody.GetPosition().y + offsetY, 4));
}

void AngerLevel::UpdateUI()
{
	auto& playerMech = ECS::GetComponent<PlayerMechanics>(player);
	auto& shieldMech = ECS::GetComponent<ShieldMechanic>(shield);
	auto& gameCoolDown = ECS::GetComponent<CoolDown>(player);
	if (shieldMech.shieldOn == true)
	{
		ECS::GetComponent<Sprite>(shieldUI).SetTransparency(0.2);
	}
	else if (shieldMech.shieldOn == false && gameCoolDown.isCoolDownActive == false)
	{
		ECS::GetComponent<Sprite>(shieldUI).SetTransparency(1.0);
	}

	if (playerMech.GetAttackSequence() == true) 
	{ 
		ECS::GetComponent<Sprite>(attackUI).SetTransparency(0.2); 
	}
	else if (playerMech.GetAttackSequence() == false && gameCoolDown.isCoolDownActive == false)
	{
		ECS::GetComponent<Sprite>(attackUI).SetTransparency(1.0);
	}

	if (playerMech.GetHealth() == 2) { ECS::GetComponent<Sprite>(testSprites[2]).SetTransparency(0.f); }
	else if (playerMech.GetHealth() == 1) { ECS::GetComponent<Sprite>(testSprites[1]).SetTransparency(0.f); }
	else if (playerMech.GetHealth() == 0) { ECS::GetComponent<Sprite>(testSprites[0]).SetTransparency(0.f); }
	if (playerMech.GetCanMove() == false)
	{
		ECS::GetComponent<Sprite>(ouchUI).SetTransparency(1.0);
	}
	else
	{
		ECS::GetComponent<Sprite>(ouchUI).SetTransparency(0);

	}
}

void AngerLevel::CrumblingPlatforms(int entity)
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
			//ECS::GetComponent<Sprite>(entity).SetTransparency(0.4f);
			ECS::GetComponent<PhysicsBody>(entity).GetBody()->SetActive(false);
			ECS::GetComponent<CrumblingSequence>(entity).disable = false;
		}
	}
}


>>>>>>> Stashed changes
