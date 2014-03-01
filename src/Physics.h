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
	};
}