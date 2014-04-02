#include "PhysicalEntity.h"
#include <btBulletDynamicsCommon.h>

namespace GameEngine{

	//! Updates _btposition, Checks to see if out of bounds 
	void PhysicalEntity::update(float delta)
	{
		_btposition = _rigidBody->getWorldTransform().getOrigin();

		//have we fallen out of world?
		if(_btposition.getY() < -200.0f)
		{
			remove();
			return;
		}
	}

	//! Sync Bullet object to irrlicht scene node, only use if no Motionstate available.
	void PhysicalEntity::sync(float delta)
	{
		btVector3 point = _rigidBody->getWorldTransform().getOrigin();
		_btposition = point;

		_node->setPosition(irr::core::vector3df((float)point.getX(),(float)point.getY(),(float)point.getZ()));

		const btQuaternion& quat = _rigidBody->getOrientation();
		irr::core::quaternion q(quat.getX(),quat.getY(),quat.getZ(),quat.getW());

		irr::core::vector3df euler;
		q.toEuler(euler);

		euler *= irr::core::RADTODEG;

		_node->setRotation(euler);
	}


	void PhysicalEntity::remove(){
		_node->remove();
		GameEngine::Physics::world->removeRigidBody(_rigidBody);
		delete _rigidBody;
		_rigidBody = 0;
		Entity::remove();
	}
}