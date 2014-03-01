#include "Box.h"
#include "Engine.h"

#include <iostream>

Box::Box (const btVector3& position, const irr::core::vector3df& scale, float mass) : GameEngine::PhysicalEntity(-1,0,"box")
{
	//scene node
	loadContent();
	_node->setScale(scale);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	//Rigid body
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(position);
	btDefaultMotionState* motionstate = new btDefaultMotionState(transform);

	//setup shape
	btVector3 halfExtends(scale.X*0.5f,scale.Y*0.5f,scale.Z*0.5f);
	btCollisionShape* shape = new btBoxShape(halfExtends);

	//calc intertia, based on mass and shape
	btVector3 localInertia;
	shape->calculateLocalInertia(mass,localInertia);

	//create the RB
	_rigidBody = new btRigidBody(mass,motionstate,shape,localInertia);
	//add to world
	GameEngine::Physics::world->addRigidBody(_rigidBody);

	//free memory used for setup
	//delete motionstate;
	//delete shape;

	_alive = true;
}

void Box::intitalise()
{
}

bool Box::loadContent()
{
	irr::scene::IAnimatedMesh* cube = GameEngine::engine.getDevice()->getSceneManager()->getMesh("models/cube1.obj");
	if (!cube)
	{
		std::cerr << "Error loading Mesh" << std::endl;
		return false;
	}
	_node = GameEngine::engine.getDevice()->getSceneManager()->addAnimatedMeshSceneNode(cube);
	//_node = engine.getDevice()->getSceneManager()->addEmptySceneNode();
	//_node->setScale(irr::core::vector3df(2.0f, 2.0f, 2.0f));
	//_node->setPosition(irr::core::vector3df(0, 0.0f, 0));
	//_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	return true;
}

void Box::update(float delta)
{
	PhysicalEntity::update(delta);
	if(_alive)
	{
		if(rand() % 10000 == 1)
		{
			//fire();
		}
	//	_node->setPosition(_node->getPosition() + _velocity * delta);
	}
}

void Box::handleMessage(const GameEngine::Message& message)
{
	if(message.message == "laserHit")
	{
		_alive = false;
		_node->setVisible(false);
	}
}