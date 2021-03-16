#ifndef __ECS_H__
#define __ECS_H__

#include <entt/entity/registry.hpp>
#include <vector>

#include "Transform.h"
#include "Camera.h"
#include "Sprite.h"
#include "AnimationController.h"
#include "PhysicsBody.h"
#include "VerticalScroll.h"
#include "MainEntities.h"
#include "OtherEntities.h"
#include "DestroyTrigger.h"
#include "TranslateTrigger.h"
#include "MoveTrigger.h"
#include "MoveTriggerOneWay.h"
#include "ResizeTrigger.h"
#include "RotationTrigger.h"
#include "VanishTrigger.h"
#include "HorizontalScroll.h"
//#include "CanJump.h"
#include "CollisionFlag.h"
#include "FlaggedTrigger.h"
#include "RecheckConditions.h"
#include "ShrinkTrigger.h"
#include "EndTrigger.h"
#include "CrumblingSequence.h"
#include "DestroyPlatformTrigger.h"
#include "MovingClass.h"
#include "MovingTrigger.h"
#include "MovingPlatform.h"
#include "Kinematics.h"
#include "ShadowSense.h"
#include "ShadowAreaTrigger.h"
#include "ShadowTime.h"
#include "AttackTrigger.h"
#include "AttackMechanic.h"
#include "KnockBackTrigger.h"
#include "Movement.h"
#include "KnockBack.h"
#include "ShadowLoop.h"
#include "CoolDown.h"
#include "OrbTrigger.h"
#include "BossLevel.h"
#include "MovingTrigger.h"
#include "MovingClass.h"
#include "RespawnTrigger.h"
#include "PlayerMechanics.h"




#include "ShieldMechanic.h"
#include "Health.h"
#include "BulletTrigger.h"
#include "Kinematics.h"
#include "ShadowSense.h"
#include "ShadowAreaTrigger.h"
#include "ShadowTime.h"
#include "AttackTrigger.h"
#include "AttackMechanic.h"
#include "KnockBackTrigger.h"
#include "Movement.h"
#include "KnockBack.h"
#include "ShadowLoop.h"
#include "CoolDown.h"
#include "OrbTrigger.h"
#include "BossLevel.h"
#include "MovingTrigger.h"
#include "MovingClass.h"
#include "RespawnTrigger.h"
#include "PlayerMechanics.h"
#include "OutburstTrigger.h"
#include "BreakableWallTrigger.h"


#include "ShieldMechanic.h"
#include "Health.h"
#include "BulletTrigger.h"
#include "Kinematics.h"
#include "ShadowSense.h"
#include "ShadowAreaTrigger.h"
#include "ShadowTime.h"
#include "AttackTrigger.h"
#include "AttackMechanic.h"
#include "KnockBackTrigger.h"
#include "Movement.h"
#include "KnockBack.h"
#include "ShadowLoop.h"
#include "CoolDown.h"
#include "OrbTrigger.h"
#include "BossLevel.h"
#include "MovingTrigger.h"
#include "MovingClass.h"
#include "RespawnTrigger.h"
#include "PlayerMechanics.h"




#include "ShieldMechanic.h"
#include "Health.h"
#include "BulletTrigger.h"
#include "Kinematics.h"
#include "ShadowSense.h"
#include "ShadowAreaTrigger.h"
#include "ShadowTime.h"
#include "AttackTrigger.h"
#include "AttackMechanic.h"
#include "KnockBackTrigger.h"
#include "Movement.h"
#include "KnockBack.h"
#include "ShadowLoop.h"
#include "CoolDown.h"
#include "OrbTrigger.h"
#include "BossLevel.h"
#include "MovingTrigger.h"
#include "MovingClass.h"
#include "RespawnTrigger.h"
#include "PlayerMechanics.h"
#include "TestBulet.h"
#include "ShieldMechanic.h"
#include "Health.h"
#include "BulletTrigger.h"
#include "Kinematics.h"
#include "ShadowSense.h"
#include "ShadowAreaTrigger.h"
#include "ShadowTime.h"
#include "AttackTrigger.h"
#include "AttackMechanic.h"
#include "KnockBackTrigger.h"
#include "Movement.h"
#include "KnockBack.h"
#include "ShadowLoop.h"
#include "CoolDown.h"
#include "OrbTrigger.h"
#include "BossLevel.h"
#include "MovingTrigger.h"
#include "MovingClass.h"
#include "RespawnTrigger.h"
#include "PlayerMechanics.h"
#include "OutburstTrigger.h"
#include "BreakableWallTrigger.h"

class ECS abstract
{
public:
	//Attach the register to the ECS
	//*Please don't forget to do this before creating new entities
	static void AttachRegister(entt::registry* reg);	
	//Unattach the register to the ECS
	//*Please don't forget to do this when you're done creating entities
	static void UnattachRegister();

	//Create new entity and return the ID
	static unsigned CreateEntity();
	//remove entities
	static void DestroyEntity(unsigned entity);

	//Attach component 
	//*You can simply attach the component or
	template<typename T>
	static void AttachComponent(unsigned entity);
	//Attach component
	//*You can attach the component type and pass an already created object
	template<typename T>
	static void AttachComponent(unsigned entity, T object);
	//Get component
	//*Returns a reference to the component so you can edit it
	template<typename T>
	static T& GetComponent(unsigned entity);
	//Remove component
	template<typename T>
	static void RemoveComponent(unsigned entity);

	//Set up the entity identifier
	static void SetUpIdentifier(unsigned entity, unsigned componentID, std::string name);
	//Side stuff for entity identifier
	static void SetIsMainCamera(unsigned entity, bool mainCamera);
	static void SetIsMainPlayer(unsigned entity, bool mainPlayer);
	//in progress - does nothing currently
	static void SetEntityID(unsigned entity, std::vector<int> entities);


private:
	static entt::registry* m_reg;
};

template<typename T>
inline void ECS::AttachComponent(unsigned entity)
{
	//Assign component of typename T
	m_reg->assign<T>(entity);
}

template<typename T>
inline void ECS::AttachComponent(unsigned entity, T object)
{
	//Assign component of typename T
	m_reg->assign<T>(entity);
	//Set the component value to this object
	m_reg->get<T>(entity) = object;
}

template<typename T>
inline T & ECS::GetComponent(unsigned entity)
{
	return m_reg->get<T>(entity);
}

template<typename T>
inline void ECS::RemoveComponent(unsigned entity)
{
	//Remove this component from the entity
	m_reg->remove<T>(entity);
}

#endif // !__ECS_H__

