#pragma once
#include <irrlicht.h>
#include "PhysicalEntity.h"
#include "Box.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

class Player{
private:
	irr::scene::ICameraSceneNode* _camera;
	irr::scene::ISceneNode* _playerNode;
	//
	btPairCachingGhostObject* _ghostObject;
	btKinematicCharacterController* _characterC;
	btKinematicCharacterController*  addCharacter(btScalar stepHeight,btVector3* characterPosition, btScalar characterHeight, btScalar characterWidth);
public:
	Player(){};
	~Player(){};
	irr::scene::ICameraSceneNode* getCamera() { return _camera; }
	void intitalise(irr::core::vector3df position);
	bool loadContent();
	void unloadContent();
	irr::scene::ISceneNode* getNode() { return _playerNode; }

	void update(float delta);
};

/*
#pragma once
#include "Entity.h"

class Player: public GameEngine::Entity{
private:
	irr::scene::ITriangleSelector* _selector;
public:
	Player() :Entity(-1,0,"Player"){}
	~Player(){};
	void intitalise();
	bool loadContent();
	void unloadContent(){};
	void update(float delta);
};
*/