#include "Physics.h"

namespace GameEngine{

	//physics
	btDiscreteDynamicsWorld* Physics::world;
	btDefaultCollisionConfiguration* Physics::_collisionConfig;
	btCollisionDispatcher* Physics::_dispatcher;
	btBroadphaseInterface* Physics::broadPhase;
	btSequentialImpulseConstraintSolver* Physics::_solver;

	bool Physics::initialise(){
		_collisionConfig = new btDefaultCollisionConfiguration();
		_dispatcher = new btCollisionDispatcher(_collisionConfig);
		broadPhase = new btAxisSweep3(btVector3(-1000,1000,1000), btVector3(1000,1000,1000));
		_solver= new btSequentialImpulseConstraintSolver();
		Physics::world = new btDiscreteDynamicsWorld(_dispatcher,broadPhase,_solver,_collisionConfig);
		return true;
	}

	void Physics::shutdown(){
		delete Physics::world;
		delete _solver;
		delete _dispatcher;
		delete broadPhase;
		delete _collisionConfig;
	}
}