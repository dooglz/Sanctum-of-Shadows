#pragma once
#include "StaticPhysicalEntity.h"
#include "Engine.h"

namespace GameEngine{

	btRigidBody* StaticPhysicalEntity::createBoundingBoxRB(irr::scene::ISceneNode* node, irr::core::vector3df offset){
		
		//Rigid body
		irr::core::vector3df scale = irr::core::vector3df(node->getScale());
		btVector3 pos = Physics::irrVec3ToBtVec3(node->getPosition()+offset);
		irr::core::vector3df a = node->getTransformedBoundingBox().getExtent();
			//account for offset origin in model file
			//pos.setY(pos.getY()+(scale.Y*a.Y*0.5f));
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(pos);

		//setup shape
		btVector3 halfExtends(scale.X*a.X*0.5f,scale.Y*a.Y*0.5f,scale.Z*a.Z*0.5f);
		btCollisionShape* shape = new btBoxShape(halfExtends);

		//mass is 0, object is static, default motionstate
		btVector3 localInertia;
		shape->calculateLocalInertia(0,localInertia);
		btMotionState* motionstate = new btDefaultMotionState(transform);

		//create the RB
		return (new btRigidBody(0,motionstate,shape,localInertia));
	}

	StaticPhysicalEntity::~StaticPhysicalEntity()
	{
		if (_rigidBody != nullptr )
		{
			GameEngine::Physics::world->removeCollisionObject(_rigidBody);
			delete _rigidBody;
			_rigidBody = NULL;
		}
	}
}