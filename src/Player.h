#pragma once
#include <irrlicht.h>
#include "PhysicalEntity.h"
#include "Box.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

class Player{
private:
	GameEngine::PhysicalEntity* _physicsMesh;
	irr::scene::ICameraSceneNode* _camera;
	btRigidBody* _playerRB;
	irr::scene::ISceneNode* _playerNode;
	//
	btPairCachingGhostObject* m_ghostObject;
	btKinematicCharacterController* m_character;
	btKinematicCharacterController*  addCharacter(btScalar stepHeight,btVector3* characterPosition, btScalar characterHeight, btScalar characterWidth);
public:
	Player(){};
	~Player(){};
	irr::scene::ICameraSceneNode* getCamera() { return _camera; }
	void intitalise(irr::core::vector3df position);
	bool loadContent();
	void unloadContent();
	void update(float delta);
	void update2(float delta);
	void update3(float delta);
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