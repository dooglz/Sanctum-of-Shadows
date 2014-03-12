/*===============================================================================
  Purpose:  A character manages an entity that implemets the bullet KinematicCharacterController and a irrlicht render node
===============================================================================*/

#pragma once
#include <irrlicht.h>
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "Engine.h"
#include "Entity.h"


class Character: public GameEngine::Entity{
protected:
	bool walkforward;
	bool walkback;
	bool walkleft;
	bool walkright;
	int _health;
	//
	btTransform _xform;
	btVector3 _forwardDir;
	btVector3 _upDir;
	btVector3 _strafeDir;
	btScalar _walkVelocity;
	//
	btPairCachingGhostObject* _ghostObject;
	btKinematicCharacterController* _characterC;
	btKinematicCharacterController*  addCharacter(btScalar stepHeight,btVector3* characterPosition, btScalar characterHeight, btScalar characterWidth);
	void walk(float delta);
public:
	Character(int id, irr::scene::ISceneNode* node,const std::string& name):Entity(id,node,name){}
	~Character(){};
	void intitalise(irr::core::vector3df position, irr::core::vector3df size);
	irr::scene::ISceneNode* getNode() { return _node; }
	btKinematicCharacterController* getController() { return _characterC; }
	void update(float delta);
	void intitalise(){};
	void unloadContent();
	int getHealth() { return _health; }

};