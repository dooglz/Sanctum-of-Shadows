#pragma once
#include "Physics.h"

namespace GameEngine{

	btDiscreteDynamicsWorld* Physics::world;
	btDefaultCollisionConfiguration* Physics::_collisionConfig;
	btCollisionDispatcher* Physics::_dispatcher;
	btBroadphaseInterface* Physics::broadPhase;
	btSequentialImpulseConstraintSolver* Physics::_solver;

	void Physics::initialise(){
		_collisionConfig = new btDefaultCollisionConfiguration();
		_dispatcher = new btCollisionDispatcher(_collisionConfig);
		broadPhase = new btAxisSweep3(btVector3(-1000,1000,1000), btVector3(1000,1000,1000));
		_solver= new btSequentialImpulseConstraintSolver();
		Physics::world = new btDiscreteDynamicsWorld(_dispatcher,broadPhase,_solver,_collisionConfig);
	}

	//TODO investigate if this clears everything, and if it should be a destructor instead.
	void Physics::shutdown(){
		delete Physics::world;
		delete _solver;
		delete _dispatcher;
		delete broadPhase;
		delete _collisionConfig;
	}
}