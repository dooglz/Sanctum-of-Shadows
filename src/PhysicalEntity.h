#pragma once
#include <btBulletCollisionCommon.h>
#include "Entity.h"
#include "Engine.h"

namespace GameEngine{
	/*! \brief An Entity that uses Bullet for motion and collision.
	 *  \ingroup Game
	 */
	class PhysicalEntity: public Entity{
		protected:
			//! The simulated bullet Rigidbody.
			btRigidBody* _rigidBody;

			//! Position in bullet space
			btVector3 _btposition;

			//! Reference to the Motionstate in use.
			GameEngine::MotionState* _motionstate;

			//! Removes Rigidbody, calls parent Destructor.
			void remove();

		public:
			//! Constructor.
			PhysicalEntity(Scene* parentScene, irr::scene::ISceneNode* node,const std::string& name):Entity(parentScene,node,name){}

			//! Destructor.
			~PhysicalEntity(){}

			//! Updates _btposition, Checks to see if out of bounds.
			void update(float delta);

			//! Sync Bullet object transformation to irrlicht scene node, only use if no Motionstate available.
			void sync(float delta);

			//! Get the Rigidbody. There is no set as that would require also changing the Motionstate and other things.
			btRigidBody* getRB() 
			{
				return _rigidBody;
			}
	};
}