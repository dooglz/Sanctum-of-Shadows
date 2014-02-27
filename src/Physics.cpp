#include "Physics.h"

namespace GameEngine{
	btDiscreteDynamicsWorld* Physics::world;
	btDefaultCollisionConfiguration* Physics::_collisionConfig;
	btCollisionDispatcher* Physics::_dispatcher;
	btBroadphaseInterface* Physics::_broadPhase;
	btSequentialImpulseConstraintSolver* Physics::_solver;

	bool Physics::initialise(){
		_collisionConfig = new btDefaultCollisionConfiguration();
		_dispatcher = new btCollisionDispatcher(_collisionConfig);
		_broadPhase = new btAxisSweep3(btVector3(-1000,1000,1000), btVector3(1000,1000,1000));
		_solver= new btSequentialImpulseConstraintSolver();
		Physics::world = new btDiscreteDynamicsWorld(_dispatcher,_broadPhase,_solver,_collisionConfig);
		return true;
	}

	void Physics::shutdown(){
		delete Physics::world;
		delete _solver;
		delete _dispatcher;
		delete _broadPhase;
		delete _collisionConfig;
	}
}