/*===============================================================================
  Purpose:  A character manages an entity that implemets the bullet KinematicCharacterController and a irrlicht render node
===============================================================================*/

#pragma once
#include <irrlicht.h>
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "Engine.h"

class Character{
protected:
	irr::scene::ISceneNode* _node;
	bool walkforward;
	bool walkback;
	bool walkleft;
	bool walkright;
	btPairCachingGhostObject* _ghostObject;
	btKinematicCharacterController* _characterC;
	btKinematicCharacterController*  addCharacter(btScalar stepHeight,btVector3* characterPosition, btScalar characterHeight, btScalar characterWidth);
	void walk(float delta);
public:
	Character(){};
	~Character(){};
	void intitalise(irr::core::vector3df position, irr::core::vector3df size);
	irr::scene::ISceneNode* getNode() { return _node; }
	btKinematicCharacterController* getController() { return _characterC; }
	bool loadContent();
	void unloadContent();
	void update(float delta){};
};