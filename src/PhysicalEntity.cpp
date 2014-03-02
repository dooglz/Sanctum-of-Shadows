#include "PhysicalEntity.h"
#include <btBulletDynamicsCommon.h>

namespace GameEngine{

	void PhysicalEntity::update(float delta)
	{
		btVector3 point = _rigidBody->getWorldTransform().getOrigin();
		//have we fallen out of world?
		if(point.getY() < -200.0f)
		{
			die();
			return;
		}
		//If the position hasn't changed, don't bother poking irrlicht
		if(false && point == _position)
		{
			return;
		}
		else
		{
			_position = point;

			_node->setPosition(irr::core::vector3df((float)point.getX(),(float)point.getY(),(float)point.getZ()));

			const btQuaternion& quat = _rigidBody->getOrientation();
			irr::core::quaternion q(quat.getX(),quat.getY(),quat.getZ(),quat.getW());

			irr::core::vector3df euler;
			q.toEuler(euler);

			euler *= irr::core::RADTODEG;

			_node->setRotation(euler);
		}
	}
	void PhysicalEntity::die(){
		_node->remove();
		GameEngine::Physics::world->removeRigidBody(_rigidBody);
		delete _rigidBody;
		_rigidBody = 0;
		Entity::die();
	}
}