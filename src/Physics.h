#pragma once
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <irrlicht.h>

namespace GameEngine{
	/*! \brief Creates the bullet physics world.
	 *  \ingroup Game
	 */
	class Physics{
		private:

			//! Bullet Default Collision Configuration.
			static btDefaultCollisionConfiguration* _collisionConfig;

			//! Bullet Collision Dispatcher.
			static btCollisionDispatcher* _dispatcher;

			//! Bullet Sequential Impulse Constraint Solver.
			static btSequentialImpulseConstraintSolver* _solver;

		public:

			//! Bullet Broadphase detection Interface.
			static btBroadphaseInterface* broadPhase;

			//! Bullet Discrete Dynamics World.
			static btDiscreteDynamicsWorld* world;

			//! Initialise all the physics properties.
			static void initialise();

			//! Remove all Physics.
			static void shutdown();
		
			//! Convert a Irrlicht Vector3 to a Bullet Vector3.
			static btVector3 irrVec3ToBtVec3(irr::core::vector3df iVec){
				return btVector3(iVec.X,iVec.Y,iVec.Z);
			}

			//! Convert a Bullet Vector3 to an Irrlicht Vector3.
			static irr::core::vector3df btVecToirrVec3(const btVector3& bVec){
				return irr::core::vector3df((float)bVec.getX(),(float)bVec.getY(),(float)bVec.getZ());
			}

			//! Collision Masks
			enum EPhysicsCollisionMask {
				E_Static   = 1 << 0,
				E_Riggid   = 1 << 1,
				E_Actor      = 1 << 2,
				E_Trigger   = 1 << 3,
	
				//Statics collide with Riggids and actors
				E_StaticGroup   = E_Riggid | E_Actor,
				//actors collide with statics, rigids, actors, and triggers
				E_ActorGroup   = E_Static | E_Riggid | E_Actor | E_Trigger,
				E_RiggidGroup   = E_Static | E_Riggid | E_Actor | E_Trigger,
				E_TriggerGroup   = E_Riggid | E_Actor | E_Static
			};
	};

	/*! \brief a MotionState automatically syncs Irrlicht and bullet objects.
	 *  \ingroup Game
	 */
	class MotionState : public btMotionState
	{
		public:
			//! Constructor.
			MotionState(const btTransform& initalTransformation, irr::scene::ISceneNode* const node) : node(node), initalTransformation(initalTransformation){}
		
			//! Returns the transform in bulletspace.
			void getWorldTransform(btTransform& worldTrans) const
			{
				worldTrans = this->initalTransformation;
			}

			//! Returns the irrlicht transform via a bulletspace transform.
			void setWorldTransform(const btTransform& worldTrans)
			{
				worldTrans.getOpenGLMatrix(matr.pointer());
				this->node->setRotation(matr.getRotationDegrees());
				this->node->setPosition(matr.getTranslation());
			}

		private:
			//! Irrlicht Scene Node.
			irr::scene::ISceneNode* const node;

			//! Irrlicht matrix4.
			irr::core::matrix4 matr;

			//! Bullet Initial Transform.
			btTransform initalTransformation;
	};

}