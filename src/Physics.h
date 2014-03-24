#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <irrlicht.h>

namespace GameEngine{
	/*! \brief Creates the bullet physics world.
	 *  \ingroup Game
	 */
	class Physics{

	private:
		static btDefaultCollisionConfiguration* _collisionConfig;
		static btCollisionDispatcher* _dispatcher;
		static btSequentialImpulseConstraintSolver* _solver;
	public:
		static btBroadphaseInterface* broadPhase;
		static btDiscreteDynamicsWorld* world;

		// Initialise all the physics properties.
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
		MotionState(const btTransform& initalTransformation, irr::scene::ISceneNode* const node) : node(node), initalTransformation(initalTransformation){}
		
		void getWorldTransform(btTransform& worldTrans) const
		{
			worldTrans = this->initalTransformation;
		}

		void setWorldTransform(const btTransform& worldTrans)
		{
			worldTrans.getOpenGLMatrix(matr.pointer());
			this->node->setRotation(matr.getRotationDegrees());
			this->node->setPosition(matr.getTranslation());
		}
	private:
		irr::scene::ISceneNode* const node;
		irr::core::matrix4 matr;
		btTransform initalTransformation;
	};

}