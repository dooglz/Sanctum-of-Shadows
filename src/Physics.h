#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <irrlicht.h>

namespace GameEngine{
	class Physics{

	private:
		static btDefaultCollisionConfiguration* _collisionConfig;
		static btCollisionDispatcher* _dispatcher;
		static btBroadphaseInterface* _broadPhase;
		static btSequentialImpulseConstraintSolver* _solver;
	public:
		static btDiscreteDynamicsWorld* world;
		static bool initialise();
		static void shutdown();
		//TODO actually do this properly
		static btVector3 irrVec3ToBtVec3(irr::core::vector3df iVec){
			return btVector3(iVec.X,iVec.Y,iVec.Z);
		}
		static irr::core::vector3df btVecToirrVec3(const btVector3& bVec){
			return irr::core::vector3df((float)bVec.getX(),(float)bVec.getY(),(float)bVec.getZ());
		}

	};

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