#pragma once
#include <irrlicht.h>
#include "PhysicalEntity.h"
#include "Box.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "Player.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

class Enemy{
private:
	
	irr::scene::ISceneNode* _EnemyNode;
	bool walkforward;
	bool walkleft;
	bool walkright;
	Player* _player;
	btPairCachingGhostObject* _ghostObject;
	btKinematicCharacterController* _characterC;
	btKinematicCharacterController*  addCharacter(btScalar stepHeight,btVector3* characterPosition, btScalar characterHeight, btScalar characterWidth);
public:
	Enemy(){};
	~Enemy(){};
	void intitalise(irr::core::vector3df position, Player* player);
	bool loadContent();
	void unloadContent();
	void update(float delta);
};