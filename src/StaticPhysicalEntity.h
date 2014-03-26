#pragma once
#include "Entity.h"
#include <btBulletCollisionCommon.h>

namespace GameEngine{
	/*! \brief An Entity that uses Bullet for collision
	 *  \ingroup Game
	 */
	class StaticPhysicalEntity : public Entity{

		protected:
			
			static btRigidBody* createBoundingBoxRB(irr::scene::ISceneNode* node, irr::core::vector3df offset);

			//! The simulated bullet Rigidbody.
			btRigidBody* _rigidBody;

		public:

			//! Constructor.
			StaticPhysicalEntity(int id, irr::scene::ISceneNode* node,const std::string& name):Entity(id,node,name){}

			//! Destructor.
			~StaticPhysicalEntity();

			//! Get the Rigidbody.
			btRigidBody* getRB() 
			{
				return _rigidBody;
			}
	};

}